#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	// FIRST LINE
	char input[32];
	fgets(input, 32, stdin);

	char* token = strtok(input, " ");
	int x = atoi(token);

	token = strtok(NULL, " ");
	int y = atoi(token);

	token = strtok(NULL, " ");
	int z = atoi(token);

	// SECOND LINE
	fgets(input, 32, stdin);

	token = strtok(input, " ");
	char hungry = token[0];

	token = strtok(NULL, " ");
	char sick = token[0];

	// CALCULATIONS
	float temporary = x;

	if (hungry == 'y' || hungry == 'Y') {
		//x += y;
		temporary += y;
	}
	if (sick == 'y' || sick == 'Y') {
		//x = (float)x / z;
		temporary = (float)temporary / z;
	}

	if ((temporary - (int)temporary) > 0) {
		temporary = (int)temporary + 1;
	}

	printf("%.0f\n", temporary);

	return 0;
}