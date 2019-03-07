#include "mymalloc.h"

void insert(struct memEntry * head, int data)
{
 struct memEntry * temp = NULL;
 temp = (struct memEntry*)&myblock[data];
 temp->size = 4096-data;
 temp->isFree = 1;
 temp->next = NULL;
 head->next = temp;
}
void* mymalloc(int x, char* file, int line) {
	struct memEntry * head = NULL;
	short magic=1999;
	int data = 0;
	if (x <= 0){
		printf("Enter a valid number to malloc\n");
		return NULL;
	} if ((x + sizeof(struct memEntry)) >= 4096) {
		printf("%d is too large\n");
		return NULL;
	} if ((x + data) >= 4096) {
		printf("Not enough space left\n");
		return NULL;
	}
	  if (myblock[sizeof(short)]!= magic) {
	  *(short *)&myblock[sizeof(short)]=magic;
	  head = (struct memEntry*)&myblock[sizeof(struct memEntry)];
	  head->next = NULL;
	  head->size = x;
	  head->isFree=0;
	  data = sizeof(struct memEntry) + sizeof(short) + head->size;
	  insert(head, data);
	}
	 
	 struct memEntry* new = (struct memEntry*)&myblock[head->size + sizeof(struct memEntry)];
	 new = head;
	 while(new->isFree==1) {
	 	if(new->size==x) {
	 	  new->isFree=0;
	 	  break;
	 	}
	 	else if(new->size > x) {
	 	 int temp = new->size;
	 	 new->size=x;
	 	 insert(new, data);
	 	 new->isFree=0;
	 	 break;
	 	}
	 new = new->next;
	 data = sizeof(struct memEntry) + new->size;
	}
	return (void *)(new + sizeof(struct memEntry));
}

void* myfree(int x, char* file, int line) {
	short magic = 1999;
	if (myblock[sizeof(short)] != magic) {
		printf("trying to free something that has not been malloced\n");
		return NULL;
	}
	printf("%d\n", myblock[sizeof(short)]);
	
}        

void mergeMetadata() {
	struct memEntry* head = (struct memEntry*)&myblock[sizeof(struct memEntry)];
	while (head->next != NULL) {
		if (head->isFree == 1 && head->next->isFree == 1) {
			int tempSize = head->next->size;
			head->size = head->size + tempSize;
			head->next = head->next->next;
			head = head->next;
		}
		head = head->next;
	}
}


int main (int argc, char** argv) {
	mymalloc(1, "alack", 2);
}
