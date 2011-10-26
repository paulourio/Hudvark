CC=cc
PROGRAMA=hudvark
CFLAGS=-Wall -O2
INCLUDES=-Iinclude

default: all

all: dvarkpp dvarkan $(PROGRAMA)

$(PROGRAMA): include/config.h

dvarkpp: gramatica.o
	cd preproc && make
	mv preproc/dvarkpp .

dvarkan: list.o tree.o gramatica.o main.o tokenizer.o montar_arvore.o 
	$(CC) $(LDFLAGS) $(INCLUDES) list.o tree.o gramatica.o tokenizer.o \
		montar_arvore.o main.o -o dvarkan

gramatica.o: gramatica.c include/gramatica.h
	$(CC) $(CFLAGS) $(INCLUDES) -c gramatica.c
	
main.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c main.c

tokenizer.o: tokenizer.c include/list.h include/token.h
	$(CC) $(CFLAGS) $(INCLUDES) -c tokenizer.c
	
montar_arvore.o: tree.o list.o montar_arvore.c include/token.h \
	include/analise.h include/tree.h include/list.h include/mensagens.h
	$(CC) $(CFLAGS) $(INCLUDES) -c montar_arvore.c
	
tree.o: tree.c include/tree.h gramatica.o
	$(CC) $(CFLAGS) $(INCLUDES) -c tree.c

list.o: list.c include/list.h
	$(CC) $(CFLAGS) $(INCLUDES) -c list.c

clean:
	cd preproc && make clean
	$(RM) include/config.h
	$(RM) dvarkan dvarkpp *.o

