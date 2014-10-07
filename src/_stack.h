#ifndef _stack_h
#define _stack_h

#include "_type.h"

struct stack {
	struct type base;
	array *array;
};

void stack_init (stack *);
void _type_dealloc_stack (type *);

#endif