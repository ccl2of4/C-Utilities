#ifndef object_h
#define object_h

#include "types.h"

/*************
	OBJECT
*************/
typedef void * object_ref;

object_ref object_create (void);

object_ref object_retain (object_ref); //virtual
void object_release (object_ref); //virtual
void object_dealloc (object_ref); //virtual
bool object_equals (object_ref, object_ref); //virtual
int object_hash (object_ref); //virtual

#endif