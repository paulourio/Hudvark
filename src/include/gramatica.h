/*
 * Este arquivo define a gramática da linguagem
 * Brainfuck.
 */
#ifndef GRAMATICA_H
#define GRAMATICA_H

#include <mensagens.h>

#define	PROXIMO		1
#define ANTERIOR	2
#define INCREMENTO	3
#define	DECREMENTO	4
#define	IMPRESSAO	5
#define LEITURA		6
#define	LOOP_INICIO	7
#define LOOP_FIM	8
#define BOLHA		9

#define SIMBOLO_NAO_ACEITO 0

struct gramatica {
	int token;
	char simbolo;
	char *to_s;
};

extern struct gramatica gramatica[];

extern int identificar_simbolo(const int simbolo);
extern char *token_para_string(const int token);
extern int token_para_simbolo(const int token);

#endif

