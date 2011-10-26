CC=cc
CFLAGS=-Wall -O2
INCLUDES=-I../include

default: montar_arvore.o

montar_arvore.o: montar_arvore.c
	$(CC) $(CFLAGS) $(INCLUDES) -c montar_arvore.c

clean:
	$(RM) montar_arvore.o

