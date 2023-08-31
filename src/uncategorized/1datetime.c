#include <stdio.h>

#define secondsPerYear 31536000
#define secondsPerLeapYear 31622400 
#define secondsPerDay 86400
#define secondsPerHour 3600
#define secondsPerMinute 60

char* months[12] = {
	"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP",
	"OCT", "NOV", "DEC"
};
char* weekdays[7] = {
	"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

typedef struct datetime {
	int date; // 1-31
	int month; // 1-12
	int year; // 1970++
	int dayOfWeek; // 0-6
	int hour; // 0-23
	int minute; // 0-59
	int second; // 0-59
} datetime_t;

datetime_t createDate(int);
void printDate(datatime_t);
int isLeapYear(int);
int getNextLeapYear(int);
int getMonthDays(int, int);

int main(void) {
	datetime_t inputDate;
	int timestamp;
	(void)scanf("%d", &timestamp);

	inputDate = createDate(timestamp);
	printDate(inputDate);

	return 0;
}

datetime_t createDate(int timestamp) {
	datetime_t date;
	date.year = 1970;
	date.month = 1;
	date.date = 1;
	date.dayOfWeek = 4;
	date.hour = 0;
	date.minute = 0;
	date.second = 0;

	while (1) {
		if (isLeapYear(date.year)) {
			if (timestamp < secondsPerLeapYear) {
				break;
			}
			timestamp -= secondsPerLeapYear;
			date.dayOfWeek = (date.dayOfWeek + 2) % 7;
		}
		else
		{
			if (timestamp < secondsPerYear) {
				break;
			}
			timestamp -= secondsPerYear;
			date.dayOfWeek = (date.dayOfWeek + 1) % 7;
		}
		date.year += 1;
	}

	for (int month = 1; month < 13; month++) {
		if (timestamp - getMonthDays(month, date.year) * secondsPerDay < 0) {
			date.month = month;
			break;
		}
		timestamp -= getMonthDays(month, date.year) * secondsPerDay;
		if (getMonthDays(month, date.year) == 31) {
			date.dayOfWeek = (date.dayOfWeek + 3) % 7;
		}
		else if (getMonthDays(month, date.year) == 30) {
			date.dayOfWeek = (date.dayOfWeek + 2) % 7;
		}
		else if (month == 2) {
			date.dayOfWeek = (date.dayOfWeek + (isLeapYear(date.year) ? 1 : 0)) % 7;
		}
	}

	int addedDays = (int)(timestamp / secondsPerDay);
	date.date += addedDays;
	date.dayOfWeek = (date.dayOfWeek + addedDays) % 7;
	timestamp -= addedDays * secondsPerDay;

	int addedHours = (int)(timestamp / secondsPerHour);
	date.hour += addedHours;
	timestamp -= addedHours * secondsPerHour;

	int addedMinutes = (int)(timestamp / secondsPerMinute);
	date.minute += addedMinutes;
	timestamp -= addedMinutes * secondsPerMinute;

	date.second = timestamp;

	return date;
}

void printDate(datetime_t date) {
	printf("%s %d %s %d %02d:%02d:%02d\n", weekdays[date.dayOfWeek],
		date.date, months[date.month - 1], date.year,
		date.hour, date.minute, date.second);
}

int isLeapYear(int year) {
	if (year % 4 != 0) return 0;
	else if (year % 100 != 0) return 1;
	else if (year % 400 != 0) return 0;

	return 1;
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
