CC=cc
PROGRAMA=hudvark
CFLAGS=-Wall -O2
INCLUDES=-Iinclude
ARCH=-DARCH_x86_64=1

default: all

all: dvarkpp dvarkan $(PROGRAMA)

$(PROGRAMA): include/config.h

dvarkpp: gramatica.o
	cd preproc && make
	mv preproc/dvarkpp .

dvarkan: list.o tree.o stack.o gramatica.o main.o tokenizer.o \
	montar_arvore.o semantica.o tree_dump.o analise.o \
	asm_x86_64.o compilar.o loopstack.o
	$(CC) $(LDFLAGS) $(INCLUDES) list.o tree.o gramatica.o \
		tokenizer.o montar_arvore.o stack.o semantica.o tree_dump.o \
		loopstack.o asm_x86_64.o analise.o compilar.o main.o -o dvarkan

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
	
compilar.o: include/analise.h include/tree.h tree.o compilar.c
	$(CC) $(CFLAGS) $(INCLUDES) $(ARCH) -c compilar.c
	
analise.o: include/analise.h tree.o list.o analise.c
	$(CC) $(CFLAGS) $(INCLUDES) -c analise.c
	
tree.o: tree.c include/tree.h gramatica.o tree_dump.o
	$(CC) $(CFLAGS) $(INCLUDES) -c tree.c

tree_dump.o: include/tree.h stack.o tree_dump.c
	$(CC) $(CFLAGS) $(INCLUDES) -c tree_dump.c

list.o: list.c include/list.h
	$(CC) $(CFLAGS) $(INCLUDES) -c list.c
	
stack.o: stack.c include/stack.h
	$(CC) $(CFLAGS) $(INCLUDES) -c stack.c
	
asm_x86_64.o: include/asm.h include/asm_x86_64.h asm_x86_64.c loopstack.o
	$(CC) $(CFLAGS) $(INCLUDES) -c asm_x86_64.c
	
loopstack.o: include/mensagens.h include/loopstack.h loopstack.c
	$(CC) $(CFLAGS) $(INCLUDES) -c loopstack.c

clean:
	cd preproc && make clean
	$(RM) include/config.h
	$(RM) dvarkan dvarkpp *.o

