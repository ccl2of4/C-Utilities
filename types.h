#ifndef types_h
#define types_h

#include <stdbool.h>
#include <stddef.h>

typedef void * object_ref;
typedef void * array_ref;
typedef void * list_ref;
typedef void * queue_ref;
typedef void * stack_ref;
typedef void * hash_map_ref;
typedef void * number_ref;
typedef void * iterator_ref;
typedef void * string_ref;

enum class_magic_number {
	class_magic_number_object,
	class_magic_number_array,
	class_magic_number_list,
	class_magic_number_list_node,
	class_magic_number_list_iterator,
	class_magic_number_queue,
	class_magic_number_stack,
	class_magic_number_hash_map,
	class_magic_number_number,
	class_magic_number_iterator,
	class_magic_number_string,
	class_magic_number_array_iterator,
	class_magic_number_hash_map_node,
	class_magic_number_hash_map_iterator,
};

#define TYPE_CHECK(instance, type) assert(instance); assert(((struct type *)instance)->magic_num == class_magic_number_##type)
#define IS_TYPE(instance, type) (((struct type *)instance)->magic_num == class_magic_number_##type)

#include "object.h"
#include "number.h"
#include "queue.h"
#include "stack.h"
#include "array.h"
#include "list.h"
#include "hash_map.h"
#include "iterator.h"
#include "string_.h"

#endif