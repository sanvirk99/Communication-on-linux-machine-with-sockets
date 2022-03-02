CC=gcc
CFLAGS=-I.


%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

main: udpclient.o 
	$(CC) -o main udpclient.o -lpthread