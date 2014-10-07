#ifndef _array_h
#define _array_h

#include "_object.h"

struct array {
	struct object base;
	object ** contents;
	unsigned buffer_size;
	unsigned count;
};

void array_resize(array *);
void array_init (array *);
void _object_dealloc_array (object *);

#define DEFAULT_SIZE 10
#define RESIZE_FACTOR 2

#endif