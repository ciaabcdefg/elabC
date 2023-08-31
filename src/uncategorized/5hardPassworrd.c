#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node {
	char data;
	struct _node* next;
} node;
typedef node stack;

stack* push(stack*, char);
char pop(stack**);
int check(char*);

int main(void) {
	char* str = (char*)calloc(100000, sizeof(char));
	//(void)scanf("%s", str);
	fgets(str, 100000, stdin);

	printf("%d", check(str));

	return 0;
}

int check(char* str) {
	stack* checkStack = NULL;
	int phase = 0;

	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == 'x') {
			if (phase == 1) {
				return 0;
			}
			phase = 1;
			continue;
		}

		if (phase == 0) {
			checkStack = push(checkStack, str[i]);
		}
		else {
			char popped = pop(&checkStack);

			if (str[i] == 'y') {
				if (str[i - 1] == 'x') {
					if (popped != '\0') {
						return 0;
					}
					return 1;
				}
				else {
					break;
				}
			}

			if (popped != str[i]) return 0;
		}
	}

	return 1 && phase && (checkStack == NULL);
}

char pop(stack** s) {
	if (*s == NULL) {
		return '\0';
	}

	node* prevTop = *s;
	char value = prevTop->data;
	*s = prevTop->next;

	free(prevTop);
	return value;
}

stack* push(stack* s, char value) {
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