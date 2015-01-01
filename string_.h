#ifndef string_h
#define string_h

#include "types.h"

/*************
	STRING
*************/
typedef void * string_ref;

string_ref string_create (void);
string_ref string_create_with_c_str (char *);
char *string_c_str (string_ref);

// inherited from object
object_ref object_retain (object_ref);
void object_release (object_ref);
void object_dealloc (object_ref);
bool object_equals (object_ref, object_ref);
int object_hash (object_ref);

#endif