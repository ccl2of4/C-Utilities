#ifndef _hash_map_h
#define _hash_map_h

#include "_object.h"
#include "_iterator.h"

typedef void * hash_map_node_ref;
typedef void * hash_map_iterator_ref;
typedef void * hash_map_node;

struct hash_map {
	struct object base;
	enum class_magic_number magic_num;
	list_ref *array;
	int array_length;
	int count;
};

struct hash_map_node {
	struct object base;
	enum class_magic_number magic_num;
	object_ref key;
	object_ref obj;
};

struct hash_map_iterator {
	struct iterator base;
	enum class_magic_number magic_num;
	hash_map_ref hash_map;
	unsigned current_idx;
	iterator_ref current_list_iterator;
};

// hash_map
void hash_map_init (hash_map_ref);
void hash_map_do_set (hash_map_ref, object_ref, object_ref);
void hash_map_do_remove (hash_map_ref, object_ref);
void hash_map_check_for_rehash (hash_map_ref);
void hash_map_resize_array (hash_map_ref, unsigned);
void hash_map_rehash (hash_map_ref, unsigned new_size);
void _object_dealloc_hash_map (object_ref);
array_ref hash_map_create_array (hash_map_ref, bool objects);
iterator_ref hash_map_create_iterator (hash_map_ref);

// hash_map_node
hash_map_node_ref hash_map_node_create (void);
void hash_map_node_init (hash_map_node_ref);
object_ref hash_map_node_get_key (hash_map_node_ref);
void hash_map_node_set_key (hash_map_node_ref, object_ref);
object_ref hash_map_node_get_obj (hash_map_node_ref);
void hash_map_node_set_obj (hash_map_node_ref, object_ref);
void _object_dealloc_hash_map_node (object_ref);

// hash_map_iterator
hash_map_iterator_ref hash_map_iterator_create (hash_map_ref);
void hash_map_iterator_init (hash_map_iterator_ref);
object_ref _iterator_next__hash_map_iterator (hash_map_iterator_ref);
bool _iterator_has_next__hash_map_iterator (hash_map_iterator_ref);
void hash_map_iterator_find_next (hash_map_iterator_ref _self);

#define DEFAULT_ARRAY_LENGTH 10
#define ARRAY_RESIZE_FACTOR 2
#define REHASH_UP_FACTOR .75
#define REHASH_DOWN_FACTOR .1

#endif