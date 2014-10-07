#ifndef array_h
#define array_h

#include "types.h"

/* construction/destruction */
array *array_create (void);

/* accessors*/
int array_index_of_object (array *, object *);
object *array_object_at_index (array *, unsigned);
unsigned array_count (array *);

/* mutators */
void array_add (array *, object *);
void array_insert (array *, object *, unsigned);
void array_remove (array *, unsigned);

#endif