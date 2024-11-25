.PHONY: all folders clean

# change if you have different compilers
CC=gcc
CFLAGS=-Wall -Wextra

# normal build config.
all: dynamic static
	mv build/lib* include/

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
	rm -rf build/* include/lib* testshared teststatic build;

# testing config. remove before version 1

testing: all testshared teststatic
	ln -sf build/tests* .

# remember to export LD_LIBRARY_PATH for this to work.
testshared: test.o
	$(CC) -g -o build/testshared -L./include -lcatex build/test.o

teststatic: test.o
	$(CC) -g -I./include -o build/teststatic build/test.o include/libcatex.a

test.o: src/test.c
	$(CC) $(CFLAGS) -c -o build/test.o src/test.c
