PROGRAMA=
CC=cc
CFLAGS=-Wall -O2
INCLUDES=-I../include

default: $(PROGRAMA)

$(PROGRAMA): geradorCodigoFinal

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
	$(RM) -f $(PROGRAMA) $(FONTES:.c=.o)
