#ifndef _hash_map_h
#define _hash_map_h

#include "_object.h"

struct hash_map {
	struct object base;
	list_ref *array;
	int array_length;
	int count;
};

typedef struct hash_map_node {
	struct object base;
	object_ref key;
	object_ref obj;
} hash_map_node;

void hash_map_init (hash_map_ref);
void hash_map_expand_array (hash_map_ref, unsigned);
void hash_map_rehash (hash_map_ref);
void _object_dealloc_hash_map (object_ref);

hash_map_node *hash_map_node_create (void);
void hash_map_node_init (hash_map_node *);
object_ref hash_map_node_get_key (hash_map_node *);
void hash_map_node_set_key (hash_map_node *, object_ref);
object_ref hash_map_node_get_obj (hash_map_node *);
void hash_map_node_set_obj (hash_map_node *, object_ref);
void _object_dealloc_hash_map_node (object_ref);

#define DEFAULT_LENGTH 10

#endif