/*
 * Análise léxica: ler a entrada e criar uma lista de tokens (de lexemas).
 *	Ao terminar o processo, essa lista tokens será utilizada pela
 *	analise sintática.
 */
#include <stdlib.h>
#include <stdio.h>
#include <token.h>
#include <gramatica.h>
#include <list.h>

list *tokens;

static void print_token_info(struct token *ptr)
{
	dump("Token: %s @ %p", token_para_string(ptr->token), ptr);
}

void free_token(struct token *ptr)
{
	if (ptr != NULL) {
		dump("Token liberado da memória @ %p", ptr);
		free(ptr);
	}
}

static struct token *nova_token(const int token)
{
	struct token *tk = malloc(sizeof(struct token));

	if (tk == NULL) {
		err("Não foi possível alocar memória para o símbolo %c.",
			(char) token);
		exit(1);
	}
	tk->token = token;
	tk->contagem = 1;
	return tk;
}

static void processar_simbolo(const int simbolo)
{
	int valor = identificar_simbolo(simbolo);
	struct token *tk;

	if (simbolo == '\n') /* Quebra de linha. */
		return;
	if (valor == SIMBOLO_NAO_ACEITO) {
		err("Símbolo desconhecido: %c.", (char) simbolo);
		exit(1);
	}
	tk = nova_token(valor);
	print_token_info(tk);
	list_append(tokens, tk);
}

/* Gerar a lista de lexemas.
 * Os símbolos são lidos da entrada-padrão.
 */
void processar(void)
{
	int simbolo;

	while (!feof(stdin)) {
		simbolo = fgetc(stdin);
		if (simbolo == EOF)
			break;
		processar_simbolo(simbolo);
	}
}

static void tk_finalizar(void)
{
	tokens = list_free(tokens);
}

void tk_inicializar(void)
{
	tokens = list_new();
	list_set_free_value_method(tokens, free_token);
	atexit(tk_finalizar);
}

