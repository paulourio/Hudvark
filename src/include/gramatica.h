/*
 * Este arquivo define a gramática da linguagem
 * Brainfuck.
 */
#ifndef GRAMATICA_H
#define GRAMATICA_H

#define	PROXIMO		1
#define ANTERIOR	2
#define INCREMENTO	3
#define	DECREMENTO	4
#define	IMPRESSAO	5
#define LEITURA		6
#define	LOOP_INICIO	7
#define LOOP_FIM	8

struct gramatica {
	int TOKEN;
	char SIMBOLO;
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

#endif
