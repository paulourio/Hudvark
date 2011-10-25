PROGRAMA=
CC=cc
PROGRAMA=hudvark
CFLAGS=-Wall -O2
INCLUDES=-I../include

default: $(PROGRAMA)

$(PROGRAMA): libs geradorCodigoFinal

libs: 
	cd lib && make
	mv lib/*.o .

geradorCodigoFinal: otimizador
	cd gerador_cod_otimizado && make

otimizador: geradorCodigo
	cd otimizador && make

geradorCodigo: analiseSemantica
	cd gerador_codigo && make

analiseSemantica: analiseSintatica
	cd analise_semantica && make

analiseSintatica: analiseLexica
	cd analise_sintatica && make

analiseLexica: preProc
	cd analise_lexica && make

preProc:
	cd preprocessamento && make

all: default

clean:
	cd lib && make clean
	cd gerador_cod_otimizado && make clean
	cd otimizador && make clean
	cd gerador_codigo && make clean
	cd analise_semantica && make clean
	cd analise_sintatica && make clean
	cd analise_lexica && make clean
	cd preprocessamento && make clean
	$(RM) $(PROGRAMA) $(FONTES:.c=.o)
