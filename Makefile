CC=gcc
CFLAGS=-Wall -g
all:
	$(CC) $(CFLAGS) Principal.c -o principal
clear:
	rm principal	