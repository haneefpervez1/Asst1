all:test

test:
	gcc -O -g -o mymalloc.c mymalloc

clean:
	rm -rf mymalloc
