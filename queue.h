#ifndef queue_h
#define queue_h

#include "types.h"

queue *queue_create (void);

void queue_push (queue *, type *);
void queue_pop (queue *);
type *queue_front (queue *);

#endif