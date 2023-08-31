#pragma once

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

queue* enqueue(queue*, node_t*);
node_t* dequeue(queue**);
void showQueue(queue*);