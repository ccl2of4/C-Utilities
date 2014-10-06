#ifndef array_h
#define array_h

#include "types.h"

/* ============================================ */
/* C implementation of mutable/resizeable array */
/* ============================================ */

/* construction/destruction */
array *array_create(void);
void array_free(array *);
void array_free_with_func(array *, free_func);

/* accessors*/
int array_index_of_object(array *, const void *);
void *array_object_at_index(array *, unsigned);
unsigned array_count(array *);

/* mutators */
void array_add(array *, const void *);
void array_insert(array *, const void *, unsigned);
void *array_remove(array *, unsigned);

/* sorted behavior */
void array_sort(array *, int (*compar)(const void *, const void *));
int array_insert_ordered(array *, void *, int (*compar)(const void *, const void *));
void *array_search (array *, const void *, int (*compar)(const void *, const void *));

#endif