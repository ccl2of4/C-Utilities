#ifndef array_h
#define array_h

#include "types.h"

/* construction/destruction */
array_ref array_create (void);

/* accessors*/
int array_index_of_object (array_ref, object_ref);
object_ref array_object_at_index (array_ref, unsigned);
unsigned array_count (array_ref);

/* mutators */
void array_add (array_ref, object_ref);
void array_insert (array_ref, object_ref, unsigned);
void array_remove (array_ref, unsigned);

#endif