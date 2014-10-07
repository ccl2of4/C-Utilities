#ifndef queue_h
#define queue_h

#include "types.h"

queue *queue_create (void);

void queue_push (queue *, object *);
void queue_pop (queue *);
object *queue_front (queue *);

#endif