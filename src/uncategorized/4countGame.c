#include <stdio.h>
#include <stdlib.h>

typedef struct _plr {
	int index;
	struct _plr* next;
	struct _plr* prev;
	int value;
	int tolerance;
} player;

player* getPlayers(int, int*);
player* game(player*, int*, int, int*);
void show(player*, int);
int count(player*, int);

int main(void) {
	int n = 5;
	int k = 3;

	int tolerances[5] = { 1, 5, 3, 1, 2 };
	player* start = NULL;
	start = getPlayers(n, tolerances);

	//show(start);
	
	/*
	while (1) {
		int gameStatus;
		start = game(start, &n, k, &gameStatus);
		
		if (gameStatus) {
			break;
		}
	}
	*/

	int gameStatus;

	start = game(start, &n, k, &gameStatus);
	start = game(start, &n, k, &gameStatus);
	start = game(start, &n, k, &gameStatus);
	start = game(start, &n, k, &gameStatus);
	start = game(start, &n, k, &gameStatus);
	start = game(start, &n, k, &gameStatus);
	start = game(start, &n, k, &gameStatus);
	start = game(start, &n, k, &gameStatus);
	show(start, n);

	return 0;
}

int count(player* start, int n) {
	player* current = start;
	int c = 0;

	while (n > 0) {
		if (current->value <= current->tolerance) {
			c++;
		}

		current = current->next;
		n--;
	}

	return c;
}

player* game(player* start, int* n, int k, int* gameStatus) {
	player* current = start;
	int numLeft = *n;
	int winCheck = 1;
	int prevNumber = -1;

	while (numLeft > 0) {
		if ((current->index + 1) % k == 0) {
			current->value += 1;
		}

		numLeft--;
		if (current->value > current->tolerance && current != start) {
			current->prev->next = current->next;
			current->next->prev = current->prev;
			(*n)--;

			player* toKick = current;
			current = current->next;
			free(toKick);

			continue;
		}

		if (prevNumber == -1) {
			if (current->index == 0) {
				if (current->value <= current->tolerance) {
					prevNumber = current->value;
				}				
			}
			else {
				prevNumber = current->value;
			}
		}
		if (current->index != 0 && current->value != prevNumber && winCheck) {
			winCheck = 0;
		}

		current = current->next;
	}

	*gameStatus = winCheck;

	return start;
}

void show(player* start, int n) {
	player* current = start;

	while (n > 0) {
		if (!(current->index == 0 && current->value > current->tolerance)) {
			printf("P%d(%d / %d), ", current->index + 1, current->value, current->tolerance);
		}
		current = current->next;

		n--;
	}
	printf("\n");
}

player* getPlayers(int n, int* tolerances) {
	player* start = NULL;
	player* current = start;

	for (int i = 0; i < n; i++) {
		player* playerObject = (player*)malloc(sizeof(player));
		if (playerObject == NULL) return NULL;

		playerObject->index = i;
		playerObject->tolerance = tolerances[i];
		playerObject->value = 0;

		if (i == 0) {
			start = playerObject;
			current = start;
			continue;
		}
		if (current == NULL) return NULL;

		playerObject->prev = current;
		current->next = playerObject;
		current = playerObject;
	}

	if (current == NULL) return NULL;
	current->next = start;
	start->prev = current;

	return start;
}