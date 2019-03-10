#include <stdio.h>
#include <stdlib.h>
#include <time.h>



#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )

static char myblock[4096];

struct memEntry 
{
int isFree;
int size;
struct memEntry * next;
};
void insert(struct memEntry * head, int data);
void mergeMetadata();
void myfree(void* F, char* file, int line);
void* mymalloc(int x, char* file, int line);
void traversal(struct memEntry * head, void * ptr, char* file, int line);

