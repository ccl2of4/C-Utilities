#ifndef object_h
#define object_h

#include "types.h"

object_ref object_create (void);
object_ref object_retain (object_ref);
void object_release (object_ref);
void object_dealloc (object_ref);

bool object_equals (object_ref, object_ref);
int object_hash (object_ref);

#endif