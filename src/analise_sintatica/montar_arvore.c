/*
 * Análise sintática:   Montar a árvore com os lexemas gerados na
 * 			análise léxica.
 */
#include <token.h>
#include <list.h>
#include <tree.h>
#include <mensagens.h>
#include <analise.h>

struct bstree *tree;
static list **tokens; /* Não buscamos fora, recebemos como parâmetro. */
static struct bstree *tree_node = NULL;
static struct lnode *list_node_old = NULL; /* Usado para remoção de nós. */

static struct lnode *liberar_no_atual(struct lnode **no)
{
        struct token *tk;

        if (list_node_old == NULL) {
                tk = list_remove_front(*tokens);

        } else {
                tk = list_remove_node(*tokens, *no, list_node_old);
        }
        free_token(tk);
        return list_node_old->next;
}

static inline struct lnode *proximo_no(struct lnode *no)
{
        list_node_old = no;
        return no->next;
}

static void parser_pular_loop(struct lnode **no)
{
	int nivel = 0;

	do {
		if (*no == NULL) {
			err("Esperado ']', mas encontrado EOF.");
			exit(1);
		}
		debug("Ignorando %s",
                        token_para_string((*no)->value->token));
		switch ((*no)->value->token) {
		default:
                case PROXIMO:
                case ANTERIOR:
                case INCREMENTO:
                case DECREMENTO:
                case IMPRESSAO:
                case LEITURA:
			break;
		case LOOP_INICIO:
			nivel++;
			debug("Novo nível: %d", nivel);
			break;
		case LOOP_FIM:
			nivel--;
			debug("Novo nível: %d", nivel);
			break;
		}
		if (nivel > 0)
                        *no = (*no)->next;
	} while (nivel > 0);
		debug("Token atual %s",
                        token_para_string((*no)->value->token));
}

static void parser_verificar_erro(struct lnode **no)
{
	/* TODO: Testar isso. */
	switch (tree_errno) {
	case LOOP_INVALIDO:
		parser_pular_loop(no);
		break;
	default:
	case NENHUM_ERRO:
		break;
	}
}

void parser_montar_arvore(struct lnode *no)
{
	struct token *tk;

	if (no == NULL)
		return;
	tk = no->value;
	tree_node = tree_insert(&tree, tree_node, tk);
	if (tree_node == NULL)
		parser_verificar_erro(&no);
        parser_montar_arvore(no->next);
}

void parser_analisar_tokens(list **lista)
{
	struct lnode *no = list_front(*lista);

	tokens = lista;
	if (list_isempty(*lista)) {
		err("Lista de tokens vazia: nada para analisar.");
		exit(1);
	}
	parser_montar_arvore(no);
}

static void parser_finalizar(void)
{
	tree_free(&tree);
}

void parser_inicializar(void)
{
	tree = tree_new();
	atexit(parser_finalizar);
}

