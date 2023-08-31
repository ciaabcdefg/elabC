#include <stdio.h>
#include <stdlib.h>

int** createMaze(int);
int* fromIndex2D(int**, int, int, int);
void printMaze(int**, int);

void pattern1(int**, int);
void pattern2(int**, int);
void pattern3(int**, int);
void pattern4(int**, int);

enum direction {
	up,
	down,
	left,
	right,
	downRight,
	upLeft
};

int main() {
	int size;
	int pattern;

	(void)scanf("%d %d", &size, &pattern);

	int** maze = createMaze(size);
	
	switch (pattern) {
	case 1:
		pattern1(maze, size);
		break;
	case 2:
		pattern2(maze, size);
		break;
	case 3:
		pattern3(maze, size);
		break;
	case 4:
		pattern4(maze, size);
		break;
	}

	printMaze(maze, size);

	return 0;
}

void pattern1(int** maze, int size) {
	for (int j = 0; j < size; j++) {
		for (int i = 0; i < size; i++) {
			*fromIndex2D(maze, size, i, j) = size * j + (i + 1);
		}
	}
}

void pattern2(int** maze, int size) {
	int direction = 1;
	int number = 1;

	for (int j = 0; j < size; j++) {
		if (direction == 1) {
			for (int i = 0; i < size; i++) {
				*fromIndex2D(maze, size, i, j) = number;
				number += 1;
			}
		}
		else {
			for (int i = size - 1; i >= 0; i--) {
				*fromIndex2D(maze, size, i, j) = number;
				number += 1;
			}
		}

		direction *= -1;
	}
}

void pattern3(int** maze, int size) {
	int phase = 0;
	int variant = size % 2 == 0 ? 1 : 0;

	int velocityX = 0;
	int velocityY = 0;

	int x = 0;
	int y = size - 1;

	enum direction dir = up;

	int number = 1;

	while (1) {
		*fromIndex2D(maze, size, y, x) = number;

		if (x == size - 1 && y == 0) {
			break;
		}

		switch (dir) {
		case up:
			velocityX = 0, velocityY = -1;
			break;
		case downRight:
			velocityX = 1, velocityY = 1;
			break;
		case right:
			velocityX = 1, velocityY = 0;
			break;
		case upLeft:
			velocityX = -1, velocityY = -1;
			break;
		}
		x += velocityX;
		y += velocityY;

		number++;

		if (phase == 0) {
			if (x == 0 && y == 0) {
				if (variant == 0) {
					phase = 1;
					dir = right;
				}
				else {
					phase = 1;
					dir = downRight;
				}
				continue;
			}

			if (y == size - 1 && dir == downRight) {
				dir = right;
			}
			else if (x == 0 && dir == upLeft) {
				dir = up;
			}
			else if (dir == up) {
				dir = downRight;
			}
			else if (dir == right) {
				dir = upLeft;
			}
		}
		else {
			if (variant == 0) {
				if (x == size - 1 && dir == downRight) {
					dir = up;
				}
				else if (y == 0 && dir == upLeft) {
					dir = right;
				}
				else if (dir == right) {
					dir = downRight;
				}
				else if (dir == up) {
					dir = upLeft;
				}
			}
			else {
				if (x == size - 1 && dir == downRight) {
					dir = up;
				}
				else if (y == 0 && dir == upLeft) {
					dir = right;
				}
				else if (dir == up) {
					dir = upLeft;
				}
				else if (dir == right) {
					dir = downRight;
				}
			}
		}
	}
}

void pattern4(int** maze, int size) {
	int phase = 0;

	int velocityX = 0;
	int velocityY = 0;

	int x = 0;
	int y = 0;

	int number = 1;

	enum direction dir = down;

	while (1) {
		*fromIndex2D(maze, size, y, x) = number;

		if (number == size * size) {
			break;
		}

		switch (dir) {
		case up:
			velocityX = 0, velocityY = -1;
			break;
		case down:
			velocityX = 0, velocityY = 1;
			break;
		case right:
			velocityX = 1, velocityY = 0;
			break;
		case left:
			velocityX = -1, velocityY = 0;
			break;
		}
		x += velocityX;
		y += velocityY;

		number++;

		if (phase == 0) {
			if (y == size - 1 && dir == down) {
				dir = right;
				continue;
			}
			else if (x == size - 1 && dir == right) {
				dir = up;
				continue;
			}
			else if (y == 0 && dir == up) {
				dir = left;
				continue;
			}
			else if (*fromIndex2D(maze, size, y, x) != 0) {
				x++; y++;
				dir = down;
				phase = 1;
				continue;
			}
		}
		else {

			if (*fromIndex2D(maze, size, y, x) != 0)
			{
				if (dir == down) {
					x++; y--;
					dir = right;
					continue;
				}
				else if (dir == right) {
					x--; y--;
					dir = up;
					continue;
				}
				else if (dir == up) {
					x--; y++;
					dir = left;
					continue;
				}
				else if (dir == left) {
					x++; y++;
					dir = down;
					continue;
				}
			}
		}
	}
}

int** createMaze(int size) {
	int** arr2D;
	arr2D = calloc(size * size, sizeof(*arr2D));
	if (!arr2D) return;

	return arr2D;
}

int* fromIndex2D(int** arr, int size, int y, int x) {
	return &arr[size * y + x];
}

void printMaze(int** maze, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%d ", (int)*fromIndex2D(maze, size, i, j));
		}
		printf("\n");
	}
}