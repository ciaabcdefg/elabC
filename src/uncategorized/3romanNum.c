#include <stdio.h>

void roman(int);
int getDigit(int, int);
int pow(int, int);

int main(void) {
	int iterations;

	(void)scanf("%d", &iterations);

	for (int i = 0; i < iterations; i++) {
		int number;
		(void)scanf("%d", &number);

		roman(number);
	}

	return 0;
}

int pow(int base, int power) {
	if (power == 0) return 1;
	int result = base;

	for (int i = 1; i < power; i++) {
		result *= base;
	}
	return result;
}

int getDigit(int n, int position) {
	int tens = n / pow(10, position);
	if (tens == 0) return -1;

	return tens % 10;
}

void roman(int n) {
	int thousands = getDigit(n, 3);
	int hundreds = getDigit(n, 2);
	int tens = getDigit(n, 1);
	int ones = getDigit(n, 0);

	// M
	for (int i = 0; i < thousands; i++) {
		printf("%c", 'M');
	}

	// D, C
	if (hundreds >= 5 && hundreds <= 8) {
		printf("%c", 'D');

		for (int i = 0; i < (hundreds - 5); i++) {
			printf("%c", 'C');
		}
	}
	else if (hundreds == 9) {
		printf("%s", "CM");
	}
	else if (hundreds >= 1 && hundreds <= 3 ) {
		for (int i = 0; i < hundreds; i++) {
			printf("%c", 'C');
		}
	}
	else if (hundreds == 4) {
		printf("%s", "CD");
	}

	// L, X
	if (tens >= 5 && tens <= 8) {
		printf("%c", 'L');

		for (int i = 0; i < (tens - 5); i++) {
			printf("%c", 'X');
		}
	}
	else if (tens == 9) {
		printf("%s", "XC");
	}
	else if (tens >= 1 && tens <= 3) {
		for (int i = 0; i < tens; i++) {
			printf("%c", 'X');
		}
	}
	else if (tens == 4) {
		printf("%s", "XL");
	}

	// V, I

	if (ones >= 5 && ones <= 8) {
		printf("%c", 'V');

		for (int i = 0; i < (ones - 5); i++) {
			printf("%c", 'I');
		}
	}
	else if (ones == 9) {
		printf("%s", "IX");
	}
	else if (ones >= 1 && ones <= 3) {
		for (int i = 0; i < ones; i++) {
			printf("%c", 'I');
		}
	}
	else if (ones == 4) {
		printf("%s", "IV");
	}

	printf("\n");
}