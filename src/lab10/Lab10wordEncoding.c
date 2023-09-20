#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dict {
	int frequency;
	char string[16];

	struct dict* left;
	struct dict* right;
} dict_t;

typedef struct heap {
	dict_t** data;
	int last_index;
} heap_t;

heap_t* init_heap(int size) {
	heap_t* newHeap = (heap_t*)malloc(sizeof(heap_t));
	if (newHeap == NULL) return NULL;

	dict_t** newDict = (dict_t**)calloc(size + 1, sizeof(dict_t*));
	if (newDict == NULL) return NULL;

	newHeap->data = newDict;
	newHeap->last_index = 0;

	for (int i = 0; i < size + 1; i++) {
		newHeap->data[i] = NULL;
	}

	return newHeap;
}

int parentIndex(int a) {
	return a >> 1;
}

int childIndex(int a) {
	return a << 1;
}

void swap(heap_t* h, int a, int b) {
	dict_t* temp = h->data[a];
	h->data[a] = h->data[b];
	h->data[b] = temp;
}

int isNullstring(char* string) {
	if (string[0] == '\0') {
		return 1;
	}
	return 0;
}

void balance(heap_t* h, int frequency) {
	int curIndex = h->last_index;
	int pIndex = parentIndex(curIndex);

	while (1) {
		if (h->data[pIndex] == NULL) {
			break;
		}
		if (frequency >= h->data[pIndex]->frequency || pIndex == 0) {
			break;
		}

		swap(h, parentIndex(curIndex), curIndex);

		curIndex = pIndex;
		pIndex = parentIndex(curIndex);
	}
}

void insert(heap_t* h, char* string, int frequency) {
	if (h == NULL) return;

	h->last_index++;

	dict_t* newDict = (dict_t*)malloc(sizeof(dict_t));
	if (newDict == NULL) return;

	newDict->frequency = frequency;
	newDict->left = NULL;
	newDict->right = NULL;
	memset(newDict->string, '\0', 16);
	strcpy(newDict->string, string);

	h->data[h->last_index] = newDict;

	if (h->last_index <= 1) {
		return;
	}

	balance(h, frequency);
}

void insertDict(heap_t* h, dict_t* newDict) {
	if (h == NULL) return;

	h->last_index++;
	h->data[h->last_index] = newDict;

	balance(h, newDict->frequency);
}

int find_min(heap_t* h) {
	if (h == NULL || h->last_index == 0) {
		return -1;
	}

	return h->data[1]->frequency;
}

dict_t* delete_min(heap_t* h) {
	if (find_min(h) == -1) return;

	dict_t* popped = h->data[1];

	h->data[1] = h->data[h->last_index];
	h->data[h->last_index] = NULL;

	h->last_index--;

	if (h->last_index <= 1) {
		return popped;
	}

	int curIndex = 1;
	dict_t* newMin = h->data[curIndex];

	int cIndex1 = childIndex(curIndex);
	int cIndex2 = cIndex1 + 1;

	while (1) {
		if (cIndex1 > h->last_index && cIndex2 > h->last_index) {
			break;
		}

		int chosenIndex = -1;

		if (cIndex1 > h->last_index && cIndex2 <= h->last_index) {
			chosenIndex = cIndex2;
		}
		else if (cIndex2 > h->last_index && cIndex1 <= h->last_index) {
			chosenIndex = cIndex1;
		}
		else {
			if (h->data[cIndex2]->frequency < h->data[cIndex1]->frequency) {
				chosenIndex = cIndex2;
			}
			else {
				chosenIndex = cIndex1;
			}
		}

		if (chosenIndex == -1){
			break;
		}

		if (h->data[chosenIndex] != NULL && (newMin->frequency > h->data[chosenIndex]->frequency)) {
			swap(h, curIndex, chosenIndex);
			curIndex = chosenIndex;
		}
		else {
			break;
		}

		cIndex1 = childIndex(curIndex);
		cIndex2 = cIndex1 + 1;
	}

	return popped;
}

void dfs(dict_t* d) {
	if (d == NULL) {
		return;
	}

	if (isNullstring(d->string)) {
		printf(" %d ", d->frequency);
	}
	else
	{
		printf("%s ", d->string);
	}
	
	dfs(d->left);
	dfs(d->right);
}

void printDict(dict_t* d) {
	printf("(%d) ->", d->frequency);
	dfs(d);
	printf("\n");
}

void bfs(heap_t* h) {
	if (h == NULL) return;

	for (int i = 1; i < (h->last_index + 1); i++) {
		if (isNullstring(h->data[i]->string)) {
			printDict(h->data[i]);
		}
		else {
			printf("(%s, %d)\n", h->data[i]->string, h->data[i]->frequency);
		}
	}
}

void huffman(heap_t* h) {
	dict_t* pop1 = delete_min(h);
	dict_t* pop2 = delete_min(h);

	dict_t* filler = (dict_t*)malloc(sizeof(dict_t));
	if (filler == NULL) return;

	filler->frequency = pop1->frequency + pop2->frequency;
	strcpy(filler->string, "\0");

	filler->left = pop1;
	filler->right = pop2;

	insertDict(h, filler);
}

void readHuffman(dict_t* d, char* prevString) {
	if (d->left == NULL && d->right == NULL) {
		printf("%s: %s\n", d->string, prevString);
		return;
	}
	
	readHuffman(d->left, strcat(prevString, "0"));
	prevString[strlen(prevString) - 1] = '\0';
	readHuffman(d->right, strcat(prevString, "1"));
	prevString[strlen(prevString) - 1] = '\0';
}

int main() {
	heap_t* h = NULL;
	int n, m;
	
	(void)scanf("%d", &n);

	h = init_heap(n);

	for (int i = 0; i < n; i++) {
		char input[16];
		(void)scanf("%s %d", &input, &m);

		insert(h, input, m);
	}

	while (h->last_index != 1) {
		huffman(h);
	}

	char* displayStr = (char*)calloc(n + 1, sizeof(char));
	readHuffman(h->data[1], displayStr);

	return 0;
}