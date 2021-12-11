CC=gcc
CFLAGS=-Wall -g
all:
	$(CC) $(CFLAGS) Principal.c -o labhilos -lpthread
clear:
	rm principal	