/**
 * @file main.c
 * @brief Demonstration program for the Date data type
 * @author NYCU SCMA30018 Course
 * @date 2024
 * @license Apache-2.0
 */

#include "date.h"
#include <stdio.h>
#include <string.h>

void demonstrate_date_operations() {
    printf("=== NYCU Data Structures & Graph Algorithms - HW1 Date Type Demo ===\n\n");
    
    /* Create some dates */
    Date date1 = date_create(2024, 9, 9);
    Date date2 = date_create(2024, 12, 25);
    Date date3 = date_create(2024, 2, 29);  /* Leap year */
    Date invalid_date = date_create(2023, 2, 29);  /* Invalid - not leap year */
    
    printf("1. Date Creation and Validation:\n");
    printf("   Date 1: ");
    date_print(&date1);
    printf("   Valid: %s\n", date_is_valid(&date1) ? "Yes" : "No");
    
    printf("   Date 2: ");
    date_print(&date2);
    printf("   Valid: %s\n", date_is_valid(&date2) ? "Yes" : "No");
    
    printf("   Date 3 (leap year): ");
    date_print(&date3);
    printf("   Valid: %s\n", date_is_valid(&date3) ? "Yes" : "No");
    
    printf("   Invalid date: ");
    date_print(&invalid_date);
    printf("   Valid: %s\n", date_is_valid(&invalid_date) ? "Yes" : "No");
    
    printf("\n2. Leap Year Testing:\n");
    printf("   2024 is leap year: %s\n", date_is_leap_year(2024) ? "Yes" : "No");
    printf("   2023 is leap year: %s\n", date_is_leap_year(2023) ? "Yes" : "No");
    printf("   2000 is leap year: %s\n", date_is_leap_year(2000) ? "Yes" : "No");
    printf("   1900 is leap year: %s\n", date_is_leap_year(1900) ? "Yes" : "No");
    
    printf("\n3. Date Comparison:\n");
    int cmp = date_compare(&date1, &date2);
    printf("   Comparing ");
    date_print(&date1);
    printf("   with     ");
    date_print(&date2);
    printf("   Result: %d (%s)\n", cmp, 
           cmp < 0 ? "first is earlier" : 
           cmp > 0 ? "first is later" : "equal");
    
    printf("\n4. Date Arithmetic:\n");
    int diff = date_diff_days(&date1, &date2);
    printf("   Days between ");
    date_print(&date1);
    printf("   and          ");
    date_print(&date2);
    printf("   Difference: %d days\n", diff);
    
    Date future_date = date_add_days(&date1, 100);
    printf("   Adding 100 days to ");
    date_print(&date1);
    printf("   Result:             ");
    date_print(&future_date);
    
    Date past_date = date_add_days(&date2, -50);
    printf("   Subtracting 50 days from ");
    date_print(&date2);
    printf("   Result:                  ");
    date_print(&past_date);
    
    printf("\n5. String Conversion:\n");
    char date_str[12];
    date_to_string(&date1, date_str);
    printf("   Date to string: %s\n", date_str);
    
    Date parsed_date;
    if (date_from_string("2024-01-01", &parsed_date)) {
        printf("   Parsed from string '2024-01-01': ");
        date_print(&parsed_date);
    }
    
    printf("\n6. Days in Month Testing:\n");
    printf("   Days in February 2024 (leap): %d\n", date_days_in_month(2024, 2));
    printf("   Days in February 2023 (non-leap): %d\n", date_days_in_month(2023, 2));
    printf("   Days in December 2024: %d\n", date_days_in_month(2024, 12));
    
    printf("\n=== Demo Complete ===\n");
}

int main() {
    demonstrate_date_operations();
    return 0;
}