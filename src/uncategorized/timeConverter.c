#include <stdio.h>
#define SECONDS_PER_DAY (24 * 60 * 60)
#define SECONDS_PER_HOUR (60 * 60)
#define SECONDS_PER_MINUTE 60

int main(void) {
	unsigned int t;
	scanf("%d", &t);

	int days = t / SECONDS_PER_DAY;
	t -= days * SECONDS_PER_DAY;

	int hours = t / SECONDS_PER_HOUR;
	t -= hours * SECONDS_PER_HOUR;

	int minutes = t / SECONDS_PER_MINUTE;
	t -= minutes * SECONDS_PER_MINUTE;

	printf("%d %d %d %d\n", days, hours, minutes, t);

	return 0;
}