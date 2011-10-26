/*
 * Author: Paulo Roberto Urio
 * Date: September, 2011
 * Description: Linked list
 *
 * Versão modificada de uma lista encadeada feita na faculdade.
 */
#include <list.h>
#include <mensagens.h>

static void list_free_node(const list *l, struct lnode *n)
{
	if (l->free_value != NULL)
		l->free_value(n->value);
	free(n);
}

void list_clear(list *l)
{
	struct lnode *current = l->front, *next;

	while (current != NULL) {
		next = current->next;
		list_free_node(l, current);
		current = next;
	}
	l->front = NULL;
}

list *list_new(void)
{
	list *l = malloc(sizeof(list));
	l->front = NULL;
	l->free_value = NULL;
	return l;
}

/* Returns NULL everytime. */
list *list_free(list *l)
{
	list_clear(l);
	free(l);
	return NULL;
}

struct token *list_remove_node(list *l, struct lnode *node,
		struct lnode *previous)
{
	void *result = NULL;

	if (previous != NULL)
		previous->next = node->next;
	else
		l->front = node->next;
	result = node->value;
	free(node);
	return result;
}

struct token *list_remove_front(list *l)
{
	if (l->front == NULL)
		return NULL;
	return list_remove_node(l, l->front, NULL);
}

static struct lnode *list_new_node(struct token *v)
{
	struct lnode *new_node;

	new_node = malloc(sizeof(struct lnode));
	if (new_node == NULL) {
		err("Não foi possível alocar memória para o nó %p.\n", v);
		exit(1);
	}
	new_node->value = v;
	new_node->next = NULL;
	return new_node;
}

static struct lnode *list_insert_after_node(struct lnode *node, struct token *t)
{
	struct lnode *n = list_new_node(t);

	if (node != NULL) {
		n->next = node->next;
		node->next = n;
	}
	return n;
}

void list_append(list *l, struct token *tk)
{
	if (l->front == NULL) {
		list_insert_front(l, tk);
		return;
	}
	l->last = list_insert_after_node(l->last, tk);
}

void list_insert_front(list *l, struct token *tk)
{
	struct lnode *n = list_new_node(tk);

	n->next = l->front;
	if (l->front == NULL)
		l->last = n;
	l->front = n;
}

