/**
 * @file test_date.c
 * @brief Unit tests for the Date data type
 * @author NYCU SCMA30018 Course
 * @date 2024
 * @license Apache-2.0
 */

#include "date.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

/* Simple test framework */
static int tests_run = 0;
static int tests_passed = 0;

#define TEST_ASSERT(condition, message) do { \
    tests_run++; \
    if (condition) { \
        tests_passed++; \
        printf("✓ %s\n", message); \
    } else { \
        printf("✗ %s\n", message); \
    } \
} while(0)

void test_date_creation() {
    printf("\n=== Testing Date Creation ===\n");
    
    Date date1 = date_create(2024, 9, 9);
    TEST_ASSERT(date1.year == 2024 && date1.month == 9 && date1.day == 9, 
                "Date creation with valid values");
    
    Date date2 = date_create(0, 0, 0);
    TEST_ASSERT(date2.year == 0 && date2.month == 0 && date2.day == 0, 
                "Date creation with zero values");
}

void test_date_validation() {
    printf("\n=== Testing Date Validation ===\n");
    
    Date valid_date = date_create(2024, 9, 9);
    TEST_ASSERT(date_is_valid(&valid_date), "Valid date validation");
    
    Date invalid_month = date_create(2024, 13, 9);
    TEST_ASSERT(!date_is_valid(&invalid_month), "Invalid month (13) validation");
    
    Date invalid_day = date_create(2024, 9, 31);
    TEST_ASSERT(!date_is_valid(&invalid_day), "Invalid day (31 in September) validation");
    
    Date feb_29_leap = date_create(2024, 2, 29);
    TEST_ASSERT(date_is_valid(&feb_29_leap), "February 29 in leap year validation");
    
    Date feb_29_non_leap = date_create(2023, 2, 29);
    TEST_ASSERT(!date_is_valid(&feb_29_non_leap), "February 29 in non-leap year validation");
    
    TEST_ASSERT(!date_is_valid(NULL), "NULL date validation");
}

void test_leap_year() {
    printf("\n=== Testing Leap Year ===\n");
    
    TEST_ASSERT(date_is_leap_year(2024), "2024 is leap year");
    TEST_ASSERT(!date_is_leap_year(2023), "2023 is not leap year");
    TEST_ASSERT(date_is_leap_year(2000), "2000 is leap year (divisible by 400)");
    TEST_ASSERT(!date_is_leap_year(1900), "1900 is not leap year (divisible by 100 but not 400)");
    TEST_ASSERT(date_is_leap_year(1600), "1600 is leap year");
    TEST_ASSERT(!date_is_leap_year(1700), "1700 is not leap year");
}

void test_days_in_month() {
    printf("\n=== Testing Days in Month ===\n");
    
    TEST_ASSERT(date_days_in_month(2024, 1) == 31, "January has 31 days");
    TEST_ASSERT(date_days_in_month(2024, 2) == 29, "February in leap year has 29 days");
    TEST_ASSERT(date_days_in_month(2023, 2) == 28, "February in non-leap year has 28 days");
    TEST_ASSERT(date_days_in_month(2024, 4) == 30, "April has 30 days");
    TEST_ASSERT(date_days_in_month(2024, 12) == 31, "December has 31 days");
    TEST_ASSERT(date_days_in_month(2024, 13) == 0, "Invalid month returns 0");
    TEST_ASSERT(date_days_in_month(2024, 0) == 0, "Invalid month (0) returns 0");
}

void test_date_comparison() {
    printf("\n=== Testing Date Comparison ===\n");
    
    Date date1 = date_create(2024, 9, 9);
    Date date2 = date_create(2024, 9, 10);
    Date date3 = date_create(2024, 9, 9);
    Date date4 = date_create(2025, 1, 1);
    
    TEST_ASSERT(date_compare(&date1, &date2) == -1, "Earlier date comparison");
    TEST_ASSERT(date_compare(&date2, &date1) == 1, "Later date comparison");
    TEST_ASSERT(date_compare(&date1, &date3) == 0, "Equal date comparison");
    TEST_ASSERT(date_compare(&date1, &date4) == -1, "Different year comparison");
    TEST_ASSERT(date_compare(NULL, &date1) == 0, "NULL date comparison");
}

void test_date_arithmetic() {
    printf("\n=== Testing Date Arithmetic ===\n");
    
    Date date1 = date_create(2024, 9, 9);
    Date date2 = date_create(2024, 9, 19);
    
    int diff = date_diff_days(&date1, &date2);
    TEST_ASSERT(diff == 10, "Date difference calculation (10 days)");
    
    diff = date_diff_days(&date2, &date1);
    TEST_ASSERT(diff == -10, "Reverse date difference calculation (-10 days)");
    
    Date same_date = date_create(2024, 9, 9);
    diff = date_diff_days(&date1, &same_date);
    TEST_ASSERT(diff == 0, "Same date difference (0 days)");
    
    /* Test adding days */
    Date result = date_add_days(&date1, 10);
    TEST_ASSERT(result.year == 2024 && result.month == 9 && result.day == 19, 
                "Adding 10 days");
    
    result = date_add_days(&date1, 0);
    TEST_ASSERT(result.year == 2024 && result.month == 9 && result.day == 9, 
                "Adding 0 days");
    
    /* Test month boundary */
    Date end_month = date_create(2024, 9, 30);
    result = date_add_days(&end_month, 1);
    TEST_ASSERT(result.year == 2024 && result.month == 10 && result.day == 1, 
                "Adding days across month boundary");
    
    /* Test year boundary */
    Date end_year = date_create(2024, 12, 31);
    result = date_add_days(&end_year, 1);
    TEST_ASSERT(result.year == 2025 && result.month == 1 && result.day == 1, 
                "Adding days across year boundary");
    
    /* Test subtracting days */
    result = date_add_days(&date2, -10);
    TEST_ASSERT(result.year == 2024 && result.month == 9 && result.day == 9, 
                "Subtracting 10 days");
}

void test_string_conversion() {
    printf("\n=== Testing String Conversion ===\n");
    
    Date date = date_create(2024, 9, 9);
    char buffer[12];
    date_to_string(&date, buffer);
    TEST_ASSERT(strcmp(buffer, "2024-09-09") == 0, "Date to string conversion");
    
    Date parsed_date;
    bool success = date_from_string("2024-12-25", &parsed_date);
    TEST_ASSERT(success && parsed_date.year == 2024 && parsed_date.month == 12 && parsed_date.day == 25, 
                "String to date parsing");
    
    success = date_from_string("invalid-date", &parsed_date);
    TEST_ASSERT(!success, "Invalid string parsing returns false");
    
    success = date_from_string("2023-02-29", &parsed_date);
    TEST_ASSERT(!success, "Invalid date string parsing returns false");
    
    date_to_string(NULL, buffer);
    date_from_string(NULL, &parsed_date);
    TEST_ASSERT(true, "NULL parameter handling (no crash)");
}

void test_edge_cases() {
    printf("\n=== Testing Edge Cases ===\n");
    
    /* Test leap year boundaries */
    Date leap_date = date_create(2024, 2, 29);
    Date result = date_add_days(&leap_date, 1);
    TEST_ASSERT(result.year == 2024 && result.month == 3 && result.day == 1, 
                "Leap year February 29 + 1 day");
    
    /* Test large date differences */
    Date date1 = date_create(2024, 1, 1);
    Date date2 = date_create(2025, 1, 1);
    int diff = date_diff_days(&date1, &date2);
    TEST_ASSERT(diff == 366, "One leap year difference (366 days)");
    
    /* Test negative year (edge case) */
    Date negative_year = date_create(-1, 1, 1);
    TEST_ASSERT(!date_is_valid(&negative_year), "Negative year is invalid");
}

int main() {
    printf("NYCU Data Structures & Graph Algorithms - Date Type Unit Tests\n");
    printf("===============================================================\n");
    
    test_date_creation();
    test_date_validation();
    test_leap_year();
    test_days_in_month();
    test_date_comparison();
    test_date_arithmetic();
    test_string_conversion();
    test_edge_cases();
    
    printf("\n=== Test Results ===\n");
    printf("Tests run: %d\n", tests_run);
    printf("Tests passed: %d\n", tests_passed);
    printf("Tests failed: %d\n", tests_run - tests_passed);
    printf("Success rate: %.1f%%\n", (tests_passed * 100.0) / tests_run);
    
    if (tests_passed == tests_run) {
        printf("🎉 All tests passed!\n");
        return 0;
    } else {
        printf("❌ Some tests failed!\n");
        return 1;
    }
}