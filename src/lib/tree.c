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

/* Allocate memory for a new node */
struct bstree *tree_new_node(const struct token *value)
{
	struct bstree   *bst;

	bst = malloc(sizeof(struct bstree));
	if (bst == NULL) {
		err("Não foi possível alocar memória para token %s.\n", 
			simbolo_para_string(token));
		exit(1);
	}
	bst->parent = NULL;
	bst->lchild = NULL;
	bst->rchild = NULL;
	bst->value = value;
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

/* Walk the tree in three orders */
void tree_walk_preorder(const struct bstree *ptree, const ftwalk cblk)
{
	if (ptree != NULL) {
		cblk(ptree);
		tree_walk_preorder(ptree->lchild, cblk);
		tree_walk_preorder(ptree->rchild, cblk);
	}
}

