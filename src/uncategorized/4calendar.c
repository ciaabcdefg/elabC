#include <stdio.h>

char* months[12] = {
	"January", "February", "March", "April", "May", "June", "July", "August", "September",
	"October", "November", "December"
};
char* weekdays[7] = {
	"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

int isLeapYear(int);
char* getMonthName(int);
int getMonthDays(int, int);

int main(void) {
	int _year = 1990;
	int _month = 1;
	int _day = 1;
	int _weekday = 1;
	int _elapsedDays = 0;

	int targetYear = 1996;
	int targetMonth = 3;

	printf("Enter year: "); (void)scanf("%d", &targetYear);
	printf("Enter month: "); (void)scanf("%d", &targetMonth);

	printf("====================\n");
	printf("%s %d\n", getMonthName(targetMonth), targetYear);
	printf("%3s %3s %3s %3s %3s %3s %3s\n", weekdays[0], weekdays[1], weekdays[2], weekdays[3], weekdays[4], weekdays[5], weekdays[6]);

	while (1) {
		if (_year == targetYear && _month == targetMonth && _day == 1) {
			break;
		}

		_day++;
		_elapsedDays++;
		_weekday = (_elapsedDays + 1) % 7;

		if (_day > getMonthDays(_month, _year)) {
			_day = 1;
			_month++;
		}
		if (_month > 12) {
			_month = 1;
			_year++;
		}
	}

	for (int i = 0; i < _weekday; i++) {
		printf("%3s ", "");
	}

	while (1) {
		if (_day > getMonthDays(_month, _year)) {
			break;
		}

		printf("%3d ", _day);

		_day++;
		_elapsedDays++;
		_weekday = (_elapsedDays + 1) % 7;
		if (_weekday == 0) {
			printf("\n");
		}
	}

	return 0;
}

int getMonthDays(int month, int year) {
	if (month == 2) {
		if (isLeapYear(year)) return 29;
		return 28;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11) {
		return 30;
	}
	return 31;
}

char* getMonthName(int month) {
	return months[month - 1];
}

int isLeapYear(int year) {
	if (year % 4 != 0) return 0;
	else if (year % 100 != 0) return 1;
	else if (year % 400 != 0) return 0;

	return 1;
}

