CC=gcc
CFLAGS=-fPIC -Wall
LDFLAGS=-shared
LDLIBS=-ldl

.PHONY: all clean run

all: main libexample.so

libexample.so: libexample.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

main: main.c libexample.so
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

run: all
	LD_LIBRARY_PATH=. ./main

clean:
	rm -f main *.so
