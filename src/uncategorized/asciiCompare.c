#include <stdio.h>
#include <string.h>

int main(void) {
	char input[10];
	fgets(input, 10, stdin);

	char* token = strtok(input, " ");
	char a = token[0];

	token = strtok(NULL, " ");
	char b = token[0];

	int difference = b - a;
	if (difference < 0) {
		difference *= -1;
	}

	printf("%d\n", difference);

	return 0;
}