
CFLAGS=-Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L 

all: build

build:

	gcc $(CFLAGS) main.c functions.c sender.c receiver.c output.c input.c list.c -lpthread -o coms;

run: build

	./main

valgrind: build

	valgrind --leak-check=full ./coms

clean:

	rm -f s-talk