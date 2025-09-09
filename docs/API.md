# Date Type Documentation

## Overview

The Date data type is a comprehensive implementation of calendar date operations for the NYCU Data Structures & Graph Algorithms course (SCMA30018). It provides efficient and robust date handling capabilities with full validation and arithmetic operations.

## Data Structure

```c
typedef struct {
    int year;   /**< Year (e.g., 2024) */
    int month;  /**< Month (1-12) */
    int day;    /**< Day (1-31) */
} Date;
```

The Date structure uses a simple 3-integer representation, making it lightweight (12 bytes) and efficient for operations.

## API Reference

### Core Functions

#### `Date date_create(int year, int month, int day)`
Creates a new Date structure with the specified values.

**Parameters:**
- `year`: The year (positive integer)
- `month`: The month (1-12)
- `day`: The day (1-31, depending on month and year)

**Returns:** Date structure with the specified values

**Example:**
```c
Date birthday = date_create(2024, 9, 9);
```

#### `bool date_is_valid(const Date* date)`
Validates a date according to calendar rules.

**Parameters:**
- `date`: Pointer to the Date structure to validate

**Returns:** `true` if valid, `false` otherwise

**Validation Rules:**
- Year must be positive
- Month must be 1-12
- Day must be valid for the given month and year
- Accounts for leap years

**Example:**
```c
Date date = date_create(2024, 2, 29);  // Leap year
if (date_is_valid(&date)) {
    printf("Valid date!\n");
}
```

### Leap Year Functions

#### `bool date_is_leap_year(int year)`
Determines if a year is a leap year.

**Leap Year Rules:**
- Divisible by 4 AND not divisible by 100, OR
- Divisible by 400

**Example:**
```c
bool is_2024_leap = date_is_leap_year(2024);  // true
bool is_1900_leap = date_is_leap_year(1900);  // false
bool is_2000_leap = date_is_leap_year(2000);  // true
```

#### `int date_days_in_month(int year, int month)`
Returns the number of days in a specific month for a given year.

**Returns:** Number of days (28-31), or 0 for invalid month

### Date Comparison

#### `int date_compare(const Date* date1, const Date* date2)`
Compares two dates chronologically.

**Returns:**
- `-1` if date1 is earlier than date2
- `0` if dates are equal
- `1` if date1 is later than date2

**Example:**
```c
Date d1 = date_create(2024, 9, 9);
Date d2 = date_create(2024, 9, 10);
int result = date_compare(&d1, &d2);  // -1 (d1 is earlier)
```

### Date Arithmetic

#### `int date_diff_days(const Date* date1, const Date* date2)`
Calculates the difference in days between two dates.

**Returns:** Number of days (date2 - date1)

**Example:**
```c
Date start = date_create(2024, 9, 9);
Date end = date_create(2024, 9, 19);
int diff = date_diff_days(&start, &end);  // 10 days
```

#### `Date date_add_days(const Date* date, int days)`
Adds or subtracts days from a date.

**Parameters:**
- `date`: The original date
- `days`: Number of days to add (negative to subtract)

**Returns:** New Date structure with the result

**Example:**
```c
Date original = date_create(2024, 9, 9);
Date future = date_add_days(&original, 100);  // 2024-12-18
Date past = date_add_days(&original, -30);    // 2024-08-10
```

### String Conversion

#### `void date_to_string(const Date* date, char* buffer)`
Converts a date to ISO 8601 format (YYYY-MM-DD).

**Parameters:**
- `date`: The date to convert
- `buffer`: Buffer to store the result (minimum 11 characters)

#### `bool date_from_string(const char* str, Date* date)`
Parses a date from ISO 8601 format string.

**Parameters:**
- `str`: String in YYYY-MM-DD format
- `date`: Pointer to store the parsed date

**Returns:** `true` if parsing successful and date is valid

**Example:**
```c
char buffer[12];
Date date = date_create(2024, 9, 9);
date_to_string(&date, buffer);  // "2024-09-09"

Date parsed;
if (date_from_string("2024-12-25", &parsed)) {
    printf("Successfully parsed Christmas!\n");
}
```

### Utility Functions

#### `void date_print(const Date* date)`
Prints a date in readable format to stdout.

## Performance Characteristics

Based on benchmark results on a typical system:

| Operation | Performance | Notes |
|-----------|-------------|-------|
| Creation | ~153M ops/sec | Very fast, simple assignment |
| Validation | ~480M ops/sec | Efficient calendar checks |
| Comparison | ~393M ops/sec | Simple integer comparisons |
| Leap Year | ~438M ops/sec | Arithmetic operations only |
| Arithmetic | ~74M ops/sec | Complex date calculations |
| Difference | ~245K ops/sec | Most expensive operation |
| String Conv | ~9M ops/sec | sprintf-based formatting |
| String Parse | ~7.6M ops/sec | sscanf-based parsing |

## Memory Usage

- **Date structure**: 12 bytes (3 × 4-byte integers)
- **No dynamic allocation**: All operations use stack memory
- **Thread-safe**: No global state modifications

## Error Handling

The Date implementation follows these error handling principles:

1. **Validation**: Always use `date_is_valid()` before operations
2. **Null Safety**: Functions handle NULL pointers gracefully
3. **Return Codes**: Boolean functions indicate success/failure
4. **Defensive Programming**: Invalid inputs return safe default values

## Usage Examples

### Basic Date Operations
```c
#include "date.h"

// Create and validate a date
Date birthday = date_create(2024, 9, 9);
if (date_is_valid(&birthday)) {
    printf("Birthday is valid!\n");
    date_print(&birthday);
}

// Calculate age in days
Date today = date_create(2024, 12, 25);
int age_days = date_diff_days(&birthday, &today);
printf("Age in days: %d\n", age_days);
```

### Date Arithmetic
```c
// Project planning
Date project_start = date_create(2024, 9, 1);
Date milestone1 = date_add_days(&project_start, 30);  // 30 days later
Date milestone2 = date_add_days(&milestone1, 45);     // 45 days after that

printf("Project timeline:\n");
printf("Start: "); date_print(&project_start);
printf("Milestone 1: "); date_print(&milestone1);
printf("Milestone 2: "); date_print(&milestone2);
```

### String Processing
```c
// Reading dates from user input
char input[12];
printf("Enter date (YYYY-MM-DD): ");
scanf("%s", input);

Date user_date;
if (date_from_string(input, &user_date)) {
    printf("You entered: ");
    date_print(&user_date);
} else {
    printf("Invalid date format!\n");
}
```

## Algorithm Complexity

| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| Creation | O(1) | O(1) |
| Validation | O(1) | O(1) |
| Comparison | O(1) | O(1) |
| Leap Year | O(1) | O(1) |
| Add Days | O(n) where n = days | O(1) |
| Date Diff | O(y) where y = year difference | O(1) |
| String Conv | O(1) | O(1) |

## Limitations

1. **Year Range**: No explicit limits, but very large years may cause integer overflow
2. **Historical Dates**: No handling of calendar changes (e.g., Julian to Gregorian)
3. **Time Zones**: Dates only, no time or timezone support
4. **Locale**: No localized date formatting

## Future Enhancements

Potential improvements for advanced coursework:

1. **Time Support**: Add hour, minute, second fields
2. **Time Zones**: UTC and local time zone handling
3. **Formatting**: Customizable date format strings
4. **Serialization**: Binary serialization for storage
5. **Optimization**: Faster algorithms for large date ranges