
CFLAGS=-Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L 

all: build

build:

	gcc $(CFLAGS) udpserv.c console.c functions.c sender.c receiver.c output.c input.c list.c -lpthread -o s-talk;

run: build

	./main

valgrind: build

	valgrind --leak-check=full ./s-talk

clean:

	rm -f s-talk