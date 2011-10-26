#include <stdio.h>
#include <stdlib.h>
#include <mensagens.h>
#include <token.h>

static void inicializar_analisadores(void)
{
	tk_inicializar();	/* Inicializa o tokenizer. */
}

int main(void)
{
	inicializar_analisadores();
	processar();
	
	return EXIT_SUCCESS;
}
