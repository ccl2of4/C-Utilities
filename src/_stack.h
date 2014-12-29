#ifndef _stack_h
#define _stack_h

#include "_object.h"

struct stack {
	struct object base;
	enum class_magic_number magic_num;
	array_ref array;
};

void stack_init (stack_ref);
void _object_dealloc__stack (object_ref);

#endif