#ifndef _stack_h
#define _stack_h

#include "_object.h"

struct stack {
	struct object base;
	array_ref array;
};

void stack_init (stack_ref);
void _object_dealloc_stack (object_ref);

#endif