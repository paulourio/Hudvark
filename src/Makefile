PROGRAMA=
CC=cc
PROGRAMA=hudvark
CFLAGS=-Wall -O2
INCLUDES=-I../include

default: $(PROGRAMA)

$(PROGRAMA): libs geradorCodigoFinal

libs: gramatica.o
	cd lib && make
	mv lib/*.o .

geradorCodigoFinal: otimizador
	cd gerador_cod_otimizado && make

otimizador: geradorCodigo
	cd otimizador && make

geradorCodigo: analises
	cd gerador_codigo && make

analises: analiseLexica analiseSintatica analiseSemantica libs
	cd analise && make
	$(CC) $(LDFLAGS) list.o gramatica.o analise/main.o tokenizer.o \
		tree.o analise_sintatica/montar_arvore.o -o dvarkan

analiseSemantica: 
	cd analise_semantica && make

analiseSintatica: 
	cd analise_sintatica && make

analiseLexica: preProc
	cd analise_lexica && make && cp tokenizer.o ..

preProc: gramatica.o
	cd preprocessamento && make
	mv preprocessamento/dvarkpp .

gramatica.o:
	cd gramatica && make
	mv gramatica/gramatica.o .

all: default

clean:
	cd lib && make clean
	cd gerador_cod_otimizado && make clean
	cd otimizador && make clean
	cd gerador_codigo && make clean
	cd analise && make clean
	cd analise_semantica && make clean
	cd analise_sintatica && make clean
	cd analise_lexica && make clean
	cd preprocessamento && make clean
	$(RM) include/config.h
	$(RM) dvarkan dvarkpp *.o
