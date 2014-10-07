#ifndef _queue_h
#define _queue_h

#include "_object.h"

struct queue {
	struct object base;
	list *list;
};

void queue_init (queue *);
void _object_dealloc_queue (object *);

#endif