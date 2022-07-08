main:
	$(CC) main.c -O3 -o trash

clean:
	rm -rf *.o

CC="clang"
