#ifndef hash_map_h
#define hash_map_h

#include "types.h"

/***************
	HASH MAP
***************/

hash_map_ref hash_map_create (void);
object_ref hash_map_get (hash_map_ref, object_ref);
void hash_map_set (hash_map_ref, object_ref, object_ref);
void hash_map_remove (hash_map_ref, object_ref);
unsigned hash_map_count (hash_map_ref);
array_ref hash_map_create_keys_array (hash_map_ref);
array_ref hash_map_create_objects_array (hash_map_ref);

// inherited from object
object_ref object_retain (object_ref);
void object_release (object_ref);
void object_dealloc (object_ref);
bool object_equals (object_ref, object_ref);
int object_hash (object_ref);


#endif