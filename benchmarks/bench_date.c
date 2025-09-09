/**
 * @file bench_date.c
 * @brief Performance benchmarks for the Date data type
 * @author NYCU SCMA30018 Course
 * @date 2024
 * @license Apache-2.0
 */

#include "date.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define BENCHMARK_ITERATIONS 1000000

/* Simple timing utility */
static double get_time_diff(clock_t start, clock_t end) {
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

void benchmark_date_creation() {
    printf("Benchmarking date creation (%d iterations)...\n", BENCHMARK_ITERATIONS);
    
    clock_t start = clock();
    
    for (int i = 0; i < BENCHMARK_ITERATIONS; i++) {
        Date date = date_create(2024, (i % 12) + 1, (i % 28) + 1);
        (void)date; /* Suppress unused variable warning */
    }
    
    clock_t end = clock();
    double elapsed = get_time_diff(start, end);
    
    printf("  Time: %.6f seconds\n", elapsed);
    printf("  Operations per second: %.0f\n", BENCHMARK_ITERATIONS / elapsed);
}

void benchmark_date_validation() {
    printf("\nBenchmarking date validation (%d iterations)...\n", BENCHMARK_ITERATIONS);
    
    /* Pre-create dates to avoid measuring creation time */
    Date* dates = malloc(BENCHMARK_ITERATIONS * sizeof(Date));
    for (int i = 0; i < BENCHMARK_ITERATIONS; i++) {
        dates[i] = date_create(2024, (i % 12) + 1, (i % 28) + 1);
    }
    
    clock_t start = clock();
    
    int valid_count = 0;
    for (int i = 0; i < BENCHMARK_ITERATIONS; i++) {
        if (date_is_valid(&dates[i])) {
            valid_count++;
        }
    }
    
    clock_t end = clock();
    double elapsed = get_time_diff(start, end);
    
    printf("  Time: %.6f seconds\n", elapsed);
    printf("  Operations per second: %.0f\n", BENCHMARK_ITERATIONS / elapsed);
    printf("  Valid dates: %d\n", valid_count);
    
    free(dates);
}

void benchmark_date_comparison() {
    printf("\nBenchmarking date comparison (%d iterations)...\n", BENCHMARK_ITERATIONS);
    
    Date date1 = date_create(2024, 6, 15);
    Date date2 = date_create(2024, 6, 16);
    
    clock_t start = clock();
    
    int comparison_results = 0;
    for (int i = 0; i < BENCHMARK_ITERATIONS; i++) {
        comparison_results += date_compare(&date1, &date2);
    }
    
    clock_t end = clock();
    double elapsed = get_time_diff(start, end);
    
    printf("  Time: %.6f seconds\n", elapsed);
    printf("  Operations per second: %.0f\n", BENCHMARK_ITERATIONS / elapsed);
    printf("  Total comparison results: %d\n", comparison_results);
}

void benchmark_date_arithmetic() {
    printf("\nBenchmarking date arithmetic (%d iterations)...\n", BENCHMARK_ITERATIONS / 10);
    
    Date base_date = date_create(2024, 6, 15);
    
    clock_t start = clock();
    
    for (int i = 0; i < BENCHMARK_ITERATIONS / 10; i++) {
        Date result = date_add_days(&base_date, i % 365);
        (void)result; /* Suppress unused variable warning */
    }
    
    clock_t end = clock();
    double elapsed = get_time_diff(start, end);
    
    printf("  Time: %.6f seconds\n", elapsed);
    printf("  Operations per second: %.0f\n", (BENCHMARK_ITERATIONS / 10) / elapsed);
}

void benchmark_date_diff() {
    printf("\nBenchmarking date difference calculation (%d iterations)...\n", BENCHMARK_ITERATIONS / 100);
    
    Date date1 = date_create(2024, 1, 1);
    Date date2 = date_create(2024, 12, 31);
    
    clock_t start = clock();
    
    int total_diff = 0;
    for (int i = 0; i < BENCHMARK_ITERATIONS / 100; i++) {
        total_diff += date_diff_days(&date1, &date2);
    }
    
    clock_t end = clock();
    double elapsed = get_time_diff(start, end);
    
    printf("  Time: %.6f seconds\n", elapsed);
    printf("  Operations per second: %.0f\n", (BENCHMARK_ITERATIONS / 100) / elapsed);
    printf("  Total differences calculated: %d\n", total_diff);
}

void benchmark_string_conversion() {
    printf("\nBenchmarking string conversion (%d iterations)...\n", BENCHMARK_ITERATIONS / 10);
    
    Date date = date_create(2024, 9, 9);
    char buffer[12];
    
    clock_t start = clock();
    
    for (int i = 0; i < BENCHMARK_ITERATIONS / 10; i++) {
        date_to_string(&date, buffer);
    }
    
    clock_t end = clock();
    double elapsed = get_time_diff(start, end);
    
    printf("  Time: %.6f seconds\n", elapsed);
    printf("  Operations per second: %.0f\n", (BENCHMARK_ITERATIONS / 10) / elapsed);
    
    /* Benchmark string parsing */
    printf("\nBenchmarking string parsing (%d iterations)...\n", BENCHMARK_ITERATIONS / 10);
    
    start = clock();
    
    Date parsed_date;
    int successful_parses = 0;
    for (int i = 0; i < BENCHMARK_ITERATIONS / 10; i++) {
        if (date_from_string("2024-09-09", &parsed_date)) {
            successful_parses++;
        }
    }
    
    end = clock();
    elapsed = get_time_diff(start, end);
    
    printf("  Time: %.6f seconds\n", elapsed);
    printf("  Operations per second: %.0f\n", (BENCHMARK_ITERATIONS / 10) / elapsed);
    printf("  Successful parses: %d\n", successful_parses);
}

void benchmark_leap_year() {
    printf("\nBenchmarking leap year calculation (%d iterations)...\n", BENCHMARK_ITERATIONS);
    
    clock_t start = clock();
    
    int leap_years = 0;
    for (int i = 0; i < BENCHMARK_ITERATIONS; i++) {
        if (date_is_leap_year(1900 + (i % 200))) {
            leap_years++;
        }
    }
    
    clock_t end = clock();
    double elapsed = get_time_diff(start, end);
    
    printf("  Time: %.6f seconds\n", elapsed);
    printf("  Operations per second: %.0f\n", BENCHMARK_ITERATIONS / elapsed);
    printf("  Leap years found: %d\n", leap_years);
}

void run_comprehensive_benchmark() {
    printf("\nRunning comprehensive mixed operations benchmark...\n");
    printf("Testing realistic usage patterns (%d mixed operations)...\n", BENCHMARK_ITERATIONS / 100);
    
    clock_t start = clock();
    
    for (int i = 0; i < BENCHMARK_ITERATIONS / 100; i++) {
        /* Create dates */
        Date date1 = date_create(2024, (i % 12) + 1, (i % 28) + 1);
        Date date2 = date_create(2024, ((i + 6) % 12) + 1, ((i + 15) % 28) + 1);
        
        /* Validate */
        bool valid1 = date_is_valid(&date1);
        bool valid2 = date_is_valid(&date2);
        
        if (valid1 && valid2) {
            /* Compare */
            int cmp = date_compare(&date1, &date2);
            
            /* Calculate difference */
            int diff = date_diff_days(&date1, &date2);
            
            /* Add some days */
            Date result = date_add_days(&date1, abs(diff) % 100);
            
            /* Convert to string */
            char buffer[12];
            date_to_string(&result, buffer);
            
            /* Suppress unused variable warnings */
            (void)cmp;
            (void)result;
        }
    }
    
    clock_t end = clock();
    double elapsed = get_time_diff(start, end);
    
    printf("  Time: %.6f seconds\n", elapsed);
    printf("  Mixed operations per second: %.0f\n", (BENCHMARK_ITERATIONS / 100) / elapsed);
}

int main() {
    printf("NYCU Data Structures & Graph Algorithms - Date Type Performance Benchmarks\n");
    printf("=========================================================================\n\n");
    
    printf("System information:\n");
    printf("  CLOCKS_PER_SEC: %ld\n", CLOCKS_PER_SEC);
    printf("  sizeof(Date): %zu bytes\n\n", sizeof(Date));
    
    benchmark_date_creation();
    benchmark_date_validation();
    benchmark_date_comparison();
    benchmark_leap_year();
    benchmark_date_arithmetic();
    benchmark_date_diff();
    benchmark_string_conversion();
    run_comprehensive_benchmark();
    
    printf("\n=== Benchmark Complete ===\n");
    printf("Note: Performance may vary based on system specifications and load.\n");
    printf("These benchmarks provide relative performance comparisons.\n");
    
    return 0;
}