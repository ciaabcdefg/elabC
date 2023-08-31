#include <stdio.h>
#include <stdlib.h>

int getIndexFromKey(int**, int, int, int);
int getUniqueCount(int*, int);
int* fromIndex2D(int**, int, int, int);
int** uniqueDict(int*, int, int);

void sort(int*, int);

int main(void) {
	int numEntries;
	(void)scanf("%d", &numEntries);

	int* entries = (int*)calloc(numEntries, sizeof(int));
	if (!entries) return;

	for (int i = 0; i < numEntries; i++) {
		(void)scanf("%d", &entries[i]);
	}

	int uniqueCount = getUniqueCount(entries, numEntries);
	int** dict = uniqueDict(entries, numEntries, uniqueCount);

	int maxOccurances = 0;
	for (int i = 0; i < uniqueCount; i++) {
		int occurances = (int)*fromIndex2D(dict, 2, i, 1);
		if (occurances > maxOccurances) {
			maxOccurances = occurances;
		}
	}

	int mostCommonValuesCount = 0;
	for (int i = 0; i < uniqueCount; i++) {
		int occurances = (int)*fromIndex2D(dict, 2, i, 1);

		if (occurances == maxOccurances) {
			mostCommonValuesCount += 1;
		}
	}

	int* mostCommonValues = (int*)calloc(mostCommonValuesCount, sizeof(int));
	if (!mostCommonValues) return;

	int currentIndex = 0;

	for (int i = 0; i < uniqueCount; i++) {
		int occurances = (int)*fromIndex2D(dict, 2, i, 1);

		if (occurances == maxOccurances) {
			int uniqueNumber = (int)*fromIndex2D(dict, 2, i, 0);

			mostCommonValues[currentIndex] = uniqueNumber;
			currentIndex++;
		}
	}

	sort(mostCommonValues, mostCommonValuesCount);

	for (int i = 0; i < mostCommonValuesCount; i++) {
		printf("%d ", mostCommonValues[i]);
	}

	free(entries);
	free(dict);
	free(mostCommonValues);

	return 0;
}

int getIndexFromKey(int** arr, int sizeY, int sizeX, int targetKey) {
	for (int i = 0; i < sizeY; i++) {
		int key = (int)*fromIndex2D(arr, sizeX, i, 0);
		if (key == targetKey) {
			return i;
		}
	}
	return -1;
}

int getUniqueCount(int* entries, int numEntries) {
	int currentUnique = -1;
	int uniqueCount = 0;

	for (int i = 0; i < numEntries; i++) {
		if (entries[i] != currentUnique) {
			uniqueCount += 1;
			currentUnique = entries[i];
		}
	}

	return uniqueCount;
}

int* fromIndex2D(int** arr, int sizeX, int y, int x) {
	return &arr[sizeX * y + x];
}

int** uniqueDict(int* entries, int numEntries, int uniqueCount) {
	int** dict;
	dict = calloc(uniqueCount * 2, sizeof(*dict));
	if (!dict) return;

	int currentUnique = -1;
	int uniqueIndex = -1;

	for (int i = 0; i < numEntries; i++) {
		if (entries[i] != currentUnique) {
			int index = getIndexFromKey(dict, uniqueCount, 2, entries[i]);

			if (index == -1) {
				currentUnique = entries[i];
				uniqueIndex += 1;
				*fromIndex2D(dict, 2, uniqueIndex, 0) = currentUnique;
			}
			else {
				*fromIndex2D(dict, 2, index, 1) += 1;
				continue;
			}
		}
		*fromIndex2D(dict, 2, uniqueIndex, 1) += 1;
	}

	return dict;
}

void sort(int* arr, int length) {
	int i, key, j;
	for (i = 1; i < length; i++) {
		key = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}






