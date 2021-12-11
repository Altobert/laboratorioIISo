CC=gcc
CFLAGS=-Wall -g
all:
	$(CC) $(CFLAGS) Principal.c  -o labhilos   -std=gnu99 -lm -lpthread	
clear:	
	rm labhilos	
