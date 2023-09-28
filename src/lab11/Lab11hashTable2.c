#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEXTSIZE 21
typedef char* item_t;
typedef struct hash {
	item_t* table;
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

unsigned probeFunction(unsigned int i) {
	return (i + i * i) / 2;
}

unsigned probeEmpty(hash_t* h, char* str) {
	unsigned int index = 0;
	unsigned int i = 0;

	while (1) {
		index = (hashFunction(h->hash_key, str, strlen(str)) + probeFunction(i)) % h->size;
		if (h->table[index] == NULL) {
			return index;
		}
		i++;
	}
}

hash_t* init_hashtable(int size, int key) {
	hash_t* newHash = (hash_t*)malloc(sizeof(hash_t));
	if (newHash == NULL) return NULL;

	item_t* newTable = (item_t*)calloc(size, sizeof(item_t*));
	if (newTable == NULL) return NULL;

	newHash->hash_key = key;
	newHash->size = size;
	newHash->table = newTable;

	return newHash;
}

void insert(hash_t* h, char* text) {
	if (h == NULL) return;

	unsigned int index = probeEmpty(h, text);

	item_t* newItem = (item_t*)malloc(sizeof(item_t));
	if (newItem == NULL) return;

	strcpy(newItem, text);

	h->table[index] = newItem;
}

int strCompare(char* str1, char* str2) {
	if (strlen(str1) != strlen(str2)) return 0;

	for (int i = 0; i < strlen(str1); i++) {
		if (str1[i] != str2[i]) {
			return 0;
		}
	}
	return 1;
}

int search(hash_t* h, char* text) {
	if (h == NULL) return -1;

	unsigned int index = 0;
	unsigned int i = 0;
	int length = strlen(text);

	while (i < h->size) {
		index = (hashFunction(h->hash_key, text, length) + probeFunction(i)) % h->size;
		if (h->table[index] != NULL && strCompare(h->table[index], text)) {
			return index;
		}
		i++;
	}

	return -1;
}

int main(void) {
	hash_t* hashtable = NULL;

	/*
	hashtable = init_hashtable(13, 19);

	insert(hashtable, "qwert");
	printf("%d\n", search(hashtable, "qwert"));
	*/

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