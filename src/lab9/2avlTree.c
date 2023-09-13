#include <stdio.h>
#include <stdlib.h>
#include "week9.h"
#ifndef __avl_tree__
typedef struct node {
	int data;
	int height;
	struct node* left;
	struct node* right;
} node_t;
typedef node_t avl_t;
#endif

int MAX(int a, int b) {
	return a > b ? a : b;
}

node_t** getConnection(avl_t* t, int data) {
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

node_t* getMin(avl_t* t) {
	if (t->left == NULL) {
		return t;
	}

	return getMin(t->left);
}

int height(avl_t* t) {
	if (t == NULL) {
		return -1;
	}

	int leftHeight = height(t->left);
	int rightHeight = height(t->right);

	if (leftHeight > rightHeight) {
		return leftHeight + 1;
	}
	else if (rightHeight > leftHeight) {
		return rightHeight + 1;
	}
	return leftHeight + 1;
}

void llAdjustment(avl_t* t) {
	node_t* node = t->left;

	int oldValue = t->data;
	t->data = node->data;

	node_t* temp = t->right;
	t->right = node;
	t->left = node->left;
	node->left = node->right;
	node->right = temp;
	node->height -= 1;

	node->data = oldValue;
}

void rrAdjustment(avl_t* t) {
	node_t* node = t->right;

	int oldValue = t->data;
	t->data = node->data;

	node_t* temp = t->left;
	t->left = node;
	t->right = node->right;
	node->right = node->left;
	node->left = temp;
	node->height -= 1;

	node->data = oldValue;
}

void rlAdjustment(avl_t* t) {
	node_t* rNode = t->right;
	node_t* rlNode = rNode->left;

	int oldValue = t->data;
	t->data = rlNode->data;

	node_t* temp = t->left;
	t->left = rlNode;
	rNode->left = rlNode->right;
	rlNode->right = rlNode->left;
	rlNode->left = temp;

	rNode->height -= 1;

	rlNode->data = oldValue;
}

void lrAdjustment(avl_t* t) {
	node_t* lNode = t->left;
	node_t* rNode = t->right;
	node_t* lrNode = lNode->right;

	int oldValue = t->data;
	t->data = lrNode->data;

	t->left = lrNode;
	lNode->right = lrNode->left;
	lrNode->left = lNode;

	t->right = lrNode;
	t->left = lNode;

	lrNode->left = lrNode->right;
	lrNode->right = rNode;

	lNode->height -= 1;
	t->height -= 1;

	lrNode->data = oldValue;
}

int imbalanceCheck(avl_t* t) {
	int leftHeight = t->left == NULL ? -1 : t->left->height;
	int rightHeight = t->right == NULL ? -1 : t->right->height;
	int heightDiff = rightHeight - leftHeight;

	return heightDiff;
}

int maxHeight(avl_t* t) {
	int leftHeight = t->left == NULL ? -1 : t->left->height;
	int rightHeight = t->right == NULL ? -1 : t->right->height;

	return MAX(leftHeight, rightHeight);
}

avl_t* insert2(avl_t* t, int data) {
	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	if (newNode == NULL) return t;

	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->height = 0;

	if (t == NULL) {
		return newNode;
	}

	node_t* node = NULL;

	if (data > t->data) {
		node = insert2(t->right, data);
		if (t->right == NULL) {
			t->right = newNode;
			node = newNode;
		}
	}
	else {
		node = insert2(t->left, data);
		if (t->left == NULL) {
			t->left = newNode;
			node = newNode;
		}
	}

	int leftHeight = t->left == NULL ? -1 : t->left->height;
	int rightHeight = t->right == NULL ? -1 : t->right->height;
	int heightDiff = rightHeight - leftHeight;

	if (heightDiff < -1) { // left
		if (imbalanceCheck(t->left) == -1) { // left
			llAdjustment(t);
		}
		else {
			lrAdjustment(t);
		}
	}
	else if (heightDiff > 1) { // right
		if (imbalanceCheck(t->right) == -1) { // left
			rlAdjustment(t);
		}
		else {
			rrAdjustment(t);
		}
	}

	if (t->height != maxHeight(t) + 1) {
		t->height = maxHeight(t) + 1;
	}

	return t;
}

avl_t* insert(avl_t* t, int data) {
	t = insert2(t, data);
	return t;
}

avl_t* delete2(avl_t* t, int data) {
	if (t == NULL) {
		return NULL;
	}
	if (t->data == data) {
		return t;
	}

	node_t* node = NULL;
	if (data > t->data) {
		node = delete2(t->right, data);
	}
	else if (data < t->data) {
		node = delete2(t->left, data);
	}

	if (node != NULL) {
		if (node->data == data) {
			if (node->left == NULL && node->right == NULL) {
				*getConnection(t, node->data) = NULL;
				free(node);
			}
			else if ((node->left == NULL) ^ (node->right == NULL)) {
				*getConnection(t, node->data) = (node->left == NULL) ? node->right : node->left;
				free(node);
			}
			else {
				node_t* minNode = getMin(node->right);

				*getConnection(node, minNode->data) = minNode->right;
				node->data = minNode->data;

				free(minNode);
			}

			node = t;
		}
	}

	if (node != NULL) {
		int imbalanceDir = imbalanceCheck(t);
		if (imbalanceDir < -1) { // left
			if (imbalanceCheck(t->left) == -1) { // left
				llAdjustment(t);
			}
			else { // right
				lrAdjustment(t);
			}
		}
		else if (imbalanceDir > 1) { // right
			if (imbalanceCheck(t->left) == -1) { // left
				rlAdjustment(t);
			}
			else { // right
				rrAdjustment(t);
			}
		}

		if (t->height != maxHeight(t) + 1) {
			t->height = maxHeight(t) + 1;
		}
	}

	return t;
}

avl_t* delete(avl_t* t, int data) {
	if (t->data == data) {
		node_t* minNode = getMin(t->right);

		*getConnection(t, minNode->data) = minNode->right;
		t->data = minNode->data;

		free(minNode);
	}
	else {
		(void)delete2(t, data);
	}

	return t;
}

void dfs(avl_t* t) {
	if (t == NULL) {
		return;
	}

	printf("%d(%d)\n", t->data, t->height);
	dfs(t->left);
	dfs(t->right);
}

int main(void) {
	avl_t* t = NULL;
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
			print_tree(t);
			break;
		}
	}
	return 0;
}
