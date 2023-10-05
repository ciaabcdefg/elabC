#include <stdio.h>

int* newArray(int n) {
	int* arr = (int*)calloc(n, sizeof(int));
	if (arr == NULL) return NULL;

	return arr;
}

void swap(int* arr, int a, int b) {
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

void show(int* arr, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void sort(int* arr, int n) {
	for (int i = 1; i < n; i++) {
		for (int j = i; j >= 0; j--) {
			if (arr[j] < arr[j - 1]) {
				swap(arr, j, j - 1);
			}
		}
		show(arr, n);
	}
}

int main(void) {
	int n;
	(void)scanf("%d", &n);

	int* arr = newArray(n);

	for (int i = 0; i < n; i++) {
		(void)scanf("%d", arr + i);
	}

	sort(arr, n);

	return 0;
}