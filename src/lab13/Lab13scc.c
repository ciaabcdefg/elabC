#include <stdio.h>
#include <stdlib.h>

typedef struct _vertex {
	int id;
	struct _vertex* next;
	int visited;
} vertex;

typedef struct _graph {
	vertex* vertices;
	int count;
} graph;

typedef struct _stack {
	int* arr;
	int top;
	int size;
} stack;

stack* stackInit(int n) {
	stack* s = (stack*)malloc(sizeof(stack));
	if (s == NULL) return NULL;
	
	int* arr = (int*)calloc(n, sizeof(int));
	if (arr == NULL) return NULL;

	s->arr = arr;
	s->top = -1;
	s->size = n;

	return s;
}

void push(stack* s, int value) {
	if (s == NULL) return;
	if (s->top >= s->size - 1) return;

	s->top += 1;
	s->arr[s->top] = value;
}

int pop(stack* s) {
	if (s == NULL) return;
	if (s->top <= -1) return;

	int popValue = s->arr[s->top];

	s->top--;

	return popValue;
}

void showStack(stack* s) {
	if (s == NULL || s->top <= -1) return;

	for (int i = s->top; i >= 0; i--) {
		printf("%d, ", s->arr[i]);
	}
	printf("\n");
}

graph* init(int n) {
	graph* g = (graph*)malloc(sizeof(graph));
	if (g == NULL) return;

	vertex* vertices = (vertex*)calloc(n, sizeof(vertex));
	if (vertices == NULL) return NULL;

	g->vertices = vertices;
	g->count = n;

	for (int i = 0; i < n; i++) {
		vertices[i].id = i;
		vertices[i].next = NULL;
		vertices[i].visited = 0;
	}

	return g;
}

void connect(graph* g, int v0, int v1) {
	if (g == NULL) return;

	vertex* connection = (vertex*)malloc(sizeof(vertex));
	if (connection == NULL) return;

	vertex* cur = &g->vertices[v0];
	while (cur != NULL) {
		if (cur->next == NULL) {
			break;
		}
		cur = cur->next;
	}
	cur->next = connection;

	connection->id = v1;
	connection->next = NULL;
}

void setVisited(graph* g, int i, int value) {
	if (g == NULL) return;

	g->vertices[i].visited = value;
}

int checkVisited(graph* g, int i) {
	if (g == NULL) return 0;

	return g->vertices[i].visited;
}

void dfs(graph* g, stack* s, int v0, int suppress, int* count, int* arr) {
	if (g == NULL) return;

	vertex* cur = &g->vertices[v0];

	if (!suppress) {
		printf("%d, ", cur->id);
	}

	setVisited(g, cur->id, 1);

	if (count != NULL) {
		if (arr != NULL) {
			arr[*count] = v0;
		}
		*count += 1;
	}
	
	while (cur != NULL && cur->next != NULL) {
		if (checkVisited(g, cur->next->id) == 0) {
			setVisited(g, cur->next->id, 1);
			dfs(g, s, cur->next->id, suppress, count, arr);
		}
		
		cur = cur->next;
	}

	if (!suppress) {
		printf("\n%d (out), ", v0);
	}
	
	if (s != NULL) {
		push(s, v0);
	}
}

void sort(int* arr, int count) {
	if (arr == NULL) return arr;

	for (int i = 0; i < count; i++) {
		for (int j = i; j < count; j++) {
			if (arr[i] > arr[j]) {
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

void showArray(int* arr, int count) {
	if (arr == NULL) return;

	for (int i = 0; i < count; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

graph* transpose(graph* g) {
	if (g == NULL) return NULL;

	graph* t = init(g->count);
	if (t == NULL) return NULL;

	for (int i = 0; i < g->count; i++) {
		vertex* cur = g->vertices[i].next;
		while (cur != NULL) {
			connect(t, cur->id, i);
			cur = cur->next;
		}
	}

	return t;
}

int main(void) {
	graph* g = NULL;
	stack* s = NULL;

	int n, m;
	int k, q;

	(void)scanf("%d", &n);
	(void)scanf("%d", &m);

	g = init(n);
	s = stackInit(n);

	for (int i = 0; i < m; i++) {
		(void)scanf("%d", &k);
		(void)scanf("%d", &q);
		connect(g, k, q);
	}

	while (s->top + 1 < n) {
		for (int i = 0; i < n; i++) {
			if (checkVisited(g, i) == 0) {
				//printf("%d is empty!\n", i);
				dfs(g, s, i, 1, NULL, NULL);
				break;
			}
		}
	}

	graph* t = transpose(g);

	int maxCount = -1;
	int* maxArr = NULL;

	while (s->top != -1) {
		int popped = pop(s);
		int count = 0;

		if (checkVisited(t, popped) == 1) {
			continue;
		}
		count = 0;
		
		int* arr = (int*)calloc(n, sizeof(int));
		if (arr == NULL) return 0;

		dfs(t, NULL, popped, 1, &count, arr);

		if (count > maxCount) {
			free(maxArr);
			maxArr = arr;
			maxCount = count;
		}
	}

	sort(maxArr, maxCount);
	showArray(maxArr, maxCount);

	return 0;
}