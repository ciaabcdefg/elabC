#include <stdio.h>
#include <stdlib.h>

int main(void){
	int *arr = calloc(5, sizeof(int));

	arr[0] = 1;

	printf("%d", arr[0]);
	return 0;
}
