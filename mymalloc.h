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

