CC=gcc
CFLAGS=-I.


%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

s-talk: udpclient.o 
	$(CC) -o s-talk udpclient.o -lpthread