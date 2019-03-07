#include "mymalloc.h"

void insert(struct memEntry * head, int data)
{
 struct memEntry * temp = NULL;
 temp = myblock[data];
 temp->size = 4096-data;
 temp->isFree = 1;
 temp->next = NULL;
 head->next = temp;
}
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
	} if ((allocate + data) >= 4096) {
		printf("Not enough space left\n");
		return NULL;
	}
	  if (myblock[sizeof(short)]!= magic) {
	  *(short *) block[sizeof(short)]=magic;
	  head = myblock[sizeof(struct memEntry)];
	  head->next = NULL;
	  head->size = x;
	  head->isFree=0;
	  data = sizeof(struct memEntry) + sizeof(short) + head->size;
	  insert(head, data);
	}
	 
	 struct memEntry new = myblock[head->size + sizeof(struct memEntry)];
	 new = head;
	 while(new->isFree==1) {
	 	if(new->size==x) {
	 	  new->isFree=0;
	 	}
	 	else if(new->size > x) {
	 	 int temp = new->size;
	 	 new->size=x;
	 	 insert(new, data)
	 	}
	 new = new->next;
	 data = sizeof(struct memEntry) + new->size;
	}
}

       




int main (int argc, char** argv) {
	mymalloc(1, "alack", 2);
}
