#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int data;
	struct _node* next;
} node;
typedef node queue;

void empty(queue*);
void show(queue*);
void size(queue*);
queue* enqueue(queue*, int);
queue* dequeue(queue*);

int main(void) {
	queue* q = NULL;
	int n, i, command, value;

	(void)scanf("%d", &n);
	for (i = 0; i < n; i++) {
		(void)scanf("%d", &command);
		switch (command) {
		case 1:
			(void)scanf("%d", &value);
			q = enqueue(q, value);
			break;
		case 2:
			q = dequeue(q);
			break;
		case 3:
			show(q);
			break;
		case 4:
			empty(q);
			break;
		case 5:
			size(q);
			break;
		}
	}
	return 0;
}

queue* dequeue(queue* q) {
	if (q == NULL) {
		empty(q);
		return NULL;
	}

	printf("%d\n", q->data);
	
	queue* prevQ = q;
	q = prevQ->next;
	free(prevQ);

	return q;
}

queue* enqueue(queue* q, int value) {
	queue* newQ = (queue*)malloc(sizeof(queue));
	if (newQ == NULL) return NULL;

	newQ->data = value;
	newQ->next = NULL;

	if (q == NULL) {
		return newQ;
	}

	queue* cur = q;
	while (cur->next != NULL) {
		cur = cur->next;
	}

	cur->next = newQ;

	return q;
}

void size(queue* q) {
	int count = 0;

	if (q != NULL) {
		queue* cur = q;
		while (cur != NULL) {
			count++;
			cur = cur->next;
		}
	}

	printf("%d\n", count);
}

void show(queue* q) {
	if (q == NULL) {
		empty(q);
		return;
	}

	queue* cur = q;
	while (cur != NULL) {
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("\n");
}

void empty(queue* q) {
	if (q == NULL) {
		printf("%s\n", "Queue is empty.");
		return;
	}
	printf("%s\n", "Queue is not empty.");
}