#ifndef _stack_h
#define _stack_h

#include "_object.h"

struct stack {
	struct object base;
	array *array;
};

void stack_init (stack *);
void _object_dealloc_stack (object *);

#endif