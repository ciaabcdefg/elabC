#include "Lab7queue.h"
#include <stdlib.h>
#include <stdio.h>

node_t* dequeue(queue** q) {
	if (*q == NULL) {
		return NULL;
	}

	queue* prevQ = *q;
	node_t* prevNode = prevQ->data;

	*q = prevQ->next;
	free(prevQ);

	return prevNode;
}

queue* enqueue(queue* q, node_t* value) {
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

void showQueue(queue* q) {
	if (q == NULL) {
		return;
	}

	queue* cur = q;
	while (cur != NULL) {
		printf("%d ", cur->data->value);
		cur = cur->next;
	}
	printf("\n");
}
