#ifndef queue_h
#define queue_h

#include "types.h"

queue *queue_create (void);
void queue_free (queue *);
void queue_free_with_func (queue *, free_func);

void queue_push (queue *, const void *);
void *queue_pop (queue *);
void *queue_front (queue *);

#endif