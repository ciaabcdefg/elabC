#include <stdio.h>

void northArrow(int);
void southArrow(int);
void eastArrow(int);
void westArrow(int);

int main(void) {
	char dir = 'E';
	int size = 2;

	(void)scanf("%c %d", &dir, &size);

	switch (dir) {
	case ('N'):
		northArrow(size);
		break;
	case ('S'):
		southArrow(size);
		break;
	case ('E'):
		eastArrow(size);
		break;
	case ('W'):
		westArrow(size);
		break;
	}

	return 0;
}

void northArrow(int size) {
	// HEAD
	for (int y = 0; y < (size + 1); y++) {
		for (int i = 0; i < (size - y); i++) {
			printf("%c", ' ');
		}
		for (int i = 0; i < (2 * (y + 1) - 1); i++) {
			printf("%c", '#');
		}
		printf("\n");
	}

	// TAIL
	for (int y = 0; y < (size + 1); y++) {
		printf(" ");
		for (int i = 0; i < (2 * size - 1); i++) {
			printf("#");
		}
		printf("\n");
	}
}
void southArrow(int size) {
	// TAIL
	for (int y = 0; y < (size + 1); y++) {
		printf(" ");
		for (int i = 0; i < (2 * size - 1); i++) {
			printf("#");
		}
		printf("\n");
	}

	// HEAD
	for (int y = size; y >= 0; y--) {
		for (int i = 0; i < (size - y); i++) {
			printf("%c", ' ');
		}
		for (int i = 0; i < (2 * (y + 1) - 1); i++) {
			printf("%c", '#');
		}
		printf("\n");
	}
}
void eastArrow(int size) {
	// TOP HALF
	for (int y = 0; y < (size + 1); y++) {
		for (int i = 0; i < (size + 1); i++) {
			if (y == 0)
				printf(" ");
			else
				printf("#");
		}

		for (int i = 0; i < (y + 1); i++) {
			printf("#");
		}

		printf("\n");
	}

	// BOTTOM HALF
	for (int y = 0; y < (size); y++) {
		for (int i = 0; i < (size + 1); i++) {
			if (y == size - 1)
				printf(" ");
			else
				printf("#");
		}

		for (int i = size; i >= y + 1; i--) {
			printf("#");
		}

		printf("\n");
	}
}
void westArrow(int size) {
	// TOP HALF
	for (int y = 0; y < (size + 1); y++) {
		for (int i = 0; i < size - y; i++) {
			printf(" ");
		}
		for (int i = 0; i < (y + 1); i++) {
			printf("#");
		}

		for (int i = 0; i < (size + 1); i++) {
			if (y == 0)
				printf(" ");
			else
				printf("#");
		}

		printf("\n");
	}

	// BOTTOM HALF
	for (int y = size - 1; y >= 0; y--) {
		for (int i = 0; i < size - y; i++) {
			printf(" ");
		}
		for (int i = 0; i < (y + 1); i++) {
			printf("#");
		}

		for (int i = 0; i < (size + 1); i++) {
			if (y == 0)
				printf(" ");
			else
				printf("#");
		}

		printf("\n");
	}
}