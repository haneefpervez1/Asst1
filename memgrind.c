#include "mymalloc.h"

void workLoadA() {
	int i = 0;
	for (i = 0; i < 150; i++) {
		malloc(1);
		free(1);
	}
}
void workLoadB() {
 void * arr[3000];
 int i,mallCount;
 mallCount=0;
 for(i=0;i<150;i++){
  arr[i] = malloc[1];
  mallCount ++;
  	if(mallCount==50){ 
  	   break;
 	}
 }
 for(i=0;i<150;i++){
  free(arr[i]);
 }
}
