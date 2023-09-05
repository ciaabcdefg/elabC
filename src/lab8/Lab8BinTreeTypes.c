#include <stdio.h>
#include <stdlib.h>
#include "week8.h"

#ifndef __bin_tree__
typedef struct node {
	int data;
	struct node* left;
	struct node* right;
} node_t;
typedef node_t tree_t;
#endif

int is_full(tree_t* t) {
	if (t == NULL) {
		return 1;
	}
	if (t->left == NULL && t->right == NULL) {
		return 1;
	}
	if (t->left != NULL && t->right != NULL) {
		return is_full(t->left) && is_full(t->right);
	}
	
	return 0;
}

int count(tree_t* t) {
	if (t == NULL) {
		return 0;
	}

	return 1 + count(t->left) + count(t->right);
}

int height(tree_t* t) {
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

int	power(int a) {
	return 1 << a;
}

int is_perfect(tree_t* t) {
	return power(height(t) + 1) == count(t) + 1;
}

int is_complete(tree_t* t) {
	if (height(t) <= 0) {
		return 1;
	}

	int curHeight = height(t);
	int leftHeight = height(t->left);
	int rightHeight = height(t->right);

	int condition1 = is_complete(t->left) && (leftHeight == curHeight - 1) && is_perfect(t->right) && (rightHeight == curHeight - 2);
	int condition2 = is_perfect(t->left) && (leftHeight == curHeight - 1) && is_complete(t->right) && (rightHeight == curHeight - 1);

	return condition1 || condition2;
}

int is_degenerate(tree_t* t) {
	return count(t) - 1 == height(t);
}

int all_left(tree_t* t) {
	if (t == NULL) {
		return 1;
	}
	if (t->right != NULL) {
		return 0;
	}

	return all_left(t->left);
}

int all_right(tree_t* t) {
	if (t == NULL) {
		return 1;
	}
	if (t->left != NULL) {
		return 0;
	}

	return all_right(t->right);
}

int is_skewed(tree_t* t) {
	return all_left(t) || all_right(t);
}

int main(void) {
	tree_t* t = NULL;
	int n, i;
	int parent, child;
	int branch; // 0 root, 1 left, 2 right
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d %d %d", &parent, &child,
			&branch);
		t = attach(t, parent, child, branch);
	}
	printf("%d %d %d %d %d\n", is_full(t),
		is_perfect(t), is_complete(t),
		is_degenerate(t), is_skewed(t));
	return 0;
}