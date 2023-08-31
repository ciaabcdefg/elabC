#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	char a[4096];
	char b[4096];

	(void)scanf("%s", &a);
	(void)scanf("%s", &b);

	char* x;
	char* y;

	char* ans;

	int xLength = strlen(a);
	int yLength = strlen(b);
	int ansLength = xLength + yLength;

	x = (char*)calloc(ansLength, sizeof(x));
	if (x == NULL) return 0;

	y = (char*)calloc(ansLength, sizeof(y));
	if (y == NULL) return 0;

	ans = (char*)calloc(ansLength, sizeof(ans));
	if (ans == NULL) return 0;

	memset(x, '0', yLength);
	strcpy(x + yLength, a);

	memset(y, '0', xLength);
	strcpy(y + xLength, b);

	int carry = 0;
	for (int _ = 0; _ < ansLength; _++) {
		int i = ansLength - _ - 1;

		int xDigit = x[i] - '0';
		int yDigit = y[i] - '0';
		int result = xDigit + yDigit + carry;

		if (result >= 10) {
			carry = 1;
			result = result % 10;
		}
		else {
			carry = 0;
		}

		memset(ans + _, '0' + result, 1);
	}

	int started = 0;

	for (int _ = 0; _ < ansLength; _++) {
		int i = ansLength - _ - 1;
		if (ans[i] != '0') started = 1;
		if (!started) continue;

		printf("%c", ans[i]);
	}

	return 0;
}