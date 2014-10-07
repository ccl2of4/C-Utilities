#ifndef _queue_h
#define _queue_h

#include "_type.h"

struct queue {
	struct type base;
	list *list;
};

void queue_init (queue *);
void _type_dealloc_queue (type *);

#endif