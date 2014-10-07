#ifndef types_h
#define types_h

#include <stdbool.h>
#include <stddef.h>

/* opaque types */
typedef struct object object;
typedef struct array array;
typedef struct list list;
typedef struct queue queue;
typedef struct stack stack;
typedef struct hash_map hash_map;
typedef struct number number;

#include "object.h"
#include "number.h"
#include "queue.h"
#include "stack.h"
#include "array.h"
#include "list.h"
#include "hash_map.h"

#endif