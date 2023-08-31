#include <stdio.h>
#include <stdlib.h>

char** createMaze(int);
char* fromIndex2D(char**, int, int, int);

void printMaze(char**, int);
void setRow(char**, int, int, char*);

int traverseMaze(char**, int, int, int);

int main(void) {
	int size;
	(void)scanf("%d\n", &size);

	char** maze = createMaze(size);

	for (int i = 0; i < size; i++) {
		char* input = (char*)calloc(100, sizeof(char));

		fgets(input, 100, stdin);
		setRow(maze, size, i, input);

		free(input);
	}

	printf("\n");

	/*
	setRow(maze, size, 0,  "############");
	setRow(maze, size, 1,  "#   #      #");
	setRow(maze, size, 2,  "S # # #### #");
	setRow(maze, size, 3,  "### #    # #");
	setRow(maze, size, 4,  "#    ### # G");
	setRow(maze, size, 5,  "#### # # # #");
	setRow(maze, size, 6,  "#  # # # # #");
	setRow(maze, size, 7,  "## # # # # #");
	setRow(maze, size, 8,  "#        # #");
	setRow(maze, size, 9,  "###### ### #");
	setRow(maze, size, 10, "#      #   #");
	setRow(maze, size, 11, "############");
	*/		

	int startX = 0;
	int startY = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (*fromIndex2D(maze, size, i, j) == 'S') {
				startX = j;
				startY = i;
			}
		}
	}

	traverseMaze(maze, size, startX, startY);
	*fromIndex2D(maze, size, startY, startX) = 'S';

	printMaze(maze, size);

	free(maze);

	return 0;
}

int traverseMaze(char** maze, int size, int x, int y) {
	if (x < 0 || x > size - 1) {
		return 0;
	}
	if (y < 0 || y > size - 1) {
		return 0;
	}

	if (*fromIndex2D(maze, size, y, x) == '#') {
		return 0;
	}
	if (*fromIndex2D(maze, size, y, x) == 'T') {
		return 0;
	}
	if (*fromIndex2D(maze, size, y, x) == 'G') {
		return 1;
	}
	
	*fromIndex2D(maze, size, y, x) = 'T';

	int found = traverseMaze(maze, size, x - 1, y) || traverseMaze(maze, size, x + 1, y) || traverseMaze(maze, size, x, y - 1) || traverseMaze(maze, size, x, y + 1);

	if (found)
	{
		*fromIndex2D(maze, size, y, x) = '.';
	}
	else {
		*fromIndex2D(maze, size, y, x) = 'X';
	}

	return found;
}

char** createMaze(int size) {
	char** arr2D;
	arr2D = calloc(size * size, sizeof(*arr2D));
	if (!arr2D) return;

	return arr2D;
}

void printMaze(char** maze, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			char* current = fromIndex2D(maze, size, i, j);

			if (*current == 'X' || *current == 'T') {
				printf("%c", ' ');
				continue;
			}
			printf("%c", (char)*current);
			
		}
		printf("\n");
	}
}

char* fromIndex2D(char** arr, int size, int y, int x) {
	return &arr[size * y + x];
}

void setRow(char** arr, int size, int y, char* str) {
	for (int i = 0; i < size; i++) {
		*fromIndex2D(arr, size, y, i) = str[i];
	}
}
