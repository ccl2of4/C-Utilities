#ifndef stack_h
#define stack_h

#include "types.h"

stack_ref stack_create (void);

void stack_push (stack_ref, object_ref);
void stack_pop (stack_ref);
object_ref stack_top (stack_ref);

#endif