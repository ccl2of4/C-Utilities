#ifndef _array_h
#define _array_h

#include "_type.h"

struct array {
	struct type base;
	type ** contents;
	unsigned buffer_size;
	unsigned count;
};

void array_resize(array *);
void array_init (array *);
void _type_dealloc_array (type *);

#define DEFAULT_SIZE 10
#define RESIZE_FACTOR 2

#endif