#include "stack.h"

int pop(stack_t *S, int *e)
{
	if (S->top < 0) return 0;
	*e = S->store[S->top--];
//	S->top = S->top - 1;
	return 1;
}

int push(stack_t *S, int *e)
{
	if (S->top == STORESIZE - 1) return 0;
//	S->top = S->top + 1;
	S->store[++S->top] =  *e;
	return 1;
}

int stack_empty(stack_t *S)
{
	return (S->top < 0);
}

void stack_init(stack_t *S)
{
	S->top = -1;
}

