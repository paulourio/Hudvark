#include <stdio.h>
#include <stdlib.h>
#include <mensagens.h>
#include <analise.h>

static void inicializar_analisadores(void)
{
	tk_inicializar();	/* Inicializa o tokenizer (análise léxica). */
	parser_inicializar();	/* Análise sintática */
}

static void analisar(void)
{
	extern list *tokens;

	inicializar_analisadores();
	processar();

	analise_semantica( parser_analisar_tokens(&tokens) );
}

int main(void)
{
	analisar();
	return EXIT_SUCCESS;
}

