#include "mymalloc.h"
/*
	This is our mymalloc function. It takes a size to malloc, a file name, and line number.
*/
void* mymalloc(int x, char* file, int line) {
	//printf("memEntry size %d\n", sizeof(struct memEntry));
	struct memEntry *head;
	short magic=1999;									// This is the magic number to check if the malloc call is the first malloc or not
	//printf("magic number size %d\n", sizeof(magic));
	if (x <= 0){										// Returns NULL if user tries to malloc an invalid number (0 or negative number)
		printf("Enter a valid number to malloc\n");
		return NULL;
	} if ((x + sizeof(struct memEntry)) >= 4096)		// Returns NULL if user tries to malloc something that is too large to fit in myblock
	 {
		printf("%d is too large\n", x);
		return NULL;
	}
	
	  if ( *(short *)myblock!= magic) {					// This part checks if it is the first malloc,
		*((short*)myblock) = magic;						// if it is it adds the magic number to the beginning of 
	 // *(short *)&myblock=magic;						// myblock and adds the first metadata
		printf("short %d\n", *((short*)myblock));
	  head = (struct memEntry*)&myblock[sizeof(struct memEntry)]; // myblock
	  head->next = NULL;
	  head->size = 4096 - sizeof(struct memEntry) - sizeof(short);
	  head->isFree=1;
	  //struct memEntry* temp = head;
		/*
	  while (temp != NULL) {
		printf("size: %d isFree: %d \n", temp->size, temp->isFree);
		temp = temp->next;
	}
	*/
	} else {
		head = (struct memEntry*)&myblock[sizeof(struct memEntry)];
	}
	 printf("inserting %d\n", x);
	 struct memEntry* new = head;
	 while(new != NULL) {
	 	if(new->size>=x && new->isFree==1) {				// if there has been a previous malloc call that has been freed and can
	 	  new->isFree=0;									// fit the size of the new malloc call it will be added here
	 	  int size_remain = new->size - x;	 	  
	 	  new->size = x;
	 	  
	 	  if( size_remain > sizeof(struct memEntry) + 1 )	// if a new memEntry needs to be created
	 	  {	 	  
		 	  char* ptr = (char *)new;						// moving a char ptr to the right place
		 	  ptr = ptr + sizeof(struct memEntry);			
		 	  ptr = ptr + new->size;
		 	  
		 	  struct memEntry* nextNode = (struct memEntry*) ptr;		// adding the new metadata and allocating the space
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
	ret = ret + sizeof(struct memEntry);	// moving the ptr to the start of the allocated spaces
	
	return (void *)(ret);					// returning the void ptr
}
/*
	This is our free function. It takes a void ptr that is going to be freed, a file, and a line number
*/
void myfree(void* F, char* file, int line) {
	short magic = 1999;							// the magic number to check if something has been malloced already
	//*((short*)myblock) = magic;
	//printf("%d\n", *(short*)myblock);
	if ( *(short*)myblock != magic) {			// the magic number is not in myblock meaning no mallocs have been made yet
		printf("trying to free something that has not been malloced\n");
		return;
	}
	if(F==NULL){								// the pointer given is NULL
		printf("pointer F is NULL. Cannot free NULL pointer\n");
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
	struct memEntry* head = (struct memEntry*)&myblock[sizeof(struct memEntry)];
	if(free_ptr->isFree==0)
	{
	 free_ptr->isFree=1;
	}
	else
	{
	 traversal(head, F);
	}
	//printf("%d\n", myblock[sizeof(short)]);
	mergeMetadata();			// merges adjacent free nodes
	while (head != NULL) {
		printf("size: %d isFree %d \n", head->size, head->isFree);
		head = head->next;
	}
	return;
}        
/*
	This function traverses through the metadata and if two consective metadatas are free, merges them into one 
*/
void mergeMetadata() {
	struct memEntry* head = (struct memEntry*)&myblock[sizeof(struct memEntry)];  // starting from the first metadata
	//printf("merge %d\n", head->size);
	struct memEntry* temp = head;
	while (temp != NULL) 
	{
		if (temp->isFree == 1 && temp->next->isFree == 1 ) 
		{
		/*
			This part combines two free nodes into one
		*/
			//printf("first free %d second free %d\n", temp->size, temp->next->size);
			int tempSize = temp->next->size;
			temp->size = temp->size + tempSize + sizeof(struct memEntry);
			struct memEntry* tempNode = temp->next;
			printf("node %d will be set to null\n", tempNode->size);
			tempNode = NULL;
			temp->next = temp->next->next;
			temp = temp->next;
			continue;
		}
		temp = temp->next;
	}
}
void traversal(struct memEntry * head, void * ptr)
{
	struct memEntry * P = head;
 	while (P!=NULL){
 	 struct memEntry* free_ptr = NULL;
	 free_ptr = (struct memEntry*)(P + sizeof(struct memEntry));
	 	if (free_ptr == ptr)
	 	{
	 	 	if(free_ptr->isFree=0)
	 	 	{
	 	 	 free_ptr->isFree=1;
	 	 	}
	 	}
	  P=P->next;	
	 }	
}

/*
int main (int argc, char** argv) {
	
	mymalloc(10, "alack", 2);
	void* a = mymalloc(20, "alack", 2);
	myfree(a, "alack", 1);
	void* b = mymalloc(30, "alack", 2);
	myfree(b, "alack", 2);
	mymalloc(60, "alack", 2);
	mymalloc(10, "alack",2);
	
	printf("in mymalloc\n");
	void* a = mymalloc(10, "alack", 2);
	void* b = mymalloc(20, "alack", 2);
	myfree(b, "alack", 1);
	void* c = mymalloc(30, "alack", 2);
	myfree(c, "alack", 2);
	void* d = mymalloc(60, "alack", 2);
	void* e = mymalloc(10, "alack",2);
	return 0;
	
	//workLoadB();
}*/
