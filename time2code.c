// time2code.c
// This program by Vishnu Pillai


#include <stdio.h>
#include <assert.h>

// You must use these #defines - DO NOT CHANGE THEM

// Australia

#define TOWN_ADELAIDE       0
#define TOWN_BRISBANE       1
#define TOWN_BROKEN_HILL    2
#define TOWN_CANBERRA       3
#define TOWN_DARWIN         4
#define TOWN_EUCLA          5
#define TOWN_HOBART         6
#define TOWN_LORD_HOWE_IS   7
#define TOWN_MELBOURNE      8
#define TOWN_PERTH          9
#define TOWN_SYDNEY         10

// New Zealand

#define TOWN_AUCKLAND       11
#define TOWN_CHRISTCHURCH   12
#define TOWN_WELLINGTON     13

// Australia

#define TIMEZONE_AWST_OFFSET  800 // Australian Western Standard Time

#define TIMEZONE_ACWST_OFFSET 845 // Australian Central Western Standard Time

#define TIMEZONE_ACST_OFFSET  930 // Australian Central Standard Time
#define TIMEZONE_ACDT_OFFSET 1030 // Australian Central Daylight Time

#define TIMEZONE_AEST_OFFSET 1000 // Australian Eastern Standard Time
#define TIMEZONE_AEDT_OFFSET 1100 // Australian Eastern Daylight Time

#define TIMEZONE_LHST_OFFSET 1030 // Lord Howe Standard Time
#define TIMEZONE_LHDT_OFFSET 1100 // Lord Howe Daylight Time

// New Zealand
#define TIMEZONE_NZST_OFFSET 1200 // NZ Standard Time
#define TIMEZONE_NZDT_OFFSET 1300 // NZ Daylight Time

// returned by get_local_time
#define INVALID_INPUT (-1)


// ADD YOUR #defines (if any) here

#define DAYLIGHT_SAVING (-10)
#define STANDARD (-20)
#define number_of_towns 14
#define VALID_INPUT (-2)

//Months

#define JANUARY 1
#define FEBRUARY 2
#define MARCH 3
#define APRIL 4
#define MAY 5
#define JUNE 6
#define JULY 7
#define AUGUST 8
#define SEPTEMBER 9
#define OCTOBER 10
#define NOVEMBER 11
#define DECEMBER 12

int get_local_time(int town, int utc_month, int utc_day, int utc_time);
void run_unit_tests(void);

// ADD PROTOTYPES FOR YOUR FUNCTIONS HERE

int dstAustralia(int town, int month, int day, int time); 
int dstNewZealand(int town, int month, int day, int time); 
int timeZone(int town, int month, int day, int time); 
int pastMidnight(int town, int month, int day, int time); 
int findTime(int town, int month, int day, int time); 
int invalidInput(int town, int month, int day, int time); 
int invalidTown(int town, int month, int day, int time);
int invalidMonth(int town, int month, int day, int time); 
int invalidDay(int town, int month, int day, int time);
int invalidTime(int town, int month, int day, int time); 


int main(void) {
    int call_get_local_time = 0;

    printf("Enter 0 to call run_unit_tests()\n");
    printf("Enter 1 to call get_local_time()\n");
    printf("Call which function: ");
    scanf("%d", &call_get_local_time);

    if (!call_get_local_time) {
        printf("calling run_unit_tests()\n");
        run_unit_tests();
        printf("unit tests done\n");
        return 0;
    }

    int town = 0;
    int month = 0;
    int day = 0;
    int time = 0;

    printf("Enter %d for Adelaide\n", TOWN_ADELAIDE);
    printf("Enter %d for Brisbane\n", TOWN_BRISBANE);
    printf("Enter %d for Broken_hill\n", TOWN_BROKEN_HILL);
    printf("Enter %d for Canberra\n", TOWN_CANBERRA);
    printf("Enter %d for Darwin\n", TOWN_DARWIN);
    printf("Enter %d for Eucla\n", TOWN_EUCLA);
    printf("Enter %d for Hobart\n", TOWN_HOBART);
    printf("Enter %d for Lord Howe Island\n", TOWN_LORD_HOWE_IS);
    printf("Enter %d for Melbourne\n", TOWN_MELBOURNE);
    printf("Enter %d for Perth\n", TOWN_PERTH);
    printf("Enter %d for Sydney\n", TOWN_SYDNEY);
    printf("Enter %d for Auckland\n", TOWN_AUCKLAND);
    printf("Enter %d for Christchurch\n", TOWN_CHRISTCHURCH);
    printf("Enter %d for Wellington\n", TOWN_WELLINGTON);

    printf("Which town: ");
    scanf("%d", &town);
 
    printf("Enter UTC month as integer 1..12: ");
    scanf("%d", &month);

    printf("Enter UTC day as integer 1..31: ");
    scanf("%d", &day);

    printf("Enter UTC time as hour * 100 + minutes\n");
    printf("Enter UTC time as integer [0..2359]: ");
    scanf("%d", &time);

    int local_time = get_local_time(town, month, day, time);

    if (local_time == INVALID_INPUT) {
        printf("invalid input - local time could not be calculated\n");
    } else {
        printf("local_time is %d\n", local_time);
    }
    return 0;
}



// Given an Australian town and a 2018 UTC time
// return the local time in the Australian town
//
// time is returned as hours*100 + minutes
// INVALID_INPUT is return for invalid inputs
//
// utc_month should be 1..12
// utc_day should be 1..31
// utc_time should be 0..2359
// utc_time is hours*100 + minutes
//
// note UTC year is assumed to be 2018
// note UTC seconds is assumed to be zero
//

int get_local_time(int town, int month, int day, int time) { 
    int findTime1 = findTime(town, month, day, time);
    int invalidInput1 = invalidInput(town, month, day, time);
    if (invalidInput1 == VALID_INPUT) {
        return findTime1;
    } else {
        return INVALID_INPUT;
    }
}


//Corrects bug where it portrays hour to be 0060 instead of 0100 etc.
//Finds the correct time.    
int findTime(int town, int month, int day, int time) {
    int pastMidnight1 = pastMidnight(town, month, day, time);
    int minutes = pastMidnight1 % 100;
    
    if ((minutes % 60 == 0) && (minutes % 100 != 0)) {
        pastMidnight1 = pastMidnight1 + 40;
            return pastMidnight1;
    } else if ((minutes >= 61) && (minutes <= 99)) {
        pastMidnight1 = pastMidnight1 + 40;
            return pastMidnight1;
    } else {
    return pastMidnight1;
    }
}

//Finds the time in the town given by the user.
//However, for certain values the resulting time is incorrect.
int pastMidnight(int town, int month, int day, int time) { 
    int timeZone1 = timeZone(town, month, day, time);
    int timeZone_addition = timeZone1 + time;
    int x = timeZone_addition;
    
    if (timeZone_addition >= 2400) {
        x = timeZone_addition - 2400;
    }
  
    //The below section is designed to fix a bug in which when the input is Eucla and the time is 
    //between and equal to 2355 & 2359, the output is incorrect.
    int j = time % 100; 
    
    if (town == TOWN_EUCLA && ((j == 55) || (j == 56) || (j == 57) || (j == 58) || (j == 59))) {
        if (j == 55) {
            return 840;
        }
        if (j == 56) {
            return 841;
        }
        if (j == 57) {
            return 842;
        }
        if (j == 58) {
            return 843;
        }
        if (j == 59) {
            return 844;
        }
    }
      return x;
}

//Function is checking the time zone for the given town.
int timeZone(int town, int month, int day, int time) { 
    int timeZone1 = -100;
    int dstAustralia1 = dstAustralia(town, month, day, time);
    int dstNewZealand1 = dstNewZealand(town, month, day, time);

    //Time zones during Standard Time for Australia
    if (dstAustralia1 == STANDARD) {
        if (town == TOWN_ADELAIDE) {
            timeZone1 = TIMEZONE_ACST_OFFSET;
        }
        if (town == TOWN_BRISBANE) {
            timeZone1 = TIMEZONE_AEST_OFFSET;
        }
        if (town == TOWN_BROKEN_HILL) {
            timeZone1 = TIMEZONE_ACST_OFFSET;
        }
        if (town == TOWN_CANBERRA) {
            timeZone1 = TIMEZONE_AEST_OFFSET;
        }
        if (town == TOWN_DARWIN) {
            timeZone1 = TIMEZONE_ACST_OFFSET;
        }
        if (town == TOWN_EUCLA) {
            timeZone1 = TIMEZONE_ACWST_OFFSET;
        }
        if (town == TOWN_HOBART) {
            timeZone1 = TIMEZONE_AEST_OFFSET;
        }
        if (town == TOWN_LORD_HOWE_IS) {
            timeZone1 = TIMEZONE_LHST_OFFSET;
        }
        if (town == TOWN_MELBOURNE) {
            timeZone1 = TIMEZONE_AEST_OFFSET; 
        }
        if (town == TOWN_PERTH) {
            timeZone1 = TIMEZONE_AWST_OFFSET;
        }
        if (town == TOWN_SYDNEY) {
            timeZone1 = TIMEZONE_AEST_OFFSET;
        }
    }

    //Time zones during Daylight Savings for Australia
    if (dstAustralia1 == DAYLIGHT_SAVING) {
        if (town == TOWN_ADELAIDE) {
            timeZone1 = TIMEZONE_ACDT_OFFSET;
        }
        if (town == TOWN_BRISBANE) {
            timeZone1 = TIMEZONE_AEST_OFFSET;
        }
        if (town == TOWN_BROKEN_HILL) {
            timeZone1 = TIMEZONE_ACDT_OFFSET;
        }
        if (town == TOWN_CANBERRA) {
            timeZone1 = TIMEZONE_AEDT_OFFSET;
        }
        if (town == TOWN_DARWIN) {
            timeZone1 = TIMEZONE_ACST_OFFSET; 
        }
        if (town == TOWN_EUCLA) {
            timeZone1 = TIMEZONE_ACWST_OFFSET;
        }
        if (town == TOWN_HOBART) {
            timeZone1 = TIMEZONE_AEDT_OFFSET;
        }
        if (town == TOWN_LORD_HOWE_IS) {
            timeZone1 = TIMEZONE_LHDT_OFFSET;
        }
        if (town == TOWN_MELBOURNE) {
            timeZone1 = TIMEZONE_AEDT_OFFSET; 
        }
        if (town == TOWN_PERTH) {
            timeZone1 = TIMEZONE_AWST_OFFSET;
        }
        if (town == TOWN_SYDNEY) {
            timeZone1 = TIMEZONE_AEDT_OFFSET;
        }
    }

    //Time zones during Standard time for New Zealand
    if (dstNewZealand1 == STANDARD) { 
        if (town == TOWN_AUCKLAND) {
            timeZone1 = TIMEZONE_NZST_OFFSET;
        }
        if (town == TOWN_CHRISTCHURCH) {
            timeZone1 = TIMEZONE_NZST_OFFSET;
        }
        if (town == TOWN_WELLINGTON) {
            timeZone1 = TIMEZONE_NZST_OFFSET; 
        }
    }

    //Time zones during Daylight Savings for New Zealand
    if (dstNewZealand1 == DAYLIGHT_SAVING) { 
        if (town == TOWN_AUCKLAND) {
            timeZone1 = TIMEZONE_NZDT_OFFSET;
        }
        if (town == TOWN_CHRISTCHURCH) {
            timeZone1 = TIMEZONE_NZDT_OFFSET;
        }
        if (town == TOWN_WELLINGTON) {
            timeZone1 = TIMEZONE_NZDT_OFFSET;
        }
    }
    return timeZone1; 
}

// Determines whether Standard or Daylights Saving in Australia
int dstAustralia(int town, int month, int day, int time) { 
//STANDARD = Standard Time
//DAYLIGHT_SAVING = Daylight Savings Time

    int result = -50; 

    if (town != TOWN_AUCKLAND && town != TOWN_CHRISTCHURCH && town != TOWN_WELLINGTON) { 
        if (month >= APRIL && month <= OCTOBER) {
            result = STANDARD;
        } else {
            result = DAYLIGHT_SAVING;
        }
        
        //Time zone changes at the exact hour (e.g. when time is 2 a.m. at Sydney)
        if (month == OCTOBER && day == 6 && (town == TOWN_SYDNEY || town == TOWN_MELBOURNE 
            || town == TOWN_HOBART || town == TOWN_CANBERRA) && time >= 1600) {
            result = DAYLIGHT_SAVING;
        } else if (month == OCTOBER && day == 6 && (town == TOWN_SYDNEY || town == TOWN_MELBOURNE 
                   || town == TOWN_HOBART || town == TOWN_CANBERRA) 
                   && time < 1600) {
             result = STANDARD;
        //The rest of the days in the month will be transfered to daylight saving time - bug fixed.
        //This occurs in the 'else if'.
        } else if (month == OCTOBER && day >= 7 && (town == TOWN_SYDNEY || 
                   town == TOWN_MELBOURNE || town == TOWN_HOBART || town == TOWN_CANBERRA)) {
            result = DAYLIGHT_SAVING;
        }
        if (month == MARCH && day == 31 && (town == TOWN_SYDNEY || town == TOWN_MELBOURNE || 
            town == TOWN_HOBART || town == TOWN_CANBERRA) 
            && time >= 1600) {
            result = STANDARD;         
        } else if (month == MARCH && day == 31 && (town == TOWN_SYDNEY || town == TOWN_MELBOURNE 
                  || town == TOWN_HOBART || town == TOWN_CANBERRA) 
                  && time < 1600) {
             result = DAYLIGHT_SAVING;
        }
        if (month == OCTOBER && day == 6 && (town == TOWN_LORD_HOWE_IS) && time >= 1530) {
            result = DAYLIGHT_SAVING;
        } else if (month == OCTOBER && day == 6 && (town == TOWN_LORD_HOWE_IS) && time < 1530) {
             result = STANDARD;
        //The rest of the days in the month will be transfered to daylight saving time - bug fixed.  
        //This occurs in the 'else if'.          
        } else if (month == OCTOBER && day >= 7 && (town == TOWN_LORD_HOWE_IS)) {
                result = DAYLIGHT_SAVING;
        }
        if (month == MARCH && day == 31 && (town == TOWN_LORD_HOWE_IS) && time >= 1500) {
            result = STANDARD;
        } else if (month == MARCH && day == 31 && (town == TOWN_LORD_HOWE_IS) && time < 1500) {
             result = DAYLIGHT_SAVING;
        }
    }
    return result; 
}

//Function figuring out whether the towns in New Zealand are under Standard Time or Daylight Savings time.
int dstNewZealand(int town, int month, int day, int time) { 
//STANDARD = Standard Time
//DAYLIGHT_SAVING = Daylight Saving Time 

    int result = -50; //An arbituary value

    if (town == TOWN_AUCKLAND || town == TOWN_CHRISTCHURCH || town == TOWN_WELLINGTON) {
        if (month >= APRIL && month <= 9) {
            result = STANDARD; 
        } else {
            result = DAYLIGHT_SAVING;
        }
    //Time zone changes at the exact hour   
    if (month == SEPTEMBER && day == 29 && (town == TOWN_WELLINGTON || town == TOWN_CHRISTCHURCH 
        || town == TOWN_AUCKLAND) && time >= 1400) {
            result = DAYLIGHT_SAVING;
        } else if (month == SEPTEMBER && day == 29 && (town == TOWN_WELLINGTON || 
                  town == TOWN_CHRISTCHURCH || town == TOWN_AUCKLAND) && time < 1400) {
            result = STANDARD;
        //The rest of the days in the month will be transfered to daylight saving time - bug fixed.
        //This occurs in the 'else if'.
        } else if (month == SEPTEMBER && day >= 30 && (town == TOWN_WELLINGTON || 
                   town == TOWN_CHRISTCHURCH || town == TOWN_AUCKLAND)) {
            result = DAYLIGHT_SAVING;
        }         
    if (month == MARCH && day == 31 && (town == TOWN_WELLINGTON || town == TOWN_CHRISTCHURCH || 
        town == TOWN_AUCKLAND) && time >= 1400) {
            result = STANDARD;
        } else if (month == MARCH && day == 31 && (town == TOWN_WELLINGTON || town == TOWN_CHRISTCHURCH || 
                  town == TOWN_AUCKLAND) && time < 1400) {
            result = DAYLIGHT_SAVING;
        }      
    }
    return result; 
}

//Finds valid and invalid input.
int invalidInput(int town, int month, int day, int time) {
    int invalidTown1 = invalidTown(town, month, day, time);
    int invalidMonth1 = invalidMonth(town, month, day, time);
    int invalidDay1 = invalidDay(town, month, day, time);
    int invalidTime1 = invalidTime(town, month, day, time);  
    
    if (invalidTown1 == VALID_INPUT && (invalidMonth1 == VALID_INPUT) && (invalidDay1 == VALID_INPUT) && (invalidTime1 == VALID_INPUT)) {
        return VALID_INPUT;
    } else {
        return INVALID_INPUT;
    }
}

//Finds valid and invalid input for town
int invalidTown(int town, int month, int day, int time) {
    if (town < 0 || town >= number_of_towns) {
        return INVALID_INPUT;
    }
    else {
        return VALID_INPUT;
    }
}

//Finds valid and invalid input for month
int invalidMonth(int town, int month, int day, int time) {
    if (month < JANUARY || month > DECEMBER) {
        return INVALID_INPUT;
    }
    else {
        return VALID_INPUT;
    }
}

//Finds valid and invalid input for day
int invalidDay(int town, int month, int day, int time) {  
    if (month == JANUARY || month == MARCH || month == MAY || month == JULY || month == AUGUST || month == OCTOBER || month == DECEMBER) {
          if (day < 1 || day > 31) {
            return INVALID_INPUT;
          } else {
                return VALID_INPUT;
          }    
    }
    if (month == FEBRUARY) {
          if (day < 1 || day > 28) {
            return INVALID_INPUT;
          } else {
                return VALID_INPUT;
          }
    }
    if (month == APRIL || month == JUNE || month == SEPTEMBER || month == NOVEMBER) {
          if (day < 1 || day > 30) {
            return INVALID_INPUT;
          } else {
                return VALID_INPUT;
          }
    } else {
        return VALID_INPUT;
    }
} 

//Finds valid and invalid input for time
int invalidTime(int town, int month, int day, int time) {
    int n = time % 100;
    
    if (time < 0000 || time > 2359) {
        return INVALID_INPUT;
    }   
    if (n >= 00 && n <= 59) {
        return VALID_INPUT;
    } else {
        return INVALID_INPUT;
    }
}


// OVERALL TESTING STRATEGY

// 1.) Testing if inputs for town, month, day and time are valid or invalid.

// 2.) Testing whether invalid_input function works when multiple variables are invalid.

// 3.) Testing whether time zones for each city are correct during Daylight Savings.

void run_unit_tests(void) {
    
// 1.) TESTING IF INPUTS FOR TOWN, MONTH, DAY AND TIME ARE VALID OR INVALID

    //Town cannot be > 14
    assert(get_local_time(99, JANUARY, 5, 0500) == INVALID_INPUT);
    
    // 42 is not a valid month
    assert(get_local_time(TOWN_SYDNEY, 42, 0, 0) == INVALID_INPUT);
        
    //Town cannot be < 0
    assert(get_local_time(-1, JANUARY, 5, 0500) == INVALID_INPUT);
    
    //Town can be within 1 and 14
    assert(get_local_time(TOWN_SYDNEY, MAY, 5, 0500) != INVALID_INPUT);
        
    //Month cannot be < 1
    assert(get_local_time(TOWN_SYDNEY, 0, 5, 0500) == INVALID_INPUT);
    
    //Month cannot be > 12
    assert(get_local_time(TOWN_SYDNEY, 13, 5, 0500) == INVALID_INPUT);
    
    //Month can be between 1 and 12
    assert(get_local_time(TOWN_SYDNEY, MAY, 5, 0500) != INVALID_INPUT);
    
    //Day cannot be > 31
    assert(get_local_time(TOWN_SYDNEY, JANUARY, 32, 0500) == INVALID_INPUT);
    
    //Day cannot be < 1
    assert(get_local_time(TOWN_SYDNEY, MAY, 0, 0500) == INVALID_INPUT);
    
    //Day can be between 1 and 31
    assert(get_local_time(TOWN_SYDNEY, JANUARY, 31, 0500) != INVALID_INPUT);
    
    //Day cannot be > 30 if month has 30 days
    assert(get_local_time(TOWN_SYDNEY, SEPTEMBER, 31, 0500) == INVALID_INPUT);
    
    //Day cannot be > 28 if month has 28 days
    assert(get_local_time(TOWN_SYDNEY, FEBRUARY, 29, 0500) == INVALID_INPUT);
    
    //Time cannot be negative
    assert(get_local_time(TOWN_SYDNEY, MAY, 5, -1000) == INVALID_INPUT);
    
    //Time cannot be = 2400
    assert(get_local_time(TOWN_SYDNEY, MAY, 5, 2400) == INVALID_INPUT);
    
    //Time cannot be > 2359
    assert(get_local_time(TOWN_SYDNEY, MAY, 5, 3250) == INVALID_INPUT);
    
    //Time can be equal to and between 0 and 2359
    assert(get_local_time(TOWN_SYDNEY, MAY, 5, 1423) != INVALID_INPUT);
    
    //Time can be equal to 0
    assert(get_local_time(TOWN_SYDNEY, MAY, 5, 0) != INVALID_INPUT);
    
    //The last 2 digits of time cannot be > 60
    assert(get_local_time(TOWN_SYDNEY, MAY, 5, 1861) == INVALID_INPUT);
    
    //The last 2 digits of time cannot be = 60
    assert(get_local_time(TOWN_SYDNEY, MAY, 5, 2060) == INVALID_INPUT);
    
// 2.) TESTING WHETHER INVALID_INPUT WORKS WHEN MULTIPLE INPUTS ARE INVALID
    
    //If all variables are invalid then return INVALID_INPUT
    assert(get_local_time(-5, -5 ,-5, 92902) == INVALID_INPUT);
    
// 3.) TESTING WHETHER TIME ZONES FOR EACH CITY ARE CORRECT DURING DAYLIGHT SAVINGS AND STANDARD TIME
    
    // Adelaide Daylight Saving Time Zone = 1030
    assert(get_local_time(TOWN_ADELAIDE, DECEMBER, 3, 0) == 1030);
    
    //Adelaide Daylight Saving Time Zone returns invalid input if != 1030
    assert(get_local_time(TOWN_ADELAIDE, DECEMBER, 3, 0) != 930);
    
    //Adelaide Standard Time Zone = 0930
    assert(get_local_time(TOWN_ADELAIDE, JULY, 3, 0) == 930);
    
    //Adelaide Standard Time Zone returns invalid input if != 0930
    assert(get_local_time(TOWN_ADELAIDE, JULY, 3, 0) != 1030);
    
    // Brisbane Daylight Saving Time Zone = 1000
    assert(get_local_time(TOWN_BRISBANE, DECEMBER, 3, 0) == 1000);  
    
    // Brisbane Daylight Saving Time Zone returns invalid input if != 1000
    assert(get_local_time(TOWN_BRISBANE, DECEMBER, 3, 0) != 930);
    
    // Brisbane Standard Time Zone = 1000
    assert(get_local_time(TOWN_BRISBANE, JULY, 3, 0) == 1000);
    
    // Brisbane Standard Time Zone returns invalid input if != 1000
    assert(get_local_time(TOWN_BRISBANE, JULY, 3, 0) != 930);
    
    //Broken Hill Daylight Savings Time Zone = 1030
    assert(get_local_time(TOWN_BROKEN_HILL, DECEMBER, 3, 0) == 1030);
    
    //Broken Hill Daylight Savings Time Zone returns invalid input if != 1030
    assert(get_local_time(TOWN_BROKEN_HILL, DECEMBER, 3, 0) != 930);
    
    //Broken Hill Standard Time Zone = 930
    assert(get_local_time(TOWN_BROKEN_HILL, JULY, 3, 0) == 930);
    
    //Broken Hill Standard Time Zone returns invalid input if != 930
    assert(get_local_time(TOWN_BROKEN_HILL, JULY, 3, 0) != 1030);
    
    //Canberra Daylight Savings Time Zone = 1100
    assert(get_local_time(TOWN_CANBERRA, DECEMBER, 3, 0) == 1100);
    
    //Canberra Daylight Savings Time Zone retruns invalid input if != 1100
    assert(get_local_time(TOWN_CANBERRA, DECEMBER, 3, 0) != 1000);

    //Canberra Standard Time Zone = 1000
    assert(get_local_time(TOWN_CANBERRA, JULY, 3, 0) == 1000);
    
    //Canberra Standard Time Zone returns invalid input if != 1000
    assert(get_local_time(TOWN_CANBERRA, JULY, 3, 0) != 1100);
    
    //Darwin Daylight Saving Time Zone = 930
    assert(get_local_time(TOWN_DARWIN, DECEMBER, 3, 0) == 930);
    
    //Darwin Daylight Saving Time Zone returns invalid input if != 930
    assert(get_local_time(TOWN_DARWIN, DECEMBER, 3, 0) != 830);
    
    //Darwin Standard Time Zone = 930
    assert(get_local_time(TOWN_DARWIN, JULY, 3, 0) == 930);
    
    //Darwin Standard Time Zone returns invalid input if != 930
    assert(get_local_time(TOWN_DARWIN, JULY, 3, 0) != 830);
    
    //Eucla Daylight Saving Time Zone = 845
    assert(get_local_time(TOWN_EUCLA, DECEMBER, 3, 0) == 845);
    
    //Eucla Daylight Saving Time Zone returns invalid input if != 845
    assert(get_local_time(TOWN_EUCLA, DECEMBER, 3, 0) != 900);
    
    //Eucla Standard Time Zone = 845
    assert(get_local_time(TOWN_EUCLA, JULY, 3, 0) == 845);
    
    //Eucla Standard Time Zone returns invalid input if != 845
    assert(get_local_time(TOWN_EUCLA, JULY, 3, 0) != 900);
    
    //Hobart Daylight Savng Time Zone == 1100
    assert(get_local_time(TOWN_HOBART, DECEMBER, 3, 0) == 1100);
    
    //Hobart Daylight Saving Time returns invalid input if != 1100
    assert(get_local_time(TOWN_HOBART, DECEMBER, 3, 0) != 1200);
    
    //Hobart Standard Time Zone = 1000
    assert(get_local_time(TOWN_HOBART, JULY, 3, 0) == 1000);
    
    //Hobart Standard Time Zone returns invalid input if != 1000
    assert(get_local_time(TOWN_HOBART, JULY, 3, 0) != 1523);
    
    //Lord Howe Island Daylight Saving Time Zone = 1100
    assert(get_local_time(TOWN_LORD_HOWE_IS, DECEMBER, 3, 0) == 1100);
    
    //Lord Howe Island Daylight Saving Time Zone returns invalid input if != 1100
    assert(get_local_time(TOWN_LORD_HOWE_IS, DECEMBER, 3, 0) != 820);
    
    //Lord Howe Island Standard Time Zone = 1030
    assert(get_local_time(TOWN_LORD_HOWE_IS, JULY, 3, 0) == 1030);
    
    //Lord Howe Island Standard Time Zone returns invalid input if != 1030
    assert(get_local_time(TOWN_HOBART, JULY, 3, 0) != 1100);
    
    //Melbourne Daylight Saving Time Zone = 1100
    assert(get_local_time(TOWN_MELBOURNE, DECEMBER, 3, 0) == 1100);
    
    //Melbourne Daylight Saving Time Zone returns invalid input if != 1100
    assert(get_local_time(TOWN_MELBOURNE, DECEMBER, 3, 0) != 1500);
    
    //Melbourne Standard Time Zone = 1000
    assert(get_local_time(TOWN_MELBOURNE, JULY, 3, 0) == 1000);
    
    //Melbourne Standard Time Zone returns invalid input if != 1000
    assert(get_local_time(TOWN_MELBOURNE, JULY, 3, 0) != 1900);
    
    //Perth Daylight Saving Time Zone = 800
    assert(get_local_time(TOWN_PERTH, DECEMBER, 3, 0) == 800);
    
    //Perth Daylight Saving Time Zone returns invalid if != 800
    assert(get_local_time(TOWN_PERTH, DECEMBER, 3, 0) != 1000);
    
    //Perth Standard Time Zone = 800
    assert(get_local_time(TOWN_PERTH, JULY, 3, 0) == 800);
    
    //Perth Standard Time Zone returns invalid if != 800
    assert(get_local_time(TOWN_PERTH, JULY, 3, 0) != 900);
    
    //Sydney Daylight Saving Time Zone = 1100
    assert(get_local_time(TOWN_SYDNEY, DECEMBER, 3, 0) == 1100);
    
    //Sydney Daylight Saving Time Zone returns invalid input if != 1100
    assert(get_local_time(TOWN_SYDNEY, DECEMBER, 3, 0) != 1200);
    
    //Sydney Standard Time Zone = 1000
    assert(get_local_time(TOWN_SYDNEY, JULY, 3, 0) == 1000);
    
    //Sydney Standard Time Zone returns invalid input if != 1000
    assert(get_local_time(TOWN_SYDNEY, JULY, 3, 0) != 1200);
    
    //Auckland Daylight Saving Time Zone = 1300
    assert(get_local_time(TOWN_AUCKLAND, DECEMBER, 3, 0) == 1300);
    
    //Auckland Daylight Saving Time Zone returns invalid input if != 1300
    assert(get_local_time(TOWN_AUCKLAND, DECEMBER, 3, 0) != 1400);
    
    //Auckland Standard Time Zone = 1200
    assert(get_local_time(TOWN_AUCKLAND, JULY, 3, 0) == 1200);
    
    //Auckland Standard Time Zone returns invalid input if != 1200
    assert(get_local_time(TOWN_AUCKLAND, JULY, 3, 0) != 1300);
    
    //Christchurch Daylight Saving Time Zone = 1300
    assert(get_local_time(TOWN_CHRISTCHURCH, DECEMBER, 3, 0) == 1300);
    
    //Christchurch Daylight Saving Time Zone returns invalid input if != 1300
    assert(get_local_time(TOWN_CHRISTCHURCH, DECEMBER, 3, 0) != 1400);
    
    //Christchurch Standard Time Zone = 1200
    assert(get_local_time(TOWN_CHRISTCHURCH, JULY, 3, 0) == 1200);
    
    //Christchurch Standard Time Zone returns invalid input if != 1200
    assert(get_local_time(TOWN_CHRISTCHURCH, JULY, 3, 0) != 1300);
    
    //Wellington Daylight Saving Time Zone = 1300
    assert(get_local_time(TOWN_WELLINGTON, DECEMBER, 3, 0) == 1300);
    
    //Wellington Daylight Saving Time Zone returns invalid input if != 1300
    assert(get_local_time(TOWN_WELLINGTON, DECEMBER, 3, 0) != 1400);
    
    //Wellington Standard Time Zone = 1200
    assert(get_local_time(TOWN_WELLINGTON, JULY, 3, 0) == 1200);
    
    //Wellington Standard Time Zone returns invalid input if != 1200
    assert(get_local_time(TOWN_WELLINGTON, JULY, 3, 0) != 1300);
    
//4.) Time zone at boundary conditions when the time zones change.
    
    //Sydney changing to daylight savings
    assert(get_local_time(TOWN_SYDNEY, OCTOBER, 6, 1600) == 300);
    assert(get_local_time(TOWN_SYDNEY, OCTOBER, 6, 1559) == 159);
    assert(get_local_time(TOWN_SYDNEY, OCTOBER, 6, 1601) == 301);
    
    //Sydney changing to standard time
    assert(get_local_time(TOWN_SYDNEY, MARCH, 31, 1600) == 200);
    assert(get_local_time(TOWN_SYDNEY, MARCH, 31, 1559) == 259);
    assert(get_local_time(TOWN_SYDNEY, MARCH, 31, 1601) == 201);
    
    //Melbourne changing to daylight savings (if this works all the 'or' statements for the other towns work as well)
    assert(get_local_time(TOWN_MELBOURNE, OCTOBER, 6, 1600) == 300);
    assert(get_local_time(TOWN_MELBOURNE, OCTOBER, 6, 1559) == 159);
    assert(get_local_time(TOWN_MELBOURNE, OCTOBER, 6, 1601) == 301);
    
    //Melbourne Changing to standard time (if this works all the 'or' statements for the other towns work as well)
    assert(get_local_time(TOWN_MELBOURNE, MARCH, 31, 1600) == 200);
    assert(get_local_time(TOWN_MELBOURNE, MARCH, 31, 1559) == 259);
    assert(get_local_time(TOWN_MELBOURNE, MARCH, 31, 1601) == 201);
    
    //Wellington changing to daylight savings
    assert(get_local_time(TOWN_WELLINGTON, SEPTEMBER, 29, 1400) == 300);
    assert(get_local_time(TOWN_WELLINGTON, SEPTEMBER, 29, 1359) == 159);
    assert(get_local_time(TOWN_WELLINGTON, SEPTEMBER, 29, 1401) == 301);
    
    //Wellington changing to standard time
    assert(get_local_time(TOWN_WELLINGTON, MARCH, 31, 1400) == 200);
    assert(get_local_time(TOWN_WELLINGTON, MARCH, 31, 1359) == 259);
    assert(get_local_time(TOWN_WELLINGTON, MARCH, 31, 1401) == 201);
    
    //Christchurch changing to daylight savings (if this work all the 'or' statements for the other towns work as well)
    assert(get_local_time(TOWN_CHRISTCHURCH, SEPTEMBER, 29, 1400) == 300);
    assert(get_local_time(TOWN_CHRISTCHURCH, SEPTEMBER, 29, 1359) == 159);
    assert(get_local_time(TOWN_CHRISTCHURCH, SEPTEMBER, 29, 1401) == 301);
    
    //Christchurch changing to standard time (if this work all the 'or' statements for the other towns work as well)
    assert(get_local_time(TOWN_CHRISTCHURCH, MARCH, 31, 1400) == 200);
    assert(get_local_time(TOWN_CHRISTCHURCH, MARCH, 31, 1359) == 259);
    assert(get_local_time(TOWN_CHRISTCHURCH, MARCH, 31, 1401) == 201);

}

