#include <iostream>
#include <iomanip>
#include <ctime>

class Calendar {
public:
    Calendar(int initialYear, int initialMonth) {
        setCurrentDate(initialYear, initialMonth, 1);
    }

    void setCurrentDate(int year, int month, int day) {
        struct tm newDate = {0};
        newDate.tm_year = year - 1900;
        newDate.tm_mon = month - 1;
        newDate.tm_mday = day;

        std::mktime(&newDate);

        currentDate = newDate;
    }

    void displayCurrentMonth() {
        std::cout << "====================\n";
        std::cout << "    " << getMonthName(currentDate.tm_mon) << " " << (currentDate.tm_year + 1900) << "\n";
        std::cout << "====================\n";

        std::cout << "Su Mo Tu We Th Fr Sa\n";

        int daysInMonth = getDaysInMonth(currentDate.tm_year, currentDate.tm_mon);
        int startingDay = getStartingDayOfWeek(currentDate.tm_year, currentDate.tm_mon);

        int dayCounter = 1;
        for (int i = 0; i < startingDay; ++i) {
            std::cout << "   ";
        }

        for (int day = 1; day <= daysInMonth; ++day) {
            std::cout << std::setw(2) << day << " ";

            if ((day + startingDay) % 7 == 0 || day == daysInMonth) {
                std::cout << "\n";
            }
        }
    }

    void navigateToNextMonth() {
        if (currentDate.tm_mon == 11) {
            setCurrentDate(currentDate.tm_year + 1, 1, 1);
        } else {
            setCurrentDate(currentDate.tm_year, currentDate.tm_mon + 2, 1);
        }
    }

    void navigateToPreviousMonth() {
        if (currentDate.tm_mon == 0) {
            setCurrentDate(currentDate.tm_year - 1, 12, 1);
        } else {
            setCurrentDate(currentDate.tm_year, currentDate.tm_mon, 1);
        }
    }

private:
    struct tm currentDate;

    std::string getMonthName(int month) {
        const std::string monthNames[] = {
            "January", "February", "March", "April",
            "May", "June", "July", "August",
            "September", "October", "November", "December"
        };
        return monthNames[month];
    }

    int getDaysInMonth(int year, int month) {
        const int daysInMonth[] = {
            31, 28, 31, 30,
            31, 30, 31, 31,
            30, 31, 30, 31
        };
        int days = daysInMonth[month];
        if (month == 1 && isLeapYear(year)) {
            days += 1;
        }
        return days;
    }

    bool isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    int getStartingDayOfWeek(int year, int month) {
        struct tm firstDay = {0};
        firstDay.tm_year = year;
        firstDay.tm_mon = month;
        firstDay.tm_mday = 1;
        std::mktime(&firstDay);
        return firstDay.tm_wday;
    }
};

int main() {
    int initialYear, initialMonth;
    std::cout << "Enter initial year and month (YYYY MM): ";
    std::cin >> initialYear >> initialMonth;

    Calendar calendar(initialYear, initialMonth);

    while (true) {
        calendar.displayCurrentMonth();

        std::cout << "\n1. Next Month\n";
        std::cout << "2. Previous Month\n";
        std::cout << "3. Exit\n";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            calendar.navigateToNextMonth();
        } else if (choice == 2) {
            calendar.navigateToPreviousMonth();
        } else if (choice == 3) {
            std::cout << "Exiting the calendar.\n";
            break;
        } else {
            std::cout << "Invalid choice. Please select again.\n";
        }
    }

    return 0;
}
