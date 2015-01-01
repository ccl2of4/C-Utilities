#ifndef stack_h
#define stack_h

#include "types.h"

/************
	STACK
************/
typedef void * stack_ref;

stack_ref stack_create (void);
void stack_push (stack_ref, object_ref);
void stack_pop (stack_ref);
object_ref stack_top (stack_ref);

// inherited from object
object_ref object_retain (object_ref);
void object_release (object_ref);
void object_dealloc (object_ref);
bool object_equals (object_ref, object_ref);
int object_hash (object_ref);

#endif