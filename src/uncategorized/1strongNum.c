#include <stdio.h>

int pow(int, int);
int factorial(int);
int isStrongNum(int);
int maxStrongNum(int);

int main(void) {
	int iterations, number;

	(void)scanf("%d", &iterations);
	for (int i = 0; i < iterations; i++) {
		(void)scanf("%d", &number);
		printf("%d\n", maxStrongNum(number));
	}

	return 0;
}

int factorial(int n) {
	int result = 1;
	for (int i = n; i > 0; i--) {
		result *= i;
	}
	return result;
}

int pow(int base, int power) {
	if (power == 0) return 1;
	int result = base;

	for (int i = 1; i < power; i++) {
		result *= base;
	}
	return result;
}

int isStrongNum(int n) {
	int i = 0;
	int sum = 0;

	while (1) {
		int digitsToCheck = n / pow(10, i);
		if (digitsToCheck == 0) break;
		
		sum += factorial(digitsToCheck % 10);
		i++;
	}

	if (sum == n) return 1;
	return 0;
}
int maxStrongNum(int n) {
	int max = 0;
	for (int i = 0; i < n; i++) {
		if (isStrongNum(i) == 1 && (i > max)) {
			max = i;
		}
	}
	return max;
}