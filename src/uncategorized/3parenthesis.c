#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node {
	char data;
	struct _node* next;
} node;
typedef node stack;

stack* push(stack*, int);
stack* pop(stack*);
char top(stack*);
int check(char*);
int empty(stack*);

int main(void)
{
	int length = 0;
	(void)scanf("%d", &length);

	char* input = (char*)calloc(length, sizeof(char));

	(void)scanf("%s", input);
	printf("%d", check(input));

	return 0;
}

int check(char* str) {
	stack* checkStack = NULL;

	for (int i = 0; i < strlen(str); i++) {
		switch (str[i]) {
		case '(':
			checkStack = push(checkStack, '(');
			break;
		case ')':
			if (top(checkStack) != '(') return 0;
			checkStack = pop(checkStack);
			break;
		case '[':
			checkStack = push(checkStack, '[');
			break;
		case ']':
			if (top(checkStack) != '[') return 0;
			checkStack = pop(checkStack);
			break;
		case '{':
			checkStack = push(checkStack, '{');
			break;
		case '}':
			if (top(checkStack) != '{') return 0;
			checkStack = pop(checkStack);
			break;
		}

		if (i == strlen(str) - 1) {
			return empty(checkStack);
		}
	}

	free(checkStack);
	return 0;
}

char top(stack* s) {
	if (s == NULL) {
		return '\0';
	}

	return s->data;
}

int empty(stack* s) {
	return s == NULL ? 1 : 0;
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