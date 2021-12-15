CC=gcc
CFLAGS=-Wall -g
all:
	$(CC) $(CFLAGS) Principal.c    -o labhilos     -std=gnu99 -lm -lpthread
	$(CC) $(CFLAGS) hiloTest2.c    -o hiloTest2    -std=gnu99 -lm -lpthread			
clear:	
	rm labhilos	
	rm hiloTest2
		
