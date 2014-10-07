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

#include "object.h"
#include "number.h"
#include "queue.h"
#include "stack.h"
#include "array.h"
#include "list.h"
#include "hash_map.h"

#endif