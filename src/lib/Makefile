CC=cc
CFLAGS=-Wall -O2
INCLUDES=-I../include

default: all

all: tree.o list.o

tree.o: tree.c ../include/tree.h 
	$(CC) $(CFLAGS) $(INCLUDES) -c tree.c

list.o: list.c ../include/list.h
	$(CC) $(CFLAGS) $(INCLUDES) -c list.c

clean:
	$(RM) *.o

