CC=gcc
CFLAGS=-I.


%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

main: udpserv.o 
	$(CC) -o main udpserv.o -lpthread