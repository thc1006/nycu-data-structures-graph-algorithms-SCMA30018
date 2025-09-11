#include "date.h"
#include <stdio.h>
#include <time.h>

void benchmark_date_validation() {
    clock_t start = clock();
    
    // Benchmark date validation
    for (int i = 0; i < 100000; i++) {
        Date date = create_date(2024, 2, 29);
        is_valid_date(&date);
    }
    
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Date validation benchmark: 100,000 operations took %f seconds\n", cpu_time_used);
}

void benchmark_date_comparison() {
    clock_t start = clock();
    
    Date date1 = create_date(2024, 1, 15);
    Date date2 = create_date(2024, 6, 20);
    
    // Benchmark date comparison
    for (int i = 0; i < 100000; i++) {
        compare_dates(&date1, &date2);
    }
    
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Date comparison benchmark: 100,000 operations took %f seconds\n", cpu_time_used);
}

void benchmark_leap_year_check() {
    clock_t start = clock();
    
    // Benchmark leap year checking
    for (int i = 1900; i < 2100; i++) {
        is_leap_year(i);
    }
    
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Leap year check benchmark: 200 years took %f seconds\n", cpu_time_used);
}

int main(void) {
    printf("Date Performance Benchmarks\n");
    printf("===========================\n\n");
    
    benchmark_date_validation();
    benchmark_date_comparison();
    benchmark_leap_year_check();
    
    printf("\n✅ Benchmarks completed!\n");
    return 0;
}