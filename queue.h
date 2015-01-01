#ifndef queue_h
#define queue_h

#include "types.h"

/************
	QUEUE
************/
typedef void * queue_ref;

queue_ref queue_create (void);
void queue_push (queue_ref, object_ref);
void queue_pop (queue_ref);
object_ref queue_front (queue_ref);

// inherited from object
object_ref object_retain (object_ref);
void object_release (object_ref);
void object_dealloc (object_ref);
bool object_equals (object_ref, object_ref);
int object_hash (object_ref);

#endif