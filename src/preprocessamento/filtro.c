/*
 * Filtra os caracteres da entrada padrão, jogando para a saída
 * apenas os caracteres aceitos pela gramática.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gramatica.h>
#include <mensagens.h>

void filtrar_entrada(void)
{
	int simbolo;

	while (!feof(stdin)) {
		simbolo = fgetc(stdin);
		if (simbolo == EOF)
			break;
		if (verificar_simbolo(simbolo))
			(void) putchar(simbolo);
	}
	(void) putchar('\n');
}

