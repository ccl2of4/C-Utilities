#ifndef object_h
#define object_h

#include "types.h"

object *object_create (void);
object *object_retain (object *);
void object_release (object *);
void object_dealloc (object *);

bool object_equals (object *, object *);
int object_hash (object *);

#endif