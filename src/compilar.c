#include <analise.h>
#include <tree.h>
#include <asm.h>

static void gerar_codigo(const struct bstree *tree)
{
	if (tree != NULL) {
		struct bstree *pai = tree->parent;

		if (pai != NULL && pai->lchild == tree) {
			/* Inicio do loop */
		}

		asm_gerar(tree->value);

		gerar_codigo(tree->lchild);

		if (tree->value->token == LOOP_FIM) {
			/* fim do loop */
		}

		gerar_codigo(tree->rchild);
	}
}

void compilar(void)
{
	struct bstree *arvore;

	arvore = analisar();

	asm_gerar_inicio();
	gerar_codigo(arvore);
	asm_gerar_final();
}
