#include <stdio.h>
#include <stdlib.h>

void findStats(int* nums, int n, double* avg, int* maxi, int* mini) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += nums[i];
	}
	*avg = sum / n;

	int max = -100;
	for (int i = 0; i < n; i++) {
		if (nums[i] > max) {
			max = nums[i];
		}
	}
	*maxi = max;

	int min = 100;
	for (int i = 0; i < n; i++) {
		if (nums[i] < min) {
			min = nums[i];
		}
	}
	*mini = min;
}

int main(void) {
	int n, i, maxi, mini;
	double avg;
	int* nums;

	(void)scanf("%d", &n);
	nums = (int*)malloc(sizeof(int) * n);

	for (i = 0; i < n; i++)
		(void)scanf("%d", nums + i);

	findStats(nums, n, &avg, &maxi, &mini);
	printf("%.2f %d %d", avg, maxi, mini);

	return 0;
}