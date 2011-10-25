/*
 * Análise léxica: ler a entrada e criar uma lista de tokens (de lexemas).
 *	Ao terminar o processo, essa lista tokens será utilizada pela
 *	analise sintática.
 */
#include <token.h>
#include <list.h>

extern list *tokens;

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
	}
}

void tk_inicializar(void)
{
	tokens = list_new();
}

void tk_finalizar(void)
{
	tokens = list_free(tokens);
}


