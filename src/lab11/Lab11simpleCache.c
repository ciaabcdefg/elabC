#include <stdio.h>
#include <stdlib.h>
typedef struct cell {
	int data;
	int mem_addr;
} cell_t;
typedef struct hash {
	cell_t* table;
	int cache_size;
} hash_t;
typedef hash_t cache_t;
typedef int memory_t;

memory_t* init_memory(int size) {
	memory_t* memory = (memory_t*)malloc(
		sizeof(memory_t) * size);
	int i = 0;
	// Randomly assign integers to memory
	for (i = 0; i < size; i++)
		memory[i] = rand();
	return memory;
}

unsigned cacheIndex(cache_t* c, int address) {
	if (c == NULL) return;

	return address % c->cache_size;
}

cache_t* init_cache(int size) {
	cache_t* cache = (cache_t*)malloc(sizeof(cache_t));
	if (cache == NULL) return NULL;

	cell_t* newTable = (cell_t*)calloc(size, sizeof(cell_t));
	if (newTable == NULL) return NULL;

	cache->cache_size = size;
	cache->table = newTable;

	for (int i = 0; i < size; i++) {
		cache->table[i].data = -1;
		cache->table[i].mem_addr = -1;
	}

	return cache;
}

void printMemory(memory_t* mem, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d, ", mem[i]);
	}
	printf("\n");
}

void printCache(cache_t* cache) {
	for (int i = 0; i < cache->cache_size; i++) {
		printf("(%d, %d), ", cache->table[i].data, cache->table[i].mem_addr);
	}
	printf("\n");
}

void get_data(int address, memory_t* memory, cache_t* cache) {
	if (memory == NULL || cache == NULL) return;

	int index = cacheIndex(cache, address);

	if (cache->table[index].mem_addr == -1) {
		printf("Load from memory\n");
	}
	else if (cache->table[index].mem_addr == address) {
		printf("Address %d is loaded\n", address);
	}
	else {
		printf("Index: %d is used\n", index);
		printf("Load from memory\n");
	}

	cache->table[index].data = memory[address];
	cache->table[index].mem_addr = address;
	printf("Data: %d\n", cache->table[index].data);
}

int main(void) {
	memory_t* memory = NULL;

	/*
	int memSize = 100;
	int cacheSize = 10;

	memory = init_memory(memSize);
	cache_t* cache = init_cache(cacheSize);

	get_data(10, memory, cache);
	get_data(20, memory, cache);
	get_data(20, memory, cache);
	*/

	cache_t* cache = NULL;
	int memory_size, cache_size;
	int i, n, addr;
	scanf("%d %d %d", &memory_size,
		&cache_size, &n);
	memory = init_memory(memory_size);
	cache = init_cache(cache_size);
	for (i = 0; i < n; i++) {
		printf("Load address: ");
		scanf("%d", &addr);
		get_data(addr, memory, cache);
	}

	return 0;
}