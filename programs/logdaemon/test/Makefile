all: check

check:
	$(CC) -c ../src/logdaemon.c ../src/util.c *.c
	$(CC) *.o -lcheck -o check

tags:
	etags *

clean:
	rm -rf *.o check