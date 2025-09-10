#ifndef DATE_H
#define DATE_H

typedef struct {
    int year;
    int month;
    int day;
} Date;

Date create_date(int year, int month, int day);
int is_valid_date(const Date* date);
int compare_dates(const Date* date1, const Date* date2);
void print_date(const Date* date);
int is_leap_year(int year);
int days_in_month(int year, int month);

#endif