#ifndef queue_h
#define queue_h

#include "types.h"

queue_ref queue_create (void);

void queue_push (queue_ref, object_ref);
void queue_pop (queue_ref);
object_ref queue_front (queue_ref);

#endif