#ifndef types_h
#define types_h
#include <stdbool.h>

/* opaque types */
typedef struct array array;
typedef struct list list;
typedef struct queue queue;
typedef struct stack stack;

/* function pointers */
typedef void (*foreach_func)(void *obj, unsigned idx, bool *stop);
typedef void (*free_func)(void *obj);

#endif