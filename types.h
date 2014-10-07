#ifndef types_h
#define types_h

#include <stdbool.h>
#include <stddef.h>

/* opaque types */
typedef struct type type;
typedef struct array array;
typedef struct list list;
typedef struct queue queue;
typedef struct stack stack;
typedef struct number number;

/* function pointers */
typedef void (*foreach_func)(void *obj, unsigned idx, bool *stop);
typedef void (*free_func)(void *obj);

#include "type.h"
#include "number.h"
#include "queue.h"
#include "stack.h"
#include "array.h"
#include "list.h"

#endif