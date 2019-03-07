#include "mymalloc.h"

void* mymalloc(int x, char* file, int line) {
	struct memEntry * head = NULL;
	short magic=1999;
	int data = 0;
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
	 if (myblock[sizeof(short)]!= magic)
	 {
	   *(short *) block[sizeof(short)]=magic;
	  head = myblock[sizeof(struct memEntry)];
	  data = sizeof(struct memEntry) + sizeof(short);
	  head->next = NULL;
	  head->size = x;
	 }
	 
	 struct memEntry new = NULL;
	 new = head;
}
       




int main (int argc, char** argv) {
	mymalloc(1, "alack", 2);
}
