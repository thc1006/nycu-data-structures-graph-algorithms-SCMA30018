#include "date.h"
#include <stdio.h>

Date create_date(int year, int month, int day) {
    Date date = {year, month, day};
    return date;
}

int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int days_in_month(int year, int month) {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && is_leap_year(year)) {
        return 29;
    }
    return days[month - 1];
}

int is_valid_date(const Date* date) {
    if (date->year < 1 || date->month < 1 || date->month > 12 || date->day < 1) {
        return 0;
    }
    return date->day <= days_in_month(date->year, date->month);
}

int compare_dates(const Date* date1, const Date* date2) {
    if (date1->year != date2->year) {
        return date1->year - date2->year;
    }
    if (date1->month != date2->month) {
        return date1->month - date2->month;
    }
    return date1->day - date2->day;
}

void print_date(const Date* date) {
    printf("%04d-%02d-%02d", date->year, date->month, date->day);
}