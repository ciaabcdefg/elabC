#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	char input[16];
	fgets(input, 16, stdin);

	char* token = strtok(input, " ");
	int time = atoi(token);

	token = strtok(NULL, " ");
	int hours = atoi(token);

	int finalTime = (time + hours) % 24;
	int days = (time + hours) / 24;

	printf("%d %d\n", days, finalTime);

	return 0;
}