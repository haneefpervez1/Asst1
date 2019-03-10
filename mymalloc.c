#include "mymalloc.h"
/*
	This is our mymalloc function. It takes a size to malloc, a file name, and line number.
*/
void* mymalloc(int x, char* file, int line) {
	struct memEntry *head;
	short magic=1999;								// This is the magic number to check if the malloc call is the first malloc or not
	if (x <= 0){									// Returns NULL if user tries to malloc an invalid number (0 or negative number)
		printf("Located in file %s, line %d,Enter a valid number to malloc\n", file, line);
		return NULL;
	} if ((x + sizeof(struct memEntry)) >= 4096){		// Returns NULL if user tries to malloc something that is too large to fit in myblock
		printf("Located in file %s, line %d, %d is too large for memory allocation \n", file, line, x);
		return NULL;
	}
	  if ( *(short *)myblock!= magic) {				// This part checks if it is the first malloc,
		*((short*)myblock) = magic;				// if it is it adds the magic number to the beginning of myblock and adds the first metadata
		//printf("short %d\n", *((short*)myblock));
	  	head = (struct memEntry*)&myblock[sizeof(struct memEntry)]; // myblock
	  	head->next = NULL;
	  	head->size = 4096 - sizeof(struct memEntry) - sizeof(short);
	  	head->isFree=1;}
	 else 
	 { 
	 head = (struct memEntry*)&myblock[sizeof(struct memEntry)];
	 }
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
	/*
	The statement below indicates that the size x cannot fit in myblock because there isn't enough space
	Because the "new" node traversed all the way to NULL without fitting the x amount of bytes in any of the memEntries.
	*/
	if(new==NULL)
	{
	 printf("Located in file %s, line %d, Not enough space for %d\n", file, line, x);
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
	if ( *(short*)myblock != magic) {			// the magic number is not in myblock meaning no mallocs have been made yet
		printf("Located in file %s, line %d,trying to free something that has not been malloced\n", file, line);
		return;
	}
	if(F==NULL){								// the pointer given is NULL
		printf("Located in file %s, line %d,Cannot free a NULL pointer\n", file, line);
		return;
	}
	/* The code below is to determine the MetaData's isFree bit to see if the data is allocated.
	   The ptr location gets decremented by size of struct memEntry to point to the beginning of the struct 
	   allowing us to access the isFree field and determine if it isFree memory or not. If it is, then flip the bit and return the original pointer.
	   if not, examine the entire linked list for a match where no match returns NULL.
	*/
	struct memEntry* free_ptr = NULL;
	free_ptr = (struct memEntry*)(F - sizeof(struct memEntry));
	struct memEntry* head = (struct memEntry*)&myblock[sizeof(struct memEntry)];
	if( (head > free_ptr) || ( (char *) free_ptr > &myblock[4095] ))    		// Invalid pointer not in bounds of static array myblock
	{
		printf("Located in file %s, line %d,Invalid Pointer\n", file, line);
		return;
	} 
	if(free_ptr->isFree==0)
	{
	 free_ptr->isFree=1;
	}
	else
	{
	 traversal(head, F, file, line);
	}
	mergeMetadata();			// merges adjacent free nodes
	return;
}        
/*
	This function traverses through the metadata and if two consective metadatas are free, merges them into one 
*/
void mergeMetadata() {
	struct memEntry* head = (struct memEntry*)&myblock[sizeof(struct memEntry)];  // starting from the first metadata
	struct memEntry* temp = head;
	while (temp->next!= NULL) 
	{
		if (temp->isFree == 1 && temp->next->isFree == 1 ) 
		{
		/*
			This part combines two free nodes into one
		*/
			int tempSize = temp->next->size;
			temp->size += tempSize + sizeof(struct memEntry);
			struct memEntry* tempNode = temp->next;
			temp->next = tempNode->next;
			tempNode->next=NULL;
			tempNode=NULL;
			mergeMetadata();
			continue;
		}
		temp = temp->next;
	}
	/*
	The statement below indicates that the head is the only node pointing to Free memory. 
	Likewise, the head and magic number reset to NULL and 0 to allow for full access to the 4096 bytes once again.
	*/
	if(head->next==NULL)
	{
	 head==NULL;
	 *(short*)myblock=0;
	}
}
/*
	This Traversal function is used to check if the ptr given in free() is indeed a valid pointer pointing to any of the Metadata.
	If no match is found, the ptr is invalid and thus no memory can be free. If so, then that metadata's isFree bit is changed to 1
	indicating that its space is free.
*/
void traversal(struct memEntry * head, void * ptr, char* file, int line)
{
	struct memEntry * P = head;
 	while (P!=NULL){
 	 struct memEntry* free_ptr = NULL;
	 free_ptr = (struct memEntry*)(P + sizeof(struct memEntry));
	 	if (free_ptr == ptr)
	 	{
	 	 	if(free_ptr->isFree==0)
	 	 	{
	 	 	 free_ptr->isFree=1;
	 	 	 return;
	 	 	}
	 	}
	  P=P->next;	
	 }
	 printf("Located in file %s, line %d,Invalid Pointer\n", file, line);	
}
