#include <stdio.h>

int estatePlanner(int, int);

int main(void) {
	int a = 0, b = 0;
	(void)scanf("%d %d", &a, &b);

	printf("%d", estatePlanner(a, b));

	return 0;
}

int estatePlanner(int a, int b) {
	if (a < b) {
		int temp = a;
		a = b;
		b = temp;
	}

	if (!(a && b)) {
		return 0;
	}
	if (b == 1) {
		return a;
	}

	int sliceSize = 0;

	for (int i = 1; i <= b; i *= 2) {
		sliceSize = i;
	}

	return 1 + estatePlanner(sliceSize, a - sliceSize) + estatePlanner(a, b - sliceSize);
}

// O(n): derived using the first case of the Master Theorem.
 
// In estatePlanner(int a, int b):
// T(n) = 2T(n/2) + log(n)

// Using the Master Theorem:
// a = 2, b = 2, f(n) = log(n) -> log(n) has a complexity of O(n^d) for 0 < d < 1
// n^(log2(2)) = n^1 = n
// 
// MASTER THEOREM: Case 1:
// f(n) = log(n) = O(n^(log2(2) - c)) for 0 < c < 1
// Therefore T(n) = O(n) or more precisely, BigTheta(n)
