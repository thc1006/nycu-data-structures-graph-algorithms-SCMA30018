/**
 * @file date.h
 * @brief Date data structure implementation for NYCU Data Structures & Graph Algorithms
 * @author NYCU SCMA30018 Course
 * @date 2024
 * @license Apache-2.0
 */

#ifndef DATE_H
#define DATE_H

#include <stdbool.h>

/**
 * @brief Date structure representing a calendar date
 */
typedef struct {
    int year;   /**< Year (e.g., 2024) */
    int month;  /**< Month (1-12) */
    int day;    /**< Day (1-31) */
} Date;

/**
 * @brief Create a new date
 * @param year The year
 * @param month The month (1-12)
 * @param day The day (1-31)
 * @return Date structure
 */
Date date_create(int year, int month, int day);

/**
 * @brief Check if a date is valid
 * @param date The date to validate
 * @return true if valid, false otherwise
 */
bool date_is_valid(const Date* date);

/**
 * @brief Check if a year is a leap year
 * @param year The year to check
 * @return true if leap year, false otherwise
 */
bool date_is_leap_year(int year);

/**
 * @brief Get the number of days in a month
 * @param year The year
 * @param month The month (1-12)
 * @return Number of days in the month
 */
int date_days_in_month(int year, int month);

/**
 * @brief Compare two dates
 * @param date1 First date
 * @param date2 Second date
 * @return -1 if date1 < date2, 0 if equal, 1 if date1 > date2
 */
int date_compare(const Date* date1, const Date* date2);

/**
 * @brief Calculate the difference in days between two dates
 * @param date1 First date
 * @param date2 Second date
 * @return Number of days between dates (date2 - date1)
 */
int date_diff_days(const Date* date1, const Date* date2);

/**
 * @brief Add days to a date
 * @param date The original date
 * @param days Number of days to add
 * @return New date after adding days
 */
Date date_add_days(const Date* date, int days);

/**
 * @brief Convert date to string format (YYYY-MM-DD)
 * @param date The date to convert
 * @param buffer Buffer to store the string (minimum 11 characters)
 */
void date_to_string(const Date* date, char* buffer);

/**
 * @brief Parse date from string format (YYYY-MM-DD)
 * @param str The string to parse
 * @param date Pointer to store the parsed date
 * @return true if parsing successful, false otherwise
 */
bool date_from_string(const char* str, Date* date);

/**
 * @brief Print date in readable format
 * @param date The date to print
 */
void date_print(const Date* date);

#endif /* DATE_H */