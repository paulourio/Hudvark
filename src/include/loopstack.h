/* This work is licensed under the Creative Commons Attribution-Noncommercial
 * 3.0 Brazil License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/br/deed.en
 * or send a letter to Creative Commons, 171 Second Street, Suite 300,
 * San Francisco, California, 94105, USA.
 *
 * Author: Paulo Roberto Urio (March 2011)
 */
#ifndef LOOP_STACK_H_INCLUDE
#define LOOP_STACK_H_INCLUDE

/* Um loop é divido em duas partes: a parte que irá validar a condicação
 * e se validada, a segunda parte, o corpo do loop, é executada. */
struct loop_info {
	int id_corpo; /* Id do corpo do loop */
};

struct loopst_node {
	struct loopst_node  *next;
	struct loop_info *data;
};

struct loopstack {
	struct loopst_node *top;
};

typedef struct loopstack	loopstack;

extern struct loopstack *loopstack_new(void);
extern void *loopstack_free(struct loopstack *s);

#define loopstack_isempty(s)	(s->top == NULL)
#define loopstack_top(s)	(!stack_isempty(s)?  s->top->data:  0)

extern void loopstack_push(struct loopstack *s, struct loop_info *data);
extern struct loop_info *loopstack_pop(struct loopstack *s);

#endif

