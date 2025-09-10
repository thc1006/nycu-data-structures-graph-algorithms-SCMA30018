#include "date.h"
#include <stdio.h>

int main() {
    printf("Date Demo Program\n");
    printf("=================\n\n");
    
    Date date1 = create_date(2024, 2, 29);
    Date date2 = create_date(2023, 2, 29);
    Date date3 = create_date(2024, 12, 25);
    
    printf("Date 1: ");
    print_date(&date1);
    printf(" - Valid: %s\n", is_valid_date(&date1) ? "Yes" : "No");
    
    printf("Date 2: ");
    print_date(&date2);
    printf(" - Valid: %s\n", is_valid_date(&date2) ? "Yes" : "No");
    
    printf("Date 3: ");
    print_date(&date3);
    printf(" - Valid: %s\n", is_valid_date(&date3) ? "Yes" : "No");
    
    printf("\nComparison results:\n");
    int cmp = compare_dates(&date1, &date3);
    printf("Date 1 vs Date 3: %s\n", 
           cmp < 0 ? "Date 1 is earlier" : 
           cmp > 0 ? "Date 1 is later" : "Dates are equal");
    
    printf("\nLeap year tests:\n");
    printf("2024 is leap year: %s\n", is_leap_year(2024) ? "Yes" : "No");
    printf("2023 is leap year: %s\n", is_leap_year(2023) ? "Yes" : "No");
    
    return 0;
}