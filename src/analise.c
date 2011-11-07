#include <analise.h>
#include <list.h>
#include <tree.h>

struct bstree *analisar(void)
{
	extern list *tokens;
	struct bstree *arvore;

	inicializar_analisadores();
	processar();

	arvore = parser_analisar_tokens(&tokens);
	analise_semantica(arvore);
	return arvore;
}

