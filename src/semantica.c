/*
 * Análise semântica: procurar por erros de lógica, como loops infinitos,
 *		ou trechos de código que não são antigíveis.
 */
#include <tree.h>
#include <stack.h>
#include <token.h>
#include <analise.h>
#include <gramatica.h>
#include <config.h>

#define DEPTH_CHAR	'\t'

static struct stack *profundidade;

static void identar(void)
{
	char *ident;

	ident = stack_content(profundidade);
	raw_debug("\n%s", ident);
	free(ident);
}

static void identacao_aumentar(void)
{
	stack_push(profundidade, DEPTH_CHAR);
	identar();
}

static void identacao_diminuir(void)
{
	(void) stack_pop(profundidade);
	identar();
}


static void imprimir_simbolo(const struct token *tk)
{
	char simbolo = (char) token_para_simbolo(tk->token);
	int i;

	if (simbolo ==  BOLHA)
		return;
	for (i = 0;  i < tk->contagem;  i++)
		raw_debug("%c", simbolo);
}

static void analisar_inicio_loop(const struct bstree *tree)
{
	int col = tree->value->coluna;

	if (stack_isfull(profundidade)) {
		err("Overflow: Pilha de loop cheia. Você pode tentar compilar "
		    "aumentando o tamanho da pilha com "
		    "./configure --tam-pilha 500");
		exit(2);
	}
	if (tree->parent != NULL && tree->parent->value->token == BOLHA) {
		warn("Loop iniciado na coluna %d nunca será executado.", col);
	}
	if (tree->rchild != NULL 
		&& tree->rchild->value->token == LOOP_FIM
		&& tree->lchild == NULL) {
		warn("Loop infinito iniciando na coluna %d.", col);
	}
	identacao_aumentar();
}

static void analisar_fim_loop(void)
{
	if (!stack_isempty(profundidade)) {
		identacao_diminuir();
	} else {
		/* Muito improvável que essa mensagem apareça.
		 * O erro de underflow já é identificado na hora de
		 * montar a árvore. */
		err("Underflow: token '%c' não esperado.\n\t"
		    "Nenhum loop aberto ao receber o token.",
		    token_para_simbolo(LOOP_FIM));
	}
}

static void analise_erro_underflow_memoria(void)
{
	err("Underflow: token '%c' está tentando acessar memória fora da "
		"memória do programa.",	token_para_simbolo(ANTERIOR));
	exit(2);
}

/* Caminha pela árvore em pré-ordem, analisando a sequência. */
static void analisar_arvore(const struct bstree *tree)
{
	if (tree != NULL) {
		struct bstree *pai = tree->parent;

		if (tree->value->token == ANTERIOR && tree->parent == NULL)
			analise_erro_underflow_memoria();

		if (tree->rchild != NULL || tree->parent == NULL)
			imprimir_simbolo(tree->value);

		if (pai != NULL && pai->lchild == tree)
			analisar_inicio_loop(tree);

		analisar_arvore(tree->lchild);

		if (tree->rchild == NULL && tree->parent != NULL) {
			if (tree->value->token == LOOP_FIM)
				analisar_fim_loop();
			imprimir_simbolo(tree->value);
		}

		analisar_arvore(tree->rchild);
	}
}

static void verificar_profundidade_no_final(void)
{
	if (!stack_isempty(profundidade)) {
		err("Esperado '%c', mas encontrado EOF",
			token_para_simbolo(LOOP_FIM));
		exit(1);
	}
}

static void liberar_pilha(void)
{
	dump("Liberando pilha @ %p", profundidade);
	profundidade = stack_free(profundidade);
}

static void iniciar_pilha(void)
{
	profundidade = stack_new(CONFIG_MAX_LOOP_DEPTH);
	dump("Pilha alocada @ %p", profundidade);
	atexit(liberar_pilha);
}

void analise_semantica(struct bstree *tree)
{
	iniciar_pilha();
	analisar_arvore(tree);
	raw_debug("\n");
	verificar_profundidade_no_final();
}
