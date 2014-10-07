#ifndef array_h
#define array_h

#include "types.h"

// inherited from object
object_ref object_retain (object_ref);
void object_release (object_ref);
void object_dealloc (object_ref);
bool object_equals (object_ref, object_ref);
int object_hash (object_ref);

// array
array_ref array_create (void);

/* accessors*/
object_ref array_object_at_index (array_ref, unsigned);
unsigned array_count (array_ref);

/* mutators */
void array_add (array_ref, object_ref);
void array_insert (array_ref, object_ref, unsigned);
void array_remove (array_ref, unsigned);

/* iterator */
iterator_ref array_create_iterator (array_ref);

#endif