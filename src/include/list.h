#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <token.h>

struct lnode {
	void *value;
	struct lnode *next;
};

typedef void (*f_list_free_value)(struct token *);

typedef struct {
	struct lnode *front;
	struct lnode *last;
	f_list_free_value free_value;
} list;

extern void list_clear(list *l);
extern list *list_new(void);
extern list *list_free(list *l);
extern void *list_remove_front(list *l);
extern void list_append(list *node, struct token *tk);
extern void list_insert_front(list *l, struct token *tk);

static inline int list_isempty(const list *l)
{
	return (l->front == NULL);
}

static inline void list_set_free_value_method(list *l, f_list_free_value method)
{
	l->free_value = method;
}

static inline struct lnode *list_back(list *l)
{
	return l->last;
}


#endif

