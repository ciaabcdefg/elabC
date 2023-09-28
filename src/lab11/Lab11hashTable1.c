#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEXTSIZE 21
typedef struct item {
	char* text;
	struct item* next;
} item_t;
typedef struct hash {
	item_t** table;
	int size;
	int hash_key;
} hash_t;

unsigned hashFunction(int key, char* str, int length) {
	if (length == 0) {
		return 0;
	}

	unsigned int x = (unsigned int)str[length - 1];
	return key * hashFunction(key, str, length - 1) + x;
}

unsigned getHash(int key, char* str, int length, int size) {
	return hashFunction(key, str, length) % size;
}

hash_t* init_hashtable(int size, int key) {
	hash_t* newHash = (hash_t*)malloc(sizeof(hash_t));
	if (newHash == NULL) return NULL;

	item_t** newTable = (item_t**)calloc(size, sizeof(item_t*));
	if (newTable == NULL) return NULL;

	newHash->hash_key = key;
	newHash->size = size;
	newHash->table = newTable;

	return newHash;
}

void insert(hash_t* h, char* text) {
	if (h == NULL) return;

	unsigned int index = getHash(h->hash_key, text, strlen(text), h->size);

	item_t* newItem = (item_t*)malloc(sizeof(item_t));
	if (newItem == NULL) return;

	newItem->next = NULL;

	char* textString = (char*)calloc(TEXTSIZE, sizeof(char));
	if (textString == NULL) return NULL;

	strcpy(textString, text);
	newItem->text = textString;

	if (h->table[index] == NULL) {
		h->table[index] = newItem;
	}
	else {
		item_t* cur = h->table[index];
		while (cur != NULL) {
			if (cur->next == NULL) {
				cur->next = newItem;
				break;
			}
			cur = cur->next;
		}
	}
}

int strCompare(char* str1, char* str2) {
	if (strlen(str1) != strlen(str2)) return -1;

	for (int i = 0; i < strlen(str1); i++) {
		if (str1[i] != str2[i]) {
			return -1;
		}
	}
	return 0;
}

int findItem(item_t* item, char* text) {
	if (item == NULL) return 0;

	item_t* cur = item;
	while (cur != NULL) {
		if (strCompare(cur->text, text) == 0) {
			return 1;
		}
		cur = cur->next;
	}

	return 0;
}

int search(hash_t* h, char* text) {
	if (h == NULL) return -1;

	unsigned int index = getHash(h->hash_key, text, strlen(text), h->size);
	if (h->table[index] == NULL) {
		return -1;
	}
	
	return (findItem(h->table[index], text) == 1) ? index : -1;
}

void printList(item_t* item) {
	item_t* cur = item;
	while (cur != NULL) {
		printf("%s, ", cur->text);
		cur = cur->next;
	}
	printf("\n");
}

int main(void) {
	hash_t* hashtable = NULL;
	char* text = NULL;

	int m, n, i, hash_key;
	int command;
	scanf("%d %d %d", &m, &n, &hash_key);
	hashtable = init_hashtable(m, hash_key);
	text = (char*)malloc(sizeof(char)
		* TEXTSIZE);
	for (i = 0; i < n; i++) {
		scanf("%d %s", &command, text);
		switch (command) {
		case 1:
			insert(hashtable, text);
			break;
		case 2:
			printf("%d\n",
				search(hashtable, text));
			break;
		}
	}

	return 0;
}