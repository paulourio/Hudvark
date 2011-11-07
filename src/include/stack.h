#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stddef.h>

#define EMPTY_STACK (-1)

struct stack {
	char *data; /* Array of char */
	int top;
	int size;
};

static inline int stack_size(void *pstack)
{
	return ((struct stack *) pstack)->size;
}

static inline int stack_isempty(void *pstack)
{
	return ((struct stack *) pstack)->top == EMPTY_STACK;
}

static inline int stack_isfull(void *pstack)
{
	return ((struct stack *) pstack)->top == stack_size(pstack) - 1;
}

static inline int stack_top(void *pstack)
{
	if (!stack_isempty(pstack)) {
		struct stack *stack = pstack;

		return stack->data[stack->top];
	}
	return EMPTY_STACK;
}

extern void *stack_new(const int size);
extern void *stack_free(void *pstack) __nonnull ((1));
extern void stack_push(void *pstack, const int data) __nonnull ((1));
extern char stack_pop(void *pstack) __nonnull ((1));
extern char *stack_content(void *pstack);

#endif

