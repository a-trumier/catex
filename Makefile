.PHONY: all folders clean

# change if you have different compilers
CC=gcc
CFLAGS=-Wall -Wextra


all: dynamic static
	cp build/lib* include/

dynamic: folders fpiccatex.o
	$(CC) --shared -o build/libcatex.so build/fpiccatex.o

static: folders catex.o
	ar rcs build/libcatex.a build/catex.o

catex.o: src/catex.c include/catex.h
	$(CC) -c -o build/catex.o $(CFLAGS) src/catex.c

fpiccatex.o: src/catex.c include/catex.h
	$(CC) -c -fpic $(CFLAGS) -o build/fpiccatex.o src/catex.c

folders:
	mkdir -p build/

clean:
	rm build/* include/lib*; rmdir build
