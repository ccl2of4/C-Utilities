#ifndef _string_h
#define _string_h

#include "string_.h"
#include "_object.h"

struct string {
	struct object base;
	char *c_array;
	unsigned buffer_size;
	unsigned length;
};

void string_init (string_ref);
void _object_dealloc__string (object_ref);


#define DEFAULT_SIZE 10
#define RESIZE_FACTOR 2

#endif