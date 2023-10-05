#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _dict {
	char key[51];
	char value[51];
	struct _dict* next;
} dict;

void swap(char* arr, int a, int b) {
	char temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

void sort(char* arr, int n) {
	for (int i = 1; i < n; i++) {
		for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--) {
			swap(arr, j, j - 1);
		}
	}
}

dict* insert(dict* d, char* key, char* value) {
	dict* newDict = (dict*)malloc(sizeof(dict));
	if (newDict == NULL) return NULL;

	newDict->next = NULL;
	strcpy(newDict->key, key);
	strcpy(newDict->value, value);
	
	if (d == NULL) {
		return newDict;
	}

	dict* cur = d;
	while (cur != NULL) {
		if (cur->next == NULL) {
			break;
		}
		cur = cur->next;
	}
	cur->next = newDict;

	return d;
}

void printMatch(dict* d, char* key) {
	if (d == NULL) return;

	dict* cur = d;
	while (cur != NULL) {
		if (strcmp(key, cur->key) == 0) {
			printf("%s ", cur->value);
		}
		cur = cur->next;
	}
	printf("\n");
}

void printAll(dict* d) {
	if (d == NULL) return;

	dict* cur = d;
	while (cur != NULL) {
		printf("(\"%s\": \"%s\"), ", cur->key, cur->value);
		cur = cur->next;
	}
	printf("\n");
}

int main(void) {
	dict* wordDict = NULL;

	int n, m = 0;
	(void)scanf("%d", &n);
	(void)scanf("%d", &m);

	for (int i = 0; i < n; i++) {
		char input[51];
		char key[51];

		(void)scanf("%s", input);

		strcpy(key, input);
		sort(key, strlen(key));

		wordDict = insert(wordDict, key, input);
	}

	for (int i = 0; i < m; i++) {
		char input[51];
		char key[51];

		(void)scanf("%s", input);
		strcpy(key, input);
		sort(key, strlen(key));

		printMatch(wordDict, key);
	}

	return 0;
}