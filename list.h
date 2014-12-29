#ifndef list_h
#define list_h

#include "types.h"

/***********
	LIST
***********/

list_ref list_create (void);
object_ref list_get (list_ref, unsigned);
unsigned list_count (list_ref);
void list_add (list_ref, object_ref);
void list_insert (list_ref, object_ref, unsigned);
void list_remove (list_ref, unsigned);
iterator_ref list_create_iterator (list_ref);

// inherited from object
object_ref object_retain (object_ref);
void object_release (object_ref);
void object_dealloc (object_ref);
bool object_equals (object_ref, object_ref);
int object_hash (object_ref);

#endif