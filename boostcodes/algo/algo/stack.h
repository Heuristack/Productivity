#ifndef stack_h
#define stack_h

#define STORESIZE 0x400

typedef struct stack {
	int store[STORESIZE];
	int top;			// get index (index_get)
	int size;			// put index (index_put), redundant for P(size == top + 1) holds
} stack_t;

void stack_init(stack_t *S);
int stack_empty(stack_t *S);

int pop(stack_t *S, int *e);
int push(stack_t *S, int *e);

#endif
