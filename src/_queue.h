#ifndef _queue_h
#define _queue_h

#include "_object.h"

struct queue {
	struct object base;
	enum class_magic_number magic_num;
	list_ref list;
};

void queue_init (queue_ref);

//override
void _object_dealloc__queue (object_ref);

#endif