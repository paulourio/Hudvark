/* This work is licensed under the Creative Commons Attribution-Noncommercial
 * 3.0 Brazil License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/br/deed.en
 * or send a letter to Creative Commons, 171 Second Street, Suite 300,
 * San Francisco, California, 94105, USA.
 *
 * Author: Paulo Roberto Urio (August 2011)
 */
#ifndef TREE_H_INCLUDE
#define TREE_H_INCLUDE

#include <mensagens.h>
#include <gramatica.h>
#include <token.h>

/* Valores para tree_errno.  Essa variável é definida quando é
 * detectado um erro na montagem da árvore, como loop no início
 * do código (trecho não executável). */
#define NENHUM_ERRO	0
#define LOOP_INVALIDO	1
#define LIBERAR_TOKEN	2
extern int tree_errno;

struct bstree {
	struct bstree *parent;
	struct bstree *lchild;
	struct bstree *rchild;
	struct token *value;
};

typedef void (*ftwalk)(const struct bstree *);

extern void *tree_new(void);
extern void tree_free(struct bstree **ptr) __nonnull ((1));
extern struct bstree *tree_insert(struct bstree **ptree,
		struct bstree *current_node, struct token *tk);
extern struct bstree *tree_new_node(struct token *value);
extern void tree_walk_preorder(const  struct bstree *ptree, const ftwalk cblk);

#endif

