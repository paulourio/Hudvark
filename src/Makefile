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

dvarkan: list.o tree.o stack.o gramatica.o main.o tokenizer.o \
	montar_arvore.o semantica.o tree_dump.o
	$(CC) $(LDFLAGS) $(INCLUDES) list.o tree.o gramatica.o tokenizer.o \
		montar_arvore.o stack.o semantica.o tree_dump.o \
		main.o -o dvarkan

gramatica.o: gramatica.c include/gramatica.h
	$(CC) $(CFLAGS) $(INCLUDES) -c gramatica.c
	
main.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c main.c

tokenizer.o: tokenizer.c include/list.h include/token.h
	$(CC) $(CFLAGS) $(INCLUDES) -c tokenizer.c
	
montar_arvore.o: tree.o list.o montar_arvore.c include/token.h \
	include/analise.h include/tree.h include/list.h include/mensagens.h
	$(CC) $(CFLAGS) $(INCLUDES) -c montar_arvore.c

semantica.o: stack.o tree.o list.o include/token.h \
	include/analise.h include/config.h gramatica.o
	$(CC) $(CFLAGS) $(INCLUDES) -c semantica.c
	
tree.o: tree.c include/tree.h gramatica.o tree_dump.o
	$(CC) $(CFLAGS) $(INCLUDES) -c tree.c

tree_dump.o: include/tree.h stack.o
	$(CC) $(CFLAGS) $(INCLUDES) stack.o -c tree_dump.c

list.o: list.c include/list.h
	$(CC) $(CFLAGS) $(INCLUDES) -c list.c
	
stack.o: stack.c include/stack.h
	$(CC) $(CFLAGS) $(INCLUDES) -c stack.c

clean:
	cd preproc && make clean
	$(RM) include/config.h
	$(RM) dvarkan dvarkpp *.o

