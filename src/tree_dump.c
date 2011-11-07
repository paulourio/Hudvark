/*
 * Funções para analisar o estado atual da árvore.
 */
#include <tree.h>
#include <stack.h>

#define MAX_CAMINHO	40

static struct stack *caminho;
static int coluna;
static int token_errada;

static void imprimir_caminho(void)
{
	char *path = stack_content(caminho);
	int i;

	raw_err("Coluna: %d\n\tTrecho:\t%s", coluna, path);
	raw_err("\033[31;1m%c\033[0m\n\t\t", token_errada);
	for (i = caminho->top;  i--;  )
		raw_err(" ");
	raw_err(" ^\n");
	free(path);
}

static void montar_caminho(struct bstree *tree, struct bstree *destino)
{
	if (tree != NULL) {
		if (stack_isfull(caminho)) {
			char last = stack_pop(caminho);

			caminho = stack_free(caminho);
			caminho = stack_new(MAX_CAMINHO);
			stack_push(caminho, (int) last);
		}
		stack_push(caminho, token_para_simbolo(tree->value->token));
		if (tree == destino) {
			imprimir_caminho();
			return;
		}
		montar_caminho(tree->lchild, destino);
		montar_caminho(tree->rchild, destino);
		//(void) stack_pop(caminho);
	}
}

/* Se acontecer um erro, a função tenta mostrar a região do erro. */
void tentar_imprimir_pedaco_codigo(struct bstree *tree,	struct bstree *destino,
				const int char_errado)
{
	if (tree == NULL)
		return;
	coluna = destino->value->coluna;
	token_errada = char_errado;
	caminho = stack_new(MAX_CAMINHO);
	montar_caminho(tree, destino);
	caminho = stack_free(caminho);
}

