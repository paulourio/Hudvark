#include <analise.h>
#include <tree.h>
#include <asm.h>

static void gerar_codigo(const struct bstree *tree)
{
	if (tree != NULL) {
		asm_gerar(tree->value);
		gerar_codigo(tree->lchild);
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

