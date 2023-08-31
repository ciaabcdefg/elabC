#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOKEN atoi(strtok(NULL, " "))

typedef struct node {
	int data;
	struct node* next;
} node_t;

node_t* append(node_t*, int);
node_t* get(node_t*, int);
node_t* reverse(node_t*);
node_t* getLastNode(node_t*);
node_t* cut(node_t*, int, int);
void show(node_t*);

int main(void) {
	node_t* startNode;
	int n, i;
	startNode = NULL;
	
	(void)scanf("%d\n", &n);

	for (i = 0; i < n; i++) {
		char input[64];
		char command;
		int par1;
		int par2;

		fgets(input, 64, stdin);

		command = strtok(input, " ")[0];

		switch (command) {
		case 'A':
			par1 = TOKEN;
			startNode = append(startNode, par1);
			break;
		case 'G':
			par1 = TOKEN;
			printf("%d\n", get(startNode, par1)->data);
			break;
		case 'S':
			show(startNode);
			break;
		case 'R':
			startNode = reverse(startNode);
			break;
		case 'C':
			par1 = TOKEN;
			par2 = TOKEN;
			startNode = cut(startNode, par1, par2);
			break;
		}
	}

	return 0;
}

node_t* get(node_t* target, int pos) {
	int currentPos = 0;
	node_t* currentNode = target;

	while (currentPos < pos) {
		currentPos++;
		currentNode = currentNode->next;
	}

	return currentNode;
}

void show(node_t* target) {
	if (target == NULL) {
		printf("\n");
		return;
	}

	node_t *currentNode = target;

	int i = 0;

	while (1)
	{
		printf("%d ", currentNode->data);

		if (currentNode->next == NULL) {
			break;
		}
		currentNode = currentNode->next;

		i++;
	}

	printf("\n");
}

node_t* getLastNode(node_t* target) {
	node_t* currentNode = target;

	while (currentNode->next != NULL) {
		currentNode = currentNode->next;
	}

	return currentNode;
}

node_t* append(node_t *target, int value) {
	if (target == NULL) {
		node_t* startNode = (node_t*)malloc(sizeof(node_t));
		if (startNode == NULL) return NULL;

		startNode->next = NULL;
		startNode->data = value;

		return startNode;
	}

	node_t* currentNode = NULL;
	currentNode = target;

	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	if (newNode == NULL) return NULL;

	newNode->next = NULL;
	newNode->data = value;

	while (1) {
		if (currentNode->next == NULL) {
			break;
		}
		currentNode = currentNode->next;
	}

	currentNode->next = newNode;

	return target;
}

node_t* reverse(node_t* target) {
	if (target->next == NULL) return target;

	node_t* lastNode = NULL;
	node_t* newFirstNode = NULL;
	node_t* picker = NULL;

	while (1) {
		if (target->next == NULL) {
			break;
		}
		if (lastNode == NULL) {
			lastNode = getLastNode(target);
			newFirstNode = lastNode;
			continue;
		}
		picker = get(target, 0);

		while (1) {
			if (picker->next == lastNode || picker->next == NULL) {
				break;
			}
			picker = picker->next;
		}

		lastNode->next = picker;
		lastNode = picker;
		picker->next = NULL;
	}

	return newFirstNode;
}

node_t* cut(node_t* target, int a, int b) {
	int index = 0;
	node_t* currentNode;
	node_t* newStartNode;

	currentNode = target;

	while (1) {
		if (index == a) {
			newStartNode = currentNode;
			break;
		}

		node_t* previousNode = currentNode;
		currentNode = currentNode->next;
		free(previousNode);

		index++;
	}

	while (1) {
		if (index == b) {
			break;
		}

		currentNode = currentNode->next;
		index++;
	}

	while (1) {
		if (currentNode->next == NULL) {
			break;
		}

		node_t* previousNode = currentNode;
		currentNode = currentNode->next; 

		if (index == b) {
			previousNode->next = NULL;
			break;
		}
		else {
			free(previousNode);
		}

		index++;
	}

	if (index != b) {
		free(currentNode);
	}

	return newStartNode;
}