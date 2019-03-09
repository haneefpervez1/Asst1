#include "mymalloc.h"
/*void insert(struct memEntry * head, int x)
{
 struct memEntry * node = NULL;
 node = head;
 	while(node->next!=NULL)
 	{
 	 node=node->next;
 	} 
 	 int size_remain = node->size - x;	 	  	 	  
	 if(size_remain > sizeof(struct memEntry) + 1)
	 	  {	 	  
		 	  char* ptr = (char *)node;
		 	  ptr = ptr + sizeof(struct memEntry);
		 	  ptr = ptr + node->size;
		 	  struct memEntry* nextNode = (struct memEntry*) ptr;
		 	  nextNode->size = size_remain - sizeof(struct memEntry);
		 	  nextNode->next = node->next;
		 	  node->next = nextNode;
	 	  }
}*/
void* mymalloc(int x, char* file, int line) {
	//printf("memEntry size %d\n", sizeof(struct memEntry));
	struct memEntry *head;
	short magic=1999;
	//printf("magic number size %d\n", sizeof(magic));
	if (x <= 0){
		printf("Enter a valid number to malloc\n");
		return NULL;
	} if ((x + sizeof(struct memEntry)) >= 4096)
	 {
		printf("%d is too large\n");
		return NULL;
	}
	
	  if ( *(short *)myblock!= magic) {
		*((short*)myblock) = magic;
	 // *(short *)&myblock=magic;
		printf("short %d\n", *((short*)myblock));
	  head = (struct memEntry*)&myblock[sizeof(struct memEntry)]; // myblock
	  head->next = NULL;
	  head->size = 4096 - sizeof(struct memEntry) - sizeof(short);
	  head->isFree=1;
	  //insert(head, x);
	  struct memEntry* temp = head;
		/*
	  while (temp != NULL) {
		printf("size: %d isFree: %d \n", temp->size, temp->isFree);
		temp = temp->next;
	}
	*/
		//printf("short %d\n", *((short*)myblock));
	  //data = sizeof(struct memEntry) + sizeof(short) + head->size;
	  //insert(head, data);
	}
	 printf("inserting %d\n", x);
	 struct memEntry* new = head;
	 while(new != NULL) {
	 	if(new->size>=x && new->isFree==1) {
	 	  new->isFree=0;
	 	  int size_remain = new->size - x;	 	  
	 	  new->size = x;
	 	  
	 	  if( size_remain > sizeof(struct memEntry) + 1 )
	 	  {	 	  
		 	  char* ptr = (char *)new;
		 	  ptr = ptr + sizeof(struct memEntry);
		 	  ptr = ptr + new->size;
		 	  
		 	  struct memEntry* nextNode = (struct memEntry*) ptr;
		 	  nextNode->size = size_remain - sizeof(struct memEntry);
		 	  nextNode->isFree=1;
		 	  nextNode->next = new->next;
		 	  new->next = nextNode;
	 	  }
	 	  break;
	 	}
	 new = new->next;;
	}
	struct memEntry* temp = head;
	while (temp != NULL) {
		printf("size: %d isFree: %d \n", temp->size, temp->isFree);
		temp = temp->next;
	}
	if(new==NULL)
	{
	 printf("new is null\n");
	 return NULL;
	}
	char* ret = (char*)new;
	ret = ret + sizeof(struct memEntry);
	
	return (void *)(ret);
}

void myfree(void* F, char* file, int line) {
	short magic = 1999;
	//*((short*)myblock) = magic;
	//printf("%d\n", *(short*)myblock);
	if ( *(short*)myblock != magic) {
		printf("trying to free something that has not been malloced\n");
		return;
	}
	printf("freeing \n");
	/* The code below is to determine the MetaData's isFree bit to see if the data is allocated.
	   The ptr location gets decremented by size of struct memEntry to point to the beginning of the struct 
	   allowing us to access the isFree field and determine if it isFree memory or not. If it is, then flip the bit and return the original pointer.
	   if not, examine the entire linked list for a match where no match returns NULL.
	*/
	struct memEntry* free_ptr = NULL;
	free_ptr = (struct memEntry*)(F - sizeof(struct memEntry));
	printf("free_ptr %d\n", free_ptr->size);
	if(free_ptr->isFree==0)
	{
	 free_ptr->isFree=1;
	}
	
	//printf("%d\n", myblock[sizeof(short)]);
	mergeMetadata();
	struct memEntry* head = (struct memEntry*)&myblock[sizeof(struct memEntry)];
	while (head != NULL) {
		printf("size: %d isFree %d \n", head->size, head->isFree);
		head = head->next;
	}
	return;
}        

void mergeMetadata() {
	struct memEntry* head = (struct memEntry*)&myblock[sizeof(struct memEntry)];
	printf("merge %d\n", head->size);
	struct memEntry* temp = head;
	while (temp != NULL) 
	{
		if (temp->isFree == 1 && temp->next->isFree == 1 ) 
		{
			printf("first free %d second free %d\n", temp->size, temp->next->size);
			int tempSize = temp->next->size;
			temp->size = temp->size + tempSize;
			//struct memEntry* tempNode = temp->next;
			//tempNode = NULL;
			temp->next = temp->next->next;
			temp = temp->next;
			continue;
		}
		temp = temp->next;
	}
}


int main (int argc, char** argv) {
	mymalloc(10, "alack", 2);
	void* a = mymalloc(20, "alack", 2);
	myfree(a, "alack", 1);
	void* b = mymalloc(30, "alack", 2);
	myfree(b, "alack", 2);
	mymalloc(60, "alack", 2);
	//mymalloc(10, "alack",2);
	
}
