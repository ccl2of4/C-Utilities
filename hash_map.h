#ifndef hash_map_h
#define hash_map_h

#include "types.h"

hash_map_ref hash_map_create (void);

object_ref hash_map_get (hash_map_ref, object_ref);
void hash_map_set (hash_map_ref, object_ref, object_ref);
unsigned hash_map_count (hash_map_ref);

#endif