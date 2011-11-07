/* This work is licensed under the Creative Commons Attribution-Noncommercial
 * 3.0 Brazil License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/br/deed.en
 * or send a letter to Creative Commons, 171 Second Street, Suite 300,
 * San Francisco, California, 94105, USA.
 *
 * Author: Paulo Roberto Urio (March 2011)
 */
#include <stdlib.h>
#include <mensagens.h>
#include <loopstack.h>

struct loopstack *loopstack_new(void)
{
	struct loopstack *st;

	st = malloc(sizeof(struct loopstack));
	if (st == NULL) {
		err("Não há memória disponível para a loop-stack.\n");
		exit(1);
	}
	st->top = NULL;
	return st;
}

void *loopstack_free(struct loopstack *s)
{
	if (s == NULL)
		return s;
	while (!loopstack_isempty(s))
		(void) loopstack_pop(s);
	free(s);
	return NULL;
}

void loopstack_push(struct loopstack *s, struct loop_info *data)
{
	struct loopst_node *node;

	node = malloc(sizeof(struct loopst_node));
	if (node == NULL) {
		err("Não há memória para um novo nó da loop-stack.");
		exit(1);
	}
	node->data = data;
	node->next = s->top;
	s->top = node;
}

struct loop_info *loopstack_pop(struct loopstack *s)
{
	struct loopst_node *Top;
	struct loop_info *toRet;

	if (loopstack_isempty(s)) {
		err("Loop-stack underflow.");
		exit(1);
	}
	Top = s->top;
	toRet = Top->data;
	s->top = Top->next;
	free(Top);
	return toRet;
}

