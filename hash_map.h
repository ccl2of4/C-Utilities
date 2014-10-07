#ifndef hash_map_h
#define hash_map_h

#include "types.h"

hash_map *hash_map_create (void);

object *hash_map_get (hash_map *, object *);
void hash_map_set (hash_map *, object *, object *);
unsigned hash_map_count (hash_map *);

#endif