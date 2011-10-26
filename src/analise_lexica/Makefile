CC=cc
CFLAGS=-Wall -O2
INCLUDES=-I../include

all: tokenizer.o

tokenizer.o: tokenizer.c ../include/list.h ../include/token.h
	$(CC) $(CFLAGS) $(INCLUDES) -c tokenizer.c

clean:
	$(RM) tokenizer.o
