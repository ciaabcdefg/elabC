
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node* left;
	struct node* right;
} node_t;
typedef node_t bst_t;

node_t** getConnection(bst_t* t, int data) {
	if (t == NULL) {
		return NULL;
	}

	if (data > t->data) {
		if (t->right == NULL || t->right->data == data) {
			return &(t->right);
		}
		return getConnection(t->right, data);
	}
	else if (data < t->data) {
		if (t->left == NULL || t->left->data == data) {
			return &(t->left);
		}
		return getConnection(t->left, data);
	}
}

node_t* getNode(bst_t* t, int data) {
	if (t == NULL || t->data == data) {
		return t;
	}

	if (data > t->data) {
		return getNode(t->right, data);
	}
	return getNode(t->left, data);
}

node_t* getParent(bst_t* t, int data) {
	if (t == NULL) {
		return NULL;
	}

	if ((t->left != NULL && t->left->data == data) || (t->right != NULL && t->right->data == data)) {
		return t;
	}

	if (data > t->data) {
		return getParent(t->right, data);
	}
	return getParent(t->left, data);
}

int find(bst_t* t, int data) {
	return getNode(t, data) == NULL ? 0 : 1;
}

node_t* getMin(bst_t* t) {
	if (t->left == NULL) {
		return t;
	}

	return getMin(t->left);
}

node_t* getMax(bst_t* t) {
	if (t->right == NULL) {
		return t;
	}

	return getMax(t->right);
}

int find_min(bst_t* t) {
	return getMin(t)->data;
}

int find_max(bst_t* t) {
	return getMax(t)->data;
}

bst_t* insert(bst_t* t, int data) {
	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	if (newNode == NULL) return t;

	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;

	if (t == NULL) {
		return newNode;
	}

	node_t** connection = getConnection(t, data);
	*connection = newNode;

	return t;
}

bst_t* delete(bst_t* t, int data) {
	node_t* target = getNode(t, data);

	if (target->left == NULL && target->right == NULL) { // LEAF
		node_t* parent = getParent(t, data);
		*getConnection(parent, data) = NULL;

		free(target);
	}
	else if (target->left != NULL && target->right != NULL) { // FULL INTERNAL
		node_t* minNode = getMin(target->right);

		*getConnection(target, minNode->data) = minNode->right;
		target->data = minNode->data;
		
		free(minNode);
	}
	else if ((target->left == NULL) ^ (target->right == NULL)) { // HALF INTERNAL
		node_t* parent = getParent(t, data);
		*getConnection(parent, data) = (target->left == NULL) ? target->right : target->left;
		free(target);
	}

	return t;
}

void dfs(bst_t* t) {
	if (t == NULL) {
		return;
	}

	printf("%d ", t->data);
	dfs(t->left);
	dfs(t->right);
}

int main(void) {
	bst_t* t = NULL;
	int n, i;
	int command, data;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &command);
		switch (command) {
		case 1:
			scanf("%d", &data);
			t = insert(t, data);
			break;
		case 2:
			scanf("%d", &data);
			t = delete(t, data);
			break;
		case 3:
			scanf("%d", &data);
			printf("%d\n", find(t, data));
			break;
		case 4:
			printf("%d\n", find_min(t));
			break;
		case 5:
			printf("%d\n", find_max(t));
			break;
		}
	}
	return 0;
}

