#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node {
	double data;
	struct _node* next;
} node;
typedef node stack;

stack* push(stack* s, double value);
double pop(stack**);
double calculate(char*);

int main(void) {
	int length = 0;
	(void)scanf("%d", &length);

	char* input = (char*)calloc(length, sizeof(char));
	//char* input = "324*15-/+";

	(void)scanf("%s", input);
	printf("%.2lf", calculate(input));

	return 0;
}

double calculate(char* str) {
	stack* numStack = (stack*)malloc(sizeof(numStack));
	if (numStack == NULL) return 0;

	double a = 0, b = 0;

	for (int i = 0; i < strlen(str); i++) {
		switch (str[i]) {
		case '*':
			b = pop(&numStack);
			a = pop(&numStack);
			numStack = push(numStack, a * b);
			continue;
		case '/':
			b = pop(&numStack);
			a = pop(&numStack);
			numStack = push(numStack, a / b);
			continue;
		case '+':
			b = pop(&numStack);
			a = pop(&numStack);
			numStack = push(numStack, a + b);
			continue;
		case '-':
			b = pop(&numStack);
			a = pop(&numStack);
			numStack = push(numStack, a - b);
			continue;
		}
		
		numStack = push(numStack, ((double)str[i] - (double)'0'));
	}

	double result = numStack->data;
	free(numStack);

	return result;
}

double pop(stack** s) {
	if (*s == NULL) {
		return 0;
	}

	node* prevTop = *s;
	double value = prevTop->data;

	*s = prevTop->next;
	free(prevTop);

	return value;
}

stack* push(stack* s, double value) {
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