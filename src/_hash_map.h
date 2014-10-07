#ifndef _hash_map_h
#define _hash_map_h

#include "_type.h"

struct hash_map {
	struct type base;
	list **array;
	int array_length;
	int count;
};

typedef struct hash_map_node {
	struct type base;
	type *key;
	type *obj;
} hash_map_node;

void hash_map_init (hash_map *);
void hash_map_expand_array (hash_map *, unsigned);
void hash_map_rehash (hash_map *);
void _type_dealloc_hash_map (type *);

hash_map_node *hash_map_node_create (void);
void hash_map_node_init (hash_map_node *self);
type *hash_map_node_get_key (hash_map_node *);
void hash_map_node_set_key (hash_map_node *, type *);
type *hash_map_node_get_obj (hash_map_node *);
void hash_map_node_set_obj (hash_map_node *, type *);
void _type_dealloc_hash_map_node (type *);

#define DEFAULT_LENGTH 10

#endif