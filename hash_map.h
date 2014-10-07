#ifndef hash_map_h
#define hash_map_h

#include "types.h"

hash_map *hash_map_create (void);

type *hash_map_get (hash_map *, type *);
void hash_map_set (hash_map *, type *, type *);
unsigned hash_map_count (hash_map *);

#endif