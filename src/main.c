#include <stdio.h>
#include <stdlib.h>
#include <mensagens.h>
#include <analise.h>

static void inicializar_analisadores(void)
{
	tk_inicializar();	/* Inicializa o tokenizer (análise léxica). */
	parser_inicializar();	/* Análise sintática */
}

int main(void)
{
	extern list *tokens;

	inicializar_analisadores();
	processar();

	parser_analisar_tokens(&tokens);
	return EXIT_SUCCESS;
}

