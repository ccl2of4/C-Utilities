#ifndef list_h
#define list_h

#include "types.h"

list_ref list_create (void);

unsigned list_count (list_ref);

void list_add (list_ref, object_ref);
void list_insert (list_ref, object_ref, unsigned);
void list_remove (list_ref, unsigned);
object_ref list_get (list_ref, unsigned);

iterator_ref list_create_iterator (list_ref);

#endif