#include "date.h"
#include <stdio.h>
#include <assert.h>

void test_create_date() {
    Date date = create_date(2024, 2, 29);
    assert(date.year == 2024);
    assert(date.month == 2);
    assert(date.day == 29);
    printf("✓ test_create_date passed\n");
}

void test_is_leap_year() {
    assert(is_leap_year(2024) == 1);  // Leap year
    assert(is_leap_year(2023) == 0);  // Not leap year
    assert(is_leap_year(2000) == 1);  // Leap year (divisible by 400)
    assert(is_leap_year(1900) == 0);  // Not leap year (divisible by 100 but not 400)
    printf("✓ test_is_leap_year passed\n");
}

void test_days_in_month() {
    assert(days_in_month(2024, 1) == 31);   // January
    assert(days_in_month(2024, 2) == 29);   // February (leap year)
    assert(days_in_month(2023, 2) == 28);   // February (non-leap year)
    assert(days_in_month(2024, 4) == 30);   // April
    assert(days_in_month(2024, 12) == 31);  // December
    printf("✓ test_days_in_month passed\n");
}

void test_is_valid_date() {
    Date valid_date = create_date(2024, 2, 29);
    Date invalid_date = create_date(2023, 2, 29);  // Feb 29 in non-leap year
    Date invalid_month = create_date(2024, 13, 1); // Invalid month
    Date invalid_day = create_date(2024, 1, 32);   // Invalid day
    
    assert(is_valid_date(&valid_date) == 1);
    assert(is_valid_date(&invalid_date) == 0);
    assert(is_valid_date(&invalid_month) == 0);
    assert(is_valid_date(&invalid_day) == 0);
    printf("✓ test_is_valid_date passed\n");
}

void test_compare_dates() {
    Date date1 = create_date(2024, 1, 15);
    Date date2 = create_date(2024, 1, 15);  // Same date
    Date date3 = create_date(2024, 1, 16);  // Later date
    Date date4 = create_date(2023, 12, 31); // Earlier date
    
    assert(compare_dates(&date1, &date2) == 0);  // Equal
    assert(compare_dates(&date1, &date3) < 0);   // date1 earlier
    assert(compare_dates(&date1, &date4) > 0);   // date1 later
    printf("✓ test_compare_dates passed\n");
}

int main(void) {
    printf("Running Date Tests...\n");
    printf("====================\n\n");
    
    test_create_date();
    test_is_leap_year();
    test_days_in_month();
    test_is_valid_date();
    test_compare_dates();
    
    printf("\n✅ All tests passed successfully!\n");
    return 0;
}