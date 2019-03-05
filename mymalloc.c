#include "mymalloc.h"

void* my_malloc(x) {
	int dataUsed = 0;
	int allocate = x;
	if (allocate <= 0){
		printf("Enter a valid number to malloc\n");
		return NULL;
	} if ((allocate + sizeof(memEntry)) >= 4096) {
		printf("%d is too large\n");
		return NULL;
	} if ((allocate + dataUsed) >= 4096) {
		printf("Not enough space left\n");
		return NULL;
	}
}


