# Date API Documentation

## Overview
This document describes the Date API for the NYCU Data Structures & Graph Algorithms course project.

## Data Structure

### Date
```c
typedef struct {
    int year;
    int month;
    int day;
} Date;
```

## Functions

### `Date create_date(int year, int month, int day)`
Creates a new Date structure with the specified year, month, and day.

**Parameters:**
- `year`: The year (e.g., 2024)
- `month`: The month (1-12)
- `day`: The day of the month (1-31)

**Returns:** A Date structure with the specified values.

### `int is_valid_date(const Date* date)`
Checks if a date is valid according to calendar rules.

**Parameters:**
- `date`: Pointer to the Date structure to validate

**Returns:** 1 if valid, 0 if invalid.

### `int compare_dates(const Date* date1, const Date* date2)`
Compares two dates chronologically.

**Parameters:**
- `date1`: Pointer to the first Date
- `date2`: Pointer to the second Date

**Returns:** 
- Negative value if date1 is earlier than date2
- 0 if dates are equal
- Positive value if date1 is later than date2

### `void print_date(const Date* date)`
Prints a date in YYYY-MM-DD format.

**Parameters:**
- `date`: Pointer to the Date structure to print

### `int is_leap_year(int year)`
Determines if a given year is a leap year.

**Parameters:**
- `year`: The year to check

**Returns:** 1 if leap year, 0 otherwise.

### `int days_in_month(int year, int month)`
Returns the number of days in a given month of a given year.

**Parameters:**
- `year`: The year
- `month`: The month (1-12)

**Returns:** Number of days in the specified month.