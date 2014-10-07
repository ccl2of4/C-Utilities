#ifndef array_h
#define array_h

#include "types.h"

/* ============================================ */
/* C implementation of mutable/resizeable array */
/* ============================================ */

/* construction/destruction */
array *array_create (void);

/* accessors*/
int array_index_of_object (array *, type *);
type *array_object_at_index (array *, unsigned);
unsigned array_count (array *);

/* mutators */
void array_add (array *, type *);
void array_insert (array *, type *, unsigned);
void array_remove (array *, unsigned);

#endif