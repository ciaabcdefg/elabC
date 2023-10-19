#include <stdio.h>
#include <stdlib.h>

typedef struct _vertex {
	int id;
	int adjWeight;

	int blocked;

	struct _vertex* next;
} vertex;

typedef struct _graph {
	vertex* vertices;
	int count;
} graph;

graph* init(int n) {
	graph* g = (graph*)malloc(sizeof(graph));
	if (g == NULL) return NULL;

	vertex* vertices = (vertex*)calloc(n, sizeof(vertex));
	if (vertices == NULL) return NULL;

	g->vertices = vertices;
	g->count = n;

	for (int i = 0; i < n; i++) {
		g->vertices[i].id = i;
		g->vertices[i].adjWeight = 0;
		g->vertices[i].next = NULL;
		g->vertices[i].blocked = 0;
	}

	return g;
}

void insert(graph* g, int id0, int id1, int weight) {
	if (g == NULL) return;

	vertex* connection = (vertex*)malloc(sizeof(vertex));
	if (connection == NULL) return;

	vertex* cur = &g->vertices[id0];
	while (cur != NULL) {
		if (cur->next == NULL) {
			break;
		}
		cur = cur->next;
	}
	cur->next = connection;
	cur->adjWeight = weight;

	connection->id = id1;
	connection->adjWeight = 0;
	connection->next = NULL;
	connection->blocked = 0;

	connection = (vertex*)malloc(sizeof(vertex));
	if (connection == NULL) return;

	cur = &g->vertices[id1];
	while (cur != NULL) {
		if (cur->next == NULL) {
			break;
		}
		cur = cur->next;
	}
	cur->next = connection;
	cur->adjWeight = weight;

	connection->id = id0;
	connection->adjWeight = 0;
	connection->next = NULL;
	connection->blocked = 0;
}

int isBlocked(graph* g, int v0, int v1) {
	if (g == NULL) return 0;
	
	vertex* cur = &g->vertices[v0];

	while (cur != NULL) {
		if (cur->id == v1) {
			return cur->blocked;
		}
		cur = cur->next;
	}

	return 0;
}

void setBlocked(graph* g, int v0, int v1, int blocked) {
	if (g == NULL) return 0;

	vertex* cur = &g->vertices[v0];
	while (cur != NULL) {
		if (cur->id == v1) {
			cur->blocked = blocked;
		}
		cur = cur->next;
	}

	cur = &g->vertices[v1];
	while (cur != NULL) {
		if (cur->id == v0) {
			cur->blocked = blocked;
		}
		cur = cur->next;
	}
}

int shortestPath(graph* g, int v0, int v1, int* totalDist, int* minDist) {
	if (g == NULL) return 0;
	if (v0 == v1) {
		*minDist = (totalDist == NULL) ? 0 : *minDist;
		return 1;
	}
	if (totalDist == NULL) {
		totalDist = (int*)calloc(1, sizeof(int));
		if (totalDist == NULL) return 0;

		*totalDist = 0;
	}

	vertex* cur = &g->vertices[v0];

	if (cur != NULL) {
		// printf("\n[%d %d]: ", cur->id, *totalDist);
	}

	while (cur != NULL && cur->next != NULL) {
		if (isBlocked(g, v0, cur->next->id) == 0) {
			// printf("%d (%d), ", cur->next->id, cur->adjWeight);

			setBlocked(g, v0, cur->next->id, 1);
			*totalDist += cur->adjWeight;
			int result = shortestPath(g, cur->next->id, v1, totalDist, minDist);

			if (result == 0) {
				setBlocked(g, v0, cur->next->id, 0);
				*totalDist -= cur->adjWeight;
				// printf("Dead End at %d, back to %d (weight: %d, dist = %d)\n", cur->next->id, v0, cur->adjWeight, *totalDist);
			}
			else {
				setBlocked(g, v0, cur->next->id, 0);
				// printf("Found a path of weight = %d, back to %d\n", *totalDist, v0);
				if (*minDist == -1 || *totalDist <= *minDist) {
					*minDist = *totalDist;
					//printf("SET %d\n", *minDist);
				}
				*totalDist -= cur->adjWeight;
			}
		}
		else {
			// printf("%d already visited\n", cur->next->id);
		}

		cur = cur->next;
	}

	return 0;
}

int main(void) {
	graph* g = NULL;
	int i, n, m, p;
	int u, v, w;
	int s, t;

	(void)scanf("%d", &n);
	(void)scanf("%d", &m);
	(void)scanf("%d", &p);

	g = init(n);

	for (i = 0; i < m; i++) {
		(void)scanf("%d", &u);
		(void)scanf("%d", &v);
		(void)scanf("%d", &w);
		insert(g, u, v, w);
	}
	for (i = 0; i < p; i++) {
		(void)scanf("%d", &s);
		(void)scanf("%d", &t);

		int minDist = -1;
		shortestPath(g, s, t, NULL, &minDist);

		printf("%d\n", minDist);
	}

	return 0;
}