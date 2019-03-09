#include "mymalloc.h"

/*void workLoadA() {
	int i = 0;
	for (i = 0; i < 150; i++) {
		void *a =malloc(1);
		free(a);
	}
}*/
void workLoadB() {
	void * arr[3000];
	int i,malloc_Count;
	malloc_Count=0;
	for(i=0;i<150;i++){
		arr[i] = malloc(1);
		malloc_Count ++;	
	   	if(malloc_Count==50){ 
			break;
 		}
 	}
 	for(i=0;i<150;i++){
  	free(arr[i]);
 	}
}
void workLoadC() {
	void * arr[5000];
	int allocated, index=0;
	printf("%f\n", arr[index]);
	while(allocated!=50){
		int a = (rand() % 2);
		if(a==0 && index!=5000){	// Malloc as long as index is not 5000
		 arr[index]=malloc(1);
		 index++;
		 allocated++;
		}
		else if (a==1 && index!=0){		//Free as Long as there is a pointer to free
		 int f = (rand() % index+1);
		 void * temp = arr[index];		 
		 free(arr[f]);
		 arr[f]=NULL;
		 arr[index] = arr[f];
		 arr[f] = temp;
		 index--;
		}
	}
	while(index!=0){
	 	 int f = (rand() % index+1);
		 void * temp = arr[index];		 
		 free(arr[f]);
		 arr[f]=NULL;
		 arr[index] = arr[f];
		 arr[f] = temp;
		 index--;
	}
}

void workLoadD() {
	printf("workload d\n");
	void* arr[5000];
	int numMallocs = 0, index = 0;
	while (numMallocs != 50) {
		int operation = rand() % (2);
		if (operation == 0) printf("mallocing ");
		else printf("freeing\n");
		if (operation == 0) {
			int numBytes = rand() % (64+1-1)+1;
			printf("%d bytes\n", numBytes);
			void* allocatePtr = malloc(numBytes);
			arr[index] = allocatePtr;
			index++;
			numMallocs++;
		} else {
			int freeIndex = rand() % (index+1);
			free(arr[freeIndex]);
		}
	}
	printf("end workload d\n");
}

void workLoadE() {
	void * arr[3];
	int i;
	for(i=0;i<3;i++){
	 arr[i]=malloc(10);
	}
	free(arr[2]);
	free(arr[1]);
	free(arr[0]);
}

void workLoadF() {	

}

/*int main(int argc, char** argv){
	//workLoadC();
	//workLoadF();
	//workLoadD();
	workLoadA();
	void* a = mymalloc(10, "alack", 2);
	void* b = mymalloc(20, "alack", 2);
	myfree(b, "alack", 1);
	void* c = mymalloc(30, "alack", 2);
	myfree(c, "alack", 2);
	void* d = mymalloc(60, "alack", 2);
	void* e = mymalloc(10, "alack",2);
	return 0;
}*/

