#include <stdio.h>

int isPrime(int n) {
	if (n == 0 || n == 1) {
		return 0;
	}

	for (int i = 2; i*i <= n; i++) {
		if (n % i == 0) {
			return 0;
		}
	}
	
	return 1;
}

int main(void) {
	int n = 0;
	(void)scanf("%d", &n);

	printf("%d", isPrime(n));

	return 0;
}

// O(sqrt(n))