CC=cc
CFLAGS=-Wall -O2
INCLUDES=-I../include

default: all

all: preproc

preproc: filtro.o main.o
	$(CC) $(LDFLAGS) $(INCLUDES) filtro.o main.o -o dvarkpp

main.o: main.c preproc.h
	$(CC) $(CFLAGS) $(INCLUDES) -c main.c

filtro.o: preproc.h filtro.c
	$(CC) $(CFLAGS) $(INCLUDES) -c filtro.c

clean:
	$(RM) -f *.o dvarkpp

