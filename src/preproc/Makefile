CC=cc
CFLAGS=-Wall -O2
INCLUDES=-I../include

default: all

all: preproc

preproc: filtro.o main.o ../gramatica.o
	$(CC) $(LDFLAGS) $(INCLUDES) filtro.o main.o ../gramatica.o -o dvarkpp

main.o: main.c preproc.h
	$(CC) $(CFLAGS) $(INCLUDES) -c main.c

filtro.o: preproc.h filtro.c
	$(CC) $(CFLAGS) $(INCLUDES) -c filtro.c

clean:
	$(RM) *.o dvarkpp

