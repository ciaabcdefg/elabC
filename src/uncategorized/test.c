#include <stdio.h>

int tower_A = 0;
int tower_B = 0;
int tower_m = 0;

void move(char from, char to) {
	switch (from) {
	case 'A':
		tower_A--;
		break;
	case 'B':
		tower_B--;
		break;
	case 'm':
		tower_m--;
		break;
	}

	switch (to) {
	case 'A':
		tower_A++;
		break;
	case 'B':
		tower_B++;
		break;
	case 'm':
		tower_m++;
		break;
	}

	printf("%d, %d, %d\n", tower_A, tower_m, tower_B);
}

void tower(int n, char from, char to, char aug) {
	if (n == 1) {
		printf("Moved %d from %c to %c\n", n, from, to);
		move(from, to);

		return;
	}

	tower(n - 1, from, aug, to);
	move(from, aug);

	printf("Moved %d from %c to %c\n", n - 1, from, to);

	tower(n - 1, aug, to, from);
	move(aug, to);
}

int main(void) {
	int n = 3;
	tower_A = n;

	tower(n, 'A', 'B', 'm');

	return 0;
}