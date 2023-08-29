#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	struct _node* parent;
	struct _node* sibling;
	struct _node* child;
	int value;
} node_t;
typedef node_t tree_t;

typedef struct _queueNode {
	struct _queueNode* next;
	node_t* data;
} queueNode;
typedef queueNode queue;

//-----------------------------------------------------------//

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

node_t* searchNode(tree_t* t, int value) {
	if (t == NULL || t->value == value) {
		return t;
	}
	node_t* node = searchNode(t->child, value);

	if (node != NULL) {
		return node;
	}
	else {
		return searchNode(t->sibling, value);
	}
}

void dfs(node_t* t) {
	if (t == NULL) {
		return;
	}

	printf("%d ", t->value);
	dfs(t->child);
	dfs(t->sibling);
}

void bfs(node_t* t) {
	if (t == NULL) return;

	queue* q = NULL;
	q = enqueue(q, t);

	while (q != NULL) {
		node_t* node = dequeue(&q);
		printf("%d ", node->value);

		node_t* cur = node->child;

		while (cur != NULL) {
			q = enqueue(q, cur);
			cur = cur->sibling;
		}
	}

	printf("\n");
}

int search(tree_t* t, int value) {
	node_t* node = searchNode(t, value);
	return node == NULL ? 0 : 1;
}

int degree(tree_t* t, int value) {
	node_t* node = searchNode(t, value);
	if (node == NULL) return 0;

	int count = 0;
	
	node = node->child;
	while (node != NULL) {
		count++;
		node = node->sibling;
	}

	return count;
}

int is_root(tree_t* t, int value) {
	node_t* node = searchNode(t, value);
	if (node == NULL) return 0;

	return node->parent == NULL ? 1 : 0;
}

int is_leaf(tree_t* t, int value) {
	node_t* node = searchNode(t, value);
	if (node == NULL) return 0;

	return node->child == NULL ? 1 : 0;
}

int depth(tree_t* t, int value) {
	node_t* node = searchNode(t, value);

	int current = 0;
	while (node != NULL) {
		current++;
		node = node->parent;
	}

	return current - 1;
}

void siblings(tree_t* t, int value) {
	node_t* node = searchNode(t, value);
	if (node == NULL || node->parent == NULL) {
		printf("\n");
		return;
	}

	node_t* cur = node->parent->child;

	while (cur != NULL) {
		if (cur == node) {
			cur = cur->sibling;
			continue;
		}

		printf("%d ", cur->value);
		cur = cur->sibling;
	}

	printf("\n");
}

void print_path(tree_t* t, int start, int end) {
	node_t* startNode = searchNode(t, start);
	node_t* node = searchNode(t, end);
	int depthDifference = depth(t, end) - depth(t, start);

	int* data = (int*)calloc(depthDifference + 1, sizeof(int));
	if (data == NULL) return;

	for (int i = 0; i < depthDifference + 1; i++) {
		data[i] = node->value;
		node = node->parent;
	}

	for (int i = depthDifference; i >= 0; i--) {
		printf("%d ", data[i]);
	}

	free(data);
	printf("\n");
}

int path_length(tree_t* t, int start, int end) {
	node_t* startNode = searchNode(t, start);
	node_t* node = searchNode(t, end);
	return depth(t, end) - depth(t, start) + 1;
}

void ancestor(tree_t* t, int value) {
	print_path(t, t->value, value);
}

void descendant(tree_t* t, int value) {
	node_t* node = searchNode(t, value);
	if (node == NULL) {
		return;
	}

	bfs(node);
}

void print_tree(tree_t* t) {
	if (t == NULL) {
		return;
	}

	node_t* root = t;
	while (1) {
		if (root->parent == NULL) {
			break;
		}
		root = root->parent;
	}

	for (int i = 0; i < depth(root, t->value); i++) {
		printf("    ");
	}
	printf("%d\n", t->value);

	print_tree(t->child);
	print_tree(t->sibling);
}

tree_t* attach(tree_t* t, int parent, int child) {
	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	if (newNode == NULL) return NULL;

	newNode->sibling = NULL;
	newNode->parent = NULL;
	newNode->child = NULL;
	newNode->value = child;

	if (t == NULL) {
		return newNode;
	}

	node_t* parentNode = searchNode(t, parent);
	if (parentNode == NULL) return NULL;

	newNode->parent = parentNode;
	if (parentNode->child == NULL) {
		parentNode->child = newNode;
		return t;
	}

	node_t* curSibling = parentNode->child;
	while (1) {
		if (curSibling->sibling == NULL) {
			break;
		}
		curSibling = curSibling->sibling;
	}
	curSibling->sibling = newNode;

	return t;
}

tree_t* destroy(tree_t* t) {
	if (t == NULL) {
		return NULL;
	}

	destroy(t->child);
	destroy(t->sibling);
	free(t);

	return NULL;
}

tree_t* detach(tree_t* t, int value) {
	node_t* node = searchNode(t, value);
	if (node == NULL) return t;
	if (node->parent == NULL) {
		destroy(node->child);
		free(node);

		return NULL;
	}

	node_t* cur = node->parent->child;
	if (cur == node) {
		node->parent->child = node->sibling;
	}
	else {
		while (1) {
			if (cur->sibling == node) {
				break;
			}
			cur = cur->sibling;
		}
		cur->sibling = node->sibling;
	}

	destroy(node->child);
	free(node);

	return t;
}

//-----------------------------------------------------------//

int main(void) {
	tree_t* t = NULL;
	int n, i, command;
	int parent, child, node, start, end;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &command);
		switch (command) {
		case 1:
			scanf("%d %d", &parent, &child);
			t = attach(t, parent, child);
			break;
		case 2:
			scanf("%d", &node);
			t = detach(t, node);
			break;
		case 3:
			scanf("%d", &node);
			printf("%d\n", search(t, node));
			break;
		case 4:
			scanf("%d", &node);
			printf("%d\n", degree(t, node));
			break;
		case 5:
			scanf("%d", &node);
			printf("%d\n", is_root(t, node));
			break;
		case 6:
			scanf("%d", &node);
			printf("%d\n", is_leaf(t, node));
			break;
		case 7:
			scanf("%d", &node);
			siblings(t, node);
			break;
		case 8:
			scanf("%d", &node);
			printf("%d\n", depth(t, node));
			break;
		case 9:
			scanf("%d %d", &start, &end);
			print_path(t, start, end);
			break;
		case 10:
			scanf("%d %d", &start, &end);
			printf("%d\n",
				path_length(t, start, end));
			break;
		case 11:
			scanf("%d", &node);
			ancestor(t, node);
			break;
		case 12:
			scanf("%d", &node);
			descendant(t, node);
			break;
		case 13:
			bfs(t);
			break;
		case 14:
			dfs(t);
			break;
		case 15:
			print_tree(t);
			break;
		}
	}
	return 0;
}