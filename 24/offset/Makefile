CC=gcc
CFLAGS=-fPIC -Wall
LDFLAGS=-shared
LDLIBS=-ldl

.PHONY: all clean run

all: main libmathops.so libmathuser.so

libmathops.so: libmathops.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

libmathuser.so: libmathuser.c libmathops.so
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< -L. -lmathops

main: main.c libmathuser.so
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

run: all
	LD_LIBRARY_PATH=. ./main

clean:
	rm -f main *.so
