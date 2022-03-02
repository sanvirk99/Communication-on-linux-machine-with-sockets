#CC=gcc
#CFLAGS=-I.


#%.o: %.c 
	#$(CC) -c -o $@ $< $(CFLAGS)

#main: udpserv.o 
	#$(CC) -o main udpserv.o -lpthread

CFLAGS=-Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror

all: build

build:

	gcc $(CFLAGS) udpserv.c -lpthread -o s-talk;

run: build

	./main

valgrind: build

	valgrind --leak-check=full ./s-talk

clean:

	rm -f s-talk