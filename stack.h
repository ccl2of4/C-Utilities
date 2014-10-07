#ifndef stack_h
#define stack_h

#include "types.h"

stack *stack_create (void);

void stack_push (stack *, object *);
void stack_pop (stack *);
object *stack_top (stack *);

#endif