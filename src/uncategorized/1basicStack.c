#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int data;
	struct _node* next;
} node;
typedef node stack;

void empty(stack*);
void top(stack*);
void size(stack*);
stack* push(stack*, int);
stack* pop(stack*);

int main(void) {
	stack* s = NULL;

	int n, i, command, value;
	(void)scanf("%d", &n);

	for (i = 0; i < n; i++) {
		(void)scanf("%d", &command);

		switch (command) {
		case 1:
			(void)scanf("%d", &value);
			s = push(s, value);
			break;
		case 2:
			top(s);
			break;
		case 3:
			s = pop(s);
			break;
		case 4:
			empty(s);
			break;
		case 5:
			size(s);
			break;
		}
	}
}

stack* pop(stack* s) {
	if (s == NULL) {
		return NULL;
	}

	node* prevTop = s;
	s = prevTop->next;
	free(prevTop);

	return s;
}

void empty(stack* s) {
	if (s == NULL) printf("%s\n", "Stack is empty.");
	else printf("%s\n", "Stack is not empty.");
}

void top(stack* s) {
	if (s == NULL) {
		empty(s);
		return;
	}

	printf("%d\n", s->data);
}

void size(stack* s) {
	int count = 0;

	if (s != NULL) {
		stack* cur = s;

		while (cur != NULL) {
			cur = cur->next;
			count++;
		}
	}

	printf("%d\n", count);
}

stack* push(stack* s, int value) {
	if (s == NULL) {
		node* newNode = (node*)malloc(sizeof(node));
		if (newNode == NULL) return NULL;

		newNode->data = value;
		newNode->next = NULL;

		return newNode;
	}

	node* newNode = (node*)malloc(sizeof(node));
	if (newNode == NULL) return NULL;

	newNode->data = value;
	newNode->next = s;

	return newNode;
}