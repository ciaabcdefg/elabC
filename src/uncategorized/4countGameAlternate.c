#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _plr {
	int index;
	int count;
	int shots;
	int tolerance;
	struct _plr* next;
	struct _plr* prev;
} player ;

player* createPlayers(int, int*);
void show(player*);
int game(player*, int);
int contains(int, int);

int main(void) {
	int n = 5;
	int k = 3;
	//int tolerances[10] = { 1, 5, 3, 1, 2 };

	int* tolerances = (int*)calloc(n, sizeof(int));
	if (tolerances == NULL) return 0;

	(void)scanf("%d %d\n", &n, &k);

	fflush(stdin);
	char* input = (char*)calloc(1024, sizeof(char));
	fgets(input, 1024, stdin);

	char* token;
	token = strtok(input, " ");

	for (int i = 0; i < n; i++) {
		tolerances[i] = atoi(token);
		token = strtok(NULL, " ");
	}

	player* start = createPlayers(n, tolerances);
	printf("%d", game(start, k));

	return 0;
}

int game(player* start, int k) {
	player* current = start;
	int count = 1;

	while (current->next != current) {
		if (current->count % k == 0 || contains(current->count, k)) {
			current->shots++;
		}

		//printf("P%d(%d, %d/%d)\n", current->index, current->count, current->shots, current->tolerance);

		if (current->shots > current->tolerance) {
			player* toRemove = current;
			current->prev->next = current->next;
			current->next->prev = current->prev;
			current = current->next;
			free(toRemove);
		}
		else {
			current = current->next;
		}

		count++;
		current->count = count;
	}

	return current->index;
}

int contains(int n, int k) {
	while (n > 0) {
		if (n % 10 == k) {
			return 1;
		}
		n /= 10;
	}
	return 0;
}

void show(player* start) {
	int started = 0;
	player* current = start;

	while (1) {
		if (current == start && started) {
			break;
		}
		else if (current == start && !started) {
			started = 1;
		}
		printf("P%d(%d, %d/%d), ", current->index, current->count, current->shots, current->tolerance);
		current = current->next;
	}
	printf("\n");
}

player* createPlayers(int n, int* tolerances) {
	player* start = NULL;
	player* current = start;

	for (int i = 0; i < n; i++) {
		player* obj = (player*)malloc(sizeof(player));
		if (obj == NULL) return NULL;

		obj->index = i + 1;
		obj->shots = 0;
		obj->count = 1;
		obj->tolerance = tolerances[i];
		
		if (i == 0) {
			start = obj;
			current = start;
			continue;
		}

		obj->prev = current;
		current->next = obj;
		current = obj;
	}

	if (current == NULL) return NULL;
	current->next = start;
	start->prev = current;

	return start;
}

