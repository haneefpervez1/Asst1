#include "mymalloc.h"

void* mymalloc(int x, char* file, int line) {
	struct memEntry * head = NULL;
	short magic=1999;
	if (x <= 0){
		printf("Enter a valid number to malloc\n");
		return NULL;
	} if ((x + sizeof(struct memEntry)) >= 4096)
	 {
		printf("%d is too large\n");
		return NULL;
	}
	  if ( *(short *)myblock!= magic) {
	  *(short *)&myblock=magic;
	  head = (struct memEntry*)&myblock; // myblock
	  head->next = NULL;
	  head->size = 4096 - sizeof(struct memEntry);
	  head->isFree=1;
	  //data = sizeof(struct memEntry) + sizeof(short) + head->size;
	  //insert(head, data);
	}
	 
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
		 	  
		 	  struct memEntry* next = (struct memEntry*) ptr;
		 	  next->size = size_remain - sizeof(struct memEntry);
		 	  next->next = new->next;
		 	  new->next = next;
	 	  }
	 	  break;
	 	}
	 new = new->next;
	}
	if(new==NULL)
	{
	 return NULL;
	}
	
	char* ret = (char*)new;
	ret = ret + sizeof(struct memEntry);
	
	return (void *)(ret);
}

void* myfree(void* F, char* file, int line) {
	short magic = 1999;
	if ( *(short*)myblock != magic) {
		printf("trying to free something that has not been malloced\n");
		return NULL;
	}
	
	/* The code below is to determine the MetaData's isFree bit to see if the data is allocated.
	   The ptr location gets decremented by size of struct memEntry to point to the beginning of the struct 
	   allowing us to access the isFree field and determine if it isFree memory or not. If it is, then flip the bit and return the original pointer.
	   if not, examine the entire linked list for a match where no match returns NULL.
	*/
	char * ptr = (char *) F;
	ptr = ptr-sizeof(struct memEntry);
	struct memEntry * free_ptr = (struct memEntry *) ptr;
	if(free_ptr->isFree=0)
	{
	 free_ptr->isFree=1;
	}
	else
	{
	 
	}
	printf("%d\n", myblock[sizeof(short)]);
	
}        

void mergeMetadata() {
	struct memEntry* head = (struct memEntry*)&myblock[sizeof(struct memEntry)];
	while (head->next != NULL) 
	{
		if (head->isFree == 1 && head->next->isFree == 1) 
		{
			int tempSize = head->next->size;
			head->size = head->size + tempSize;
			head->next = head->next->next;
			head = head->next;
			continue;
		}
		head = head->next;
	}
}


int main (int argc, char** argv) {
	mymalloc(1, "alack", 2);
}
