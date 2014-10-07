#ifndef stack_h
#define stack_h

#include "types.h"

stack *stack_create (void);

void stack_push (stack *, type *);
void stack_pop (stack *);
type *stack_top (stack *);

#endif