#include "mymalloc.h"

void workLoadA() {
	int i = 0;
	for (i = 0; i < 150; i++) {
		void *a =malloc(1);
		free(a);
	}
}
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
	int allocated, malloc_count, index=0;
	while(allocated!=50){
		int a = (rand() % 2);
		if(a==0){	// Malloc
		 arr[index]=malloc(1);
		 index++;
		 allocated++;
		 malloc_count++;
		}
		else {				//free
		 int f = (rand() % index+1);
		 free(arr[f]);
		}
	}
	while(malloc_count!=0){
		
	}
}

void workLoadD() {

}

void workLoadE() {

}

void workLoadF() {

}

int main(int argc, char** argv){
	workLoadC();
	return 0;
}
