#include "mymalloc.h"

void workLoadA() {
	int i = 0;
	for (i = 0; i < 150; i++) {
		malloc(1);
		free(1);
	}
}
