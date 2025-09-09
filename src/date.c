/**
 * @file date.c
 * @brief Date data structure implementation for NYCU Data Structures & Graph Algorithms
 * @author NYCU SCMA30018 Course
 * @date 2024
 * @license Apache-2.0
 */

#include "date.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Days in each month (non-leap year) */
static const int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date date_create(int year, int month, int day) {
    Date date = {year, month, day};
    return date;
}

bool date_is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int date_days_in_month(int year, int month) {
    if (month < 1 || month > 12) {
        return 0;
    }
    
    if (month == 2 && date_is_leap_year(year)) {
        return 29;
    }
    
    return days_in_month[month - 1];
}

bool date_is_valid(const Date* date) {
    if (date == NULL) {
        return false;
    }
    
    if (date->year < 1 || date->month < 1 || date->month > 12 || date->day < 1) {
        return false;
    }
    
    int max_days = date_days_in_month(date->year, date->month);
    return date->day <= max_days;
}

int date_compare(const Date* date1, const Date* date2) {
    if (date1 == NULL || date2 == NULL) {
        return 0;
    }
    
    if (date1->year != date2->year) {
        return (date1->year < date2->year) ? -1 : 1;
    }
    
    if (date1->month != date2->month) {
        return (date1->month < date2->month) ? -1 : 1;
    }
    
    if (date1->day != date2->day) {
        return (date1->day < date2->day) ? -1 : 1;
    }
    
    return 0;
}

/* Helper function to calculate days since a reference date (year 1) */
static int days_since_reference(const Date* date) {
    int total_days = 0;
    
    /* Add days for complete years */
    for (int year = 1; year < date->year; year++) {
        total_days += date_is_leap_year(year) ? 366 : 365;
    }
    
    /* Add days for complete months in the current year */
    for (int month = 1; month < date->month; month++) {
        total_days += date_days_in_month(date->year, month);
    }
    
    /* Add remaining days */
    total_days += date->day - 1;
    
    return total_days;
}

int date_diff_days(const Date* date1, const Date* date2) {
    if (date1 == NULL || date2 == NULL || !date_is_valid(date1) || !date_is_valid(date2)) {
        return 0;
    }
    
    return days_since_reference(date2) - days_since_reference(date1);
}

Date date_add_days(const Date* date, int days) {
    if (date == NULL || !date_is_valid(date)) {
        return date_create(0, 0, 0);
    }
    
    Date result = *date;
    
    if (days == 0) {
        return result;
    }
    
    if (days > 0) {
        /* Add days */
        while (days > 0) {
            int days_in_current_month = date_days_in_month(result.year, result.month);
            int days_remaining_in_month = days_in_current_month - result.day + 1;
            
            if (days < days_remaining_in_month) {
                result.day += days;
                days = 0;
            } else {
                days -= days_remaining_in_month;
                result.day = 1;
                result.month++;
                
                if (result.month > 12) {
                    result.month = 1;
                    result.year++;
                }
            }
        }
    } else {
        /* Subtract days */
        days = -days;
        while (days > 0) {
            if (days < result.day) {
                result.day -= days;
                days = 0;
            } else {
                days -= result.day;
                result.month--;
                
                if (result.month < 1) {
                    result.month = 12;
                    result.year--;
                }
                
                result.day = date_days_in_month(result.year, result.month);
            }
        }
    }
    
    return result;
}

void date_to_string(const Date* date, char* buffer) {
    if (date == NULL || buffer == NULL) {
        return;
    }
    
    sprintf(buffer, "%04d-%02d-%02d", date->year, date->month, date->day);
}

bool date_from_string(const char* str, Date* date) {
    if (str == NULL || date == NULL) {
        return false;
    }
    
    int year, month, day;
    if (sscanf(str, "%d-%d-%d", &year, &month, &day) == 3) {
        *date = date_create(year, month, day);
        return date_is_valid(date);
    }
    
    return false;
}

void date_print(const Date* date) {
    if (date == NULL) {
        printf("NULL date\n");
        return;
    }
    
    if (!date_is_valid(date)) {
        printf("Invalid date: %d-%02d-%02d\n", date->year, date->month, date->day);
        return;
    }
    
    printf("%04d-%02d-%02d\n", date->year, date->month, date->day);
}