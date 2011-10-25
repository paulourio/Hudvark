/*
 * Este arquivo define a gramática da linguagem
 * Brainfuck.
 */
#ifndef GRAMATICA_H
#define GRAMATICA_H

#include <stdbool.h>
#include <mensagens.h>

#define	PROXIMO		1
#define ANTERIOR	2
#define INCREMENTO	3
#define	DECREMENTO	4
#define	IMPRESSAO	5
#define LEITURA		6
#define	LOOP_INICIO	7
#define LOOP_FIM	8

struct gramatica {
	int token;
	char simbolo;
};

struct gramatica gramatica[] = {
	{PROXIMO,	'>'},
	{ANTERIOR,	'<'},
	{INCREMENTO,	'+'},
	{DECREMENTO,	'-'},
	{IMPRESSAO,	'.'},
	{LEITURA,	','},
	{LOOP_INICIO,	'['},
	{LOOP_FIM,	']'},
	{0, 0} 
};

static void verificar_simbolo_extendido(const int simbolo)
{
	switch (simbolo) {
	case '@':
	case '#':
	case '!':
		warn("O símbolo \"%c\" não é implementado no compilador "
		     "clássico de brainfuck.\n", (char) simbolo);
		break;
	default:
		break;
	}
}

static int verificar_simbolo(const int simbolo)
{
	int i;
	
	for ( ; gramatica[i].token; i++) {
		if (gramatica[i].simbolo == (char) simbolo)
			return true;
		verificar_simbolo_extendido(simbolo);
	}
	return false;
}

#endif
