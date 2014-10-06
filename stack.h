#ifndef stack_h
#define stack_h

#include "types.h"

stack *stack_create (void);
void stack_free (stack *);
void stack_free_with_func (stack *, free_func);

void stack_push (stack *, const void *);
void *stack_pop (stack *);
void *stack_top (stack *);

#endif