#ifndef _array_h
#define _array_h

#include "_object.h"

struct array {
	struct object base;
	object_ref * contents;
	unsigned buffer_size;
	unsigned count;
};

void array_resize(array_ref);
void array_init (array_ref);
void _object_dealloc_array (object_ref);

#define DEFAULT_SIZE 10
#define RESIZE_FACTOR 2

#endif