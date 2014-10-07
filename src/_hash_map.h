#ifndef _hash_map_h
#define _hash_map_h

#include "_object.h"

struct hash_map {
	struct object base;
	list **array;
	int array_length;
	int count;
};

typedef struct hash_map_node {
	struct object base;
	object *key;
	object *obj;
} hash_map_node;

void hash_map_init (hash_map *);
void hash_map_expand_array (hash_map *, unsigned);
void hash_map_rehash (hash_map *);
void _object_dealloc_hash_map (object *);

hash_map_node *hash_map_node_create (void);
void hash_map_node_init (hash_map_node *self);
object *hash_map_node_get_key (hash_map_node *);
void hash_map_node_set_key (hash_map_node *, object *);
object *hash_map_node_get_obj (hash_map_node *);
void hash_map_node_set_obj (hash_map_node *, object *);
void _object_dealloc_hash_map_node (object *);

#define DEFAULT_LENGTH 10

#endif