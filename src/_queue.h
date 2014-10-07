#ifndef _queue_h
#define _queue_h

#include "_object.h"

struct queue {
	struct object base;
	list_ref list;
};

void queue_init (queue_ref);
void _object_dealloc_queue (object_ref);

#endif