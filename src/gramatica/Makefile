CC=cc
CFLAGS=-Wall -O2
INCLUDES=-I../include

default: all

all: gramatica.o 

gramatica.o: gramatica.c ../include/gramatica.h
	$(CC) $(CFLAGS) $(INCLUDES) -c gramatica.c

clean:
	$(RM) *.o

