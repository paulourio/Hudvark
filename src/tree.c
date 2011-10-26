/* This work is licensed under the Creative Commons Attribution-Noncommercial
 * 3.0 Brazil License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/br/deed.en
 * or send a letter to Creative Commons, 171 Second Street, Suite 300,
 * San Francisco, California, 94105, USA.
 *
 * Author: Paulo Roberto Urio (August 2011)
 *
 * Versão alterada da árvore de busca binária feita na faculdade.
 */
#include <stdlib.h>
#include <tree.h>
#include <token.h>
#include <gramatica.h>
#include <mensagens.h>

int tree_errno;

/* Allocate memory for a new node */
struct bstree *tree_new_node(struct token *value)
{
	struct bstree   *bst;

	bst = malloc(sizeof(struct bstree));
	if (bst == NULL) {
		err("Não foi possível alocar memória para token %s.",
			token_para_string(value->token));
		exit(1);
	}
	bst->parent = NULL;
	bst->lchild = NULL;
	bst->rchild = NULL;
	bst->value = value;
	dump("Novo nó para a árvore: %s @ %p",
                token_para_string(value->token), bst);
	return bst;
}

/* Initialize an empty binary search tree */
void *tree_new(void)
{
	return NULL;
}

/* Free all tree nodes */
void tree_free(struct bstree **ptr)
{
	if (*ptr == NULL)
		return;
	tree_free(&(*ptr)->lchild);
	tree_free(&(*ptr)->rchild);
	free(*ptr);
	*ptr = NULL;
}

/* Finds the successor node */
static struct bstree *tree_successor(struct bstree *bst)
{
	struct bstree   *pai = bst->parent;

	if (bst->rchild != NULL) {
		/* Normalmente procuraria o menor do filho à direita.
		 * Mas nesta árvore, quando o sucessor é procurado, o
		 * nó *nunca* deve ter um filho, pois é o fim de um
		 * loop. */
		//return tree_min(bst->rchild);
		warn("Procurando sucessor de um nó que não é folha.");
	}
	while (pai != NULL && bst == pai->rchild)
		pai = (bst = pai)->parent;
	return pai;
}

static struct bstree *
tree_insert_after_node(struct bstree **ptree, struct bstree *current_node,
			struct token *tk)
{
	struct bstree *new = tree_new_node(tk);

        dump("Inserindo token %s à direita", token_para_string(tk->token));
        new->parent = current_node;
        if (current_node == NULL)
		return *ptree = new;
        return current_node->rchild = new;
}

static struct bstree *
tree_insert_new_loop(struct bstree **ptree, struct bstree *current_node,
			struct token *tk)
{
	struct bstree *new;

	if (current_node == NULL) {
		warn("Início de loop no início do programa sempre será "
			"falso e nunca será executado. Ignorando loop "
			"inteiro.");
		tree_errno = LOOP_INVALIDO;
		return NULL;
	}
	dump("Inserindo token %s à esquerda", token_para_string(tk->token));
	new = tree_new_node(tk);
        new->parent = current_node;
	return current_node->lchild = new;
}

static struct bstree *
tree_insert_close_loop(struct bstree **ptree, struct bstree *current_node,
			struct token *tk)
{
	dump("Fim de loop, procurando sucessor.");
	if (current_node == NULL)
		goto erro;
	current_node = tree_successor(current_node);
	if (current_node == NULL)
		/* Árvore com apenas um nó e, portanto, nenhum loop. */
		goto erro;
	tree_errno = LIBERAR_TOKEN;
	return current_node;
erro:
	err("Erro de sintaxe: símbolo %s não esperado.",
			token_para_string(tk->token));
	exit(1);
}

/* Add a token in the tree.  Current node means the last inserted node.
 * This argument is used to speed up the tree construction.  We want to
 * insert after this current node.  If it is the close of a loop, we
 * search backwards for the next loop opening. */
struct bstree *tree_insert(struct bstree **ptree, struct bstree *current_node,
			struct token *tk)
{
	tree_errno = NENHUM_ERRO;
	switch (tk->token) {
	case PROXIMO:
	case ANTERIOR:
	case INCREMENTO:
	case DECREMENTO:
	case IMPRESSAO:
	case LEITURA:
		return tree_insert_after_node(ptree, current_node, tk);
	case LOOP_INICIO:
		return tree_insert_new_loop(ptree, current_node, tk);
	case LOOP_FIM:
		return tree_insert_close_loop(ptree, current_node, tk);
	default:
	case SIMBOLO_NAO_ACEITO:
		err("Token não esperado: %s", token_para_string(tk->token));
		exit(1);
	}
}

/* Walk the tree in three orders */
void tree_walk_preorder(const struct bstree *ptree, const ftwalk cblk)
{
	if (ptree != NULL) {
		cblk(ptree);
		tree_walk_preorder(ptree->lchild, cblk);
		tree_walk_preorder(ptree->rchild, cblk);
	}
}

