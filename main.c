#include <stdio.h>
#include <stdlib.h>

struct Date {
    int day;
    int month;
    int year;
};

// Function declarations
int isLeapYear(int year);
int getDaysInMonth(int month, int year);
int getDayOfWeek(int d, int m, int y);
void printMonthCalendar(int month, int year);
void printFullYearCalendar(int year);
const char* getDayName(int dayOfWeek);

int main() {
    int choice;
    while (1) {
        printf("\n==== Simple Calendar App ====\n");
        printf("1. Check Leap Year\n");
        printf("2. Get Day of a Date\n");
        printf("3. Print Monthly Calendar\n");
        printf("4. Print Full Year Calendar\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int year;
            printf("Enter year: ");
            scanf("%d", &year);
            if (isLeapYear(year))
                printf("%d is a Leap Year ✅\n", year);
            else
                printf("%d is NOT a Leap Year ❌\n", year);

        } else if (choice == 2) {
            struct Date date;
            printf("Enter date (DD MM YYYY): ");
            scanf("%d %d %d", &date.day, &date.month, &date.year);
            int dow = getDayOfWeek(date.day, date.month, date.year);
            printf("The day is: %s\n", getDayName(dow));

        } else if (choice == 3) {
            int month, year;
            printf("Enter month and year (MM YYYY): ");
            scanf("%d %d", &month, &year);
            printMonthCalendar(month, year);

        } else if (choice == 4) {
            int year;
            printf("Enter year: ");
            scanf("%d", &year);
            printFullYearCalendar(year);

        } else if (choice == 5) {
            printf("Exiting... Goodbye!\n");
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

// Check leap year
int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Get number of days in a given month
int getDaysInMonth(int month, int year) {
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30,
                          31, 31, 30, 31, 30, 31 };
    if (month == 2 && isLeapYear(year))
        return 29;
    return daysInMonth[month - 1];
}

// Zeller’s Congruence Algorithm to get weekday
int getDayOfWeek(int d, int m, int y) {
    if (m < 3) {
        m += 12;
        y -= 1;
    }
    int k = y % 100;
    int j = y / 100;
    int f = d + 13 * (m + 1) / 5 + k + k / 4 + j / 4 + 5 * j;
    return f % 7; // 0 = Saturday, 1 = Sunday, ..., 6 = Friday
}

// Convert day number to name
const char* getDayName(int dayOfWeek) {
    const char* days[] = {
        "Saturday", "Sunday", "Monday", "Tuesday",
        "Wednesday", "Thursday", "Friday"
    };
    return days[dayOfWeek];
}

// Print calendar for a specific month
void printMonthCalendar(int month, int year) {
    const char* months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    printf("\n  ===== %s %d =====\n", months[month - 1], year);
    printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

    int startDay = (getDayOfWeek(1, month, year) - 1) % 7;
    int days = getDaysInMonth(month, year);

    int i;
    for (i = 0; i < startDay; i++)
        printf("     "); // Print empty slots

    for (int d = 1; d <= days; d++) {
        printf("%5d", d);
        if (++i % 7 == 0)
            printf("\n");
    }
    printf("\n");
}

// Print calendar for full year
void printFullYearCalendar(int year) {
    for (int month = 1; month <= 12; month++) {
        printMonthCalendar(month, year);
    }
}
