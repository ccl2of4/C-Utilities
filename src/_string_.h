#ifndef _string_h
#define _string_h

#include "string_.h"
#include "_object.h"

struct string {
	struct object base;
	enum class_magic_number magic_num;
	char *c_array;
};

void string_init (string_ref);
void _object_dealloc__string (object_ref);
bool _object_equals__string (object_ref, object_ref);
int _object_hash__string (object_ref);

#endif