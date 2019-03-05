#include "mymalloc.h"

void* mymalloc(int x, char* file, int line) {
	int dataUsed = 0;
	int allocate = x;
	if (allocate <= 0){
		printf("Enter a valid number to malloc\n");
		return NULL;
	} if ((allocate + sizeof(struct memEntry)) >= 4096) {
		printf("%d is too large\n");
		return NULL;
	} if ((allocate + dataUsed) >= 4096) {
		printf("Not enough space left\n");
		return NULL;
	}
}

int main (int argc, char** argv) {
	mymalloc(1, "alack", 2);
}
