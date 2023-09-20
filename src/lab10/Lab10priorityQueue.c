#include <stdio.h>
#include <stdlib.h>

typedef struct heap {
	int* data;
	int last_index;
} heap_t;

heap_t* init_heap(int size) {
	heap_t* newHeap = (heap_t*)malloc(sizeof(heap_t));
	if (newHeap == NULL) return NULL;

	int* newData = (int*)calloc(size + 1, sizeof(int));
	if (newData == NULL) return NULL;

	newHeap->data = newData;
	newHeap->last_index = 0;

	return newHeap;
}

void swap(heap_t* h, int a, int b) {
	int temp = h->data[a];
	h->data[a] = h->data[b];
	h->data[b] = temp;
}

int parentIndex(int a) {
	return a >> 1;
}

int childIndex(int a) {
	return a << 1;
}

void insert(heap_t* h, int data) {
	if (h == NULL) return;

	h->data[h->last_index + 1] = data;
	h->last_index++;

	if (h->last_index <= 1){
		return;
	}

	int curIndex = h->last_index;
	int pIndex = parentIndex(curIndex);

	while (1) {
		if (data <= h->data[pIndex] || pIndex == 0) {
			break;
		}

		swap(h, parentIndex(curIndex), curIndex);

		curIndex = pIndex;
		pIndex = parentIndex(curIndex);
	}
}

int find_max(heap_t* h) {
	if (h == NULL || h->last_index == 0) {
		return -1;
	}

	return h->data[1];
}

void bfs(heap_t* h) {
	if (h == NULL) return;

	for (int i = 1; i < (h->last_index + 1); i++) {
		printf("%d ", h->data[i]);
	}
	printf("\n");
}

void delete_max(heap_t* h) {
	if (find_max(h) == -1) return;

	h->data[1] = h->data[h->last_index];
	h->data[h->last_index] = 0;
	h->last_index--;

	if (h->last_index <= 1) {
		return;
	}

	int curIndex = 1;
	int newMax = h->data[curIndex];

	int cIndex1 = childIndex(curIndex);
	int cIndex2 = cIndex1 + 1;

	while (1) {
		if (newMax < h->data[cIndex1]) {
			swap(h, curIndex, cIndex1);
			curIndex = cIndex1;
		}
		else if (newMax < h->data[cIndex2]) {
			swap(h, curIndex, cIndex2);
			curIndex = cIndex2;
		}
		else {
			break;
		}

		cIndex1 = childIndex(curIndex);
		cIndex2 = cIndex1 + 1;
	}
}

int find(heap_t* h, int key) {
	if (h == NULL || h->last_index == 0) return -1;

	for (int i = 1; i < (h->last_index + 1); i++) {
		if (h->data[i] == key) {
			return i;
		}
	}
}

void update_key(heap_t* h, int oldKey, int newKey) {
	if (h == NULL) return;

	int index = find(h, oldKey);
	if (index == -1) return;

	h->data[index] = newKey;

	int data = h->data[index];
	int pIndex = parentIndex(index);

	while (1) {
		if (data <= h->data[pIndex] || pIndex == 0) {
			break;
		}

		swap(h, parentIndex(index), index);

		index = pIndex;
		pIndex = parentIndex(index);
	}
}

int main(void) {
	heap_t* max_heap = NULL;

	/*
	max_heap = init_heap(10);
	insert(max_heap, 2);
	insert(max_heap, 3);
	insert(max_heap, 5);
	insert(max_heap, 6);
	insert(max_heap, 1);
	insert(max_heap, 7);
	
	delete_max(max_heap, 5);
	update_key(max_heap, 1, 7);
	bfs(max_heap);
	*/

	int m, n, i;
	int command, data;
	int old_key, new_key;
	scanf("%d %d", &m, &n);
	max_heap = init_heap(m);
	for (i = 0; i < n; i++) {
		scanf("%d", &command);
		switch (command) {
		case 1:
			scanf("%d", &data);
			insert(max_heap, data);
			break;
		case 2:
			delete_max(max_heap);
			break;
		case 3:
			printf("%d\n", find_max(max_heap));
			break;
		case 4:
			scanf("%d %d", &old_key, &new_key);
			update_key(max_heap, old_key,
				new_key);
			break;
		case 5:
			bfs(max_heap);
			break;
		}
	}

	return 0;
}