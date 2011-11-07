#include <analise.h>
#include <gramatica.h>
#include <tree.h>
#include <asm.h>
#include <config.h>

static void gerar_codigo(const struct bstree *tree)
{
	if (tree != NULL) {
		const struct bstree *loop = tree->lchild;
		
		asm_gerar(tree->value);
		if (CONFIG_OTIMIZAR && loop != NULL
			&& loop->lchild == NULL
			&& loop->rchild->lchild == NULL
			&& loop->rchild->value->token == DECREMENTO
			&& loop->rchild->rchild->lchild == NULL
			&& loop->rchild->rchild->value->token == LOOP_FIM) {
			asm_gerar_zerar_celula();
		} else {
			gerar_codigo(tree->lchild);
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

