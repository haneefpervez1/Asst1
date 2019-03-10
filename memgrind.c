#include "mymalloc.h"

void workLoadA() {
	int i = 0;
	for (i = 0; i < 150; i++) {
		void *a =malloc(1);
		free(a);
	}
}
void workLoadB() {
	void * arr[1000];
	int i,j,malloc_count;
	for(i=0; i<150;i++) {
		
		arr[i]=malloc(1);
		malloc_count++;
		if(malloc_count==50){
			for(j=0;j<50;j++)
			{
			 free(arr[j]);
			 malloc_count--;
			}
		}
 	}
}
void workLoadC() {
	void * arr[5000];
	int i,allocated, index=0;
	printf("%f\n", arr[index]);
	while(allocated!=50){
		int a = (rand() % 2);
		if(a==0 && index!=5000){	// Malloc as long as index is not 5000
		 arr[index]=malloc(1);
		 index++;
		 allocated++;
		}
		else if (a==1 && index!=0){		//Free as Long as there is a pointer to free
		int f = (rand() % index);
			if(f == index-1)
			{
				free(arr[f]);
				arr[f]= 0;
			}
			else
			{		 
		 		free(arr[f]);
				arr[f]=arr[index-1];
		 		arr[index-1] = 0;
			}
		index--;
		}
	}
	for(i=index-1; i>=0;i--)
	{
		free(arr[i]);
	}
}

void workLoadD() {
	printf("workload d\n");
	void* arr[4000];
	int i, numMallocs = 0, index = 0;
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
		} 
		else if(operation==1 && index!=0) {
			int freeIndex = rand() % (index);
			free(arr[freeIndex]);
			if(freeIndex == index-1)
			{
				free(arr[freeIndex]);
				arr[freeIndex]= 0;
			}
			else
			{		 
		 		free(arr[freeIndex]);
				arr[freeIndex]=arr[index-1];
		 		arr[index-1] = 0;
			}
		index--;
		}
	}
	for(i=index;i>=0;i--)
	{
	 free(arr[i]);
	}
	printf("end workload d\n");
}

void workLoadE() {
	void * arr[3];
	int i;
	for(i=0;i<3;i++){
	 arr[i]=malloc(1);
	}
	free(arr[0]);
	free(arr[1]);
	free(arr[2]);
}

void workLoadF() {	
	void* arr[6];
	int i,count=0;
	for(i=0;i<6;i++){
	 count+=15000;
	 arr[i]=malloc(count);
	}
	for(i=5;i>=3;i--)
	{
	 free(arr[i]);
	}
	for(i=0;i<3;i++)
	{
	 free(arr[i]);
	}
}

int main(int argc, char** argv){
	double times[6];
	struct timeval start, end;
	double totalTime;
	int i = 0;
	
	while (i != 100) {
	
		gettimeofday(&start, NULL);
		workLoadA();
		gettimeofday(&end, NULL);
		totalTime = end.tv_usec - start.tv_usec;
		times[0] = times[0] + totalTime;

		gettimeofday(&start, NULL);
		workLoadB();
		gettimeofday(&end, NULL);
		totalTime = end.tv_usec - start.tv_usec;
		times[1] = times[1] + totalTime;
/*
		gettimeofday(&start, NULL);
		workLoadC();
		gettimeofday(&end, NULL);
		totalTime = end.tv_usec - start.tv_usec;
		times[2] = times[2] + totalTime;
		*/
		i++;
	}
	printf("A: %f B: %f C: %f \n", times[0], times[1], times[2]);
	//workLoadE();
	//workLoadC();
	//workLoadF();
	//workLoadD();
	//workLoadA();
	//workLoadB();
	/*void* a = mymalloc(10, "alack", 2);
	void* b = mymalloc(20, "alack", 2);
	myfree(b, "alack", 1);
	void* c = mymalloc(30, "alack", 2);
	myfree(c, "alack", 2);
	void* d = mymalloc(60, "alack", 2);
	void* e = mymalloc(10, "alack",2);*/
	return 0;
}

