all: first
first: mymalloc.c
	-gcc -O -g -o mymalloc mymalloc.c
clean: rm -rf mymalloc
