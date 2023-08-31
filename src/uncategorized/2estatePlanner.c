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

	/*
	int slice1sizeA = 0;
	int slice1sizeB = 0;
	int slice2sizeA = 0;
	int slice2sizeB = 0;
	*/

	for (int i = 1; i <= b; i *= 2) {
		sliceSize = i;
	}

	/*
	slice1sizeA = sliceSize;
	slice1sizeB = a - sliceSize;

	slice2sizeA = a;
	slice2sizeB = b - sliceSize;
	*/

	//return 1 + estatePlanner(slice1sizeA, slice1sizeB) + estatePlanner(slice2sizeA, slice2sizeB);
	return 1 + estatePlanner(sliceSize, a - sliceSize) + estatePlanner(a, b - sliceSize);
}

// 