#ifndef _array_h
#define _array_h

#include "_object.h"
#include "_iterator.h"

typedef void * array_iterator_ref;

struct array {
	struct object base;
	enum class_magic_number magic_num;
	object_ref *contents;
	unsigned buffer_size;
	unsigned count;
};

struct array_iterator {
	struct iterator base;
	enum class_magic_number magic_num;
	array_ref array;
	unsigned current_idx;
};

// array
void array_resize(array_ref);
void array_init (array_ref);
void _object_dealloc_array (object_ref);

#define DEFAULT_SIZE 10
#define RESIZE_FACTOR 2

// array_iterator
array_iterator_ref array_iterator_create (array_ref);
void array_iterator_init (array_iterator_ref);
object_ref _iterator_next__array_iterator (array_iterator_ref);
bool _iterator_has_next__array_iterator (array_iterator_ref);

#endif