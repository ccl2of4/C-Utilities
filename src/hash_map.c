#include "hash_map.h"
#include "_hash_map.h"
#include "array.h"

#include <string.h>
#include "utils.h"
#include "list.h"

static void hash_map_print_array (hash_map *self) {
	int i;
	for (i = 0; i < self->array_length; ++i) {
		long long val = (long long)self->array[i];
		printf ("%lld",val);
	}
	printf ("\n");
}

hash_map *
hash_map_create (void) {
	hash_map *self = Calloc (1, sizeof (struct hash_map));
	hash_map_init (self);
	object_retain ((object *)self);
	return self;
}

void
hash_map_init (hash_map *self) {
	object_init ((object *)self);
	((object *)self)->object_dealloc = _object_dealloc_hash_map;
	hash_map_expand_array (self, DEFAULT_LENGTH);
}

void
_object_dealloc_hash_map (object *_self) {
	hash_map *self = (hash_map *)_self;
	int i;
	for (i = 0; i < self->array_length; ++i) {
		list *list =  self->array[i];
		if (list) object_release ((object *)list);
	}
	Free (self->array);
}

void hash_map_expand_array (hash_map *self, unsigned length) {
	assert (length > self->array_length);
	if (!self->array) {
		self->array = Calloc (length, sizeof (struct list *));
	} else {
		self->array = Realloc (self->array, length * sizeof (struct list *));
		memset (self->array + self->array_length, 0, (length - self->array_length) * sizeof (struct list *));
		hash_map_rehash (self);
	}
	self->array_length = length;
}

object *
hash_map_get (hash_map *self, object *key) {
	hash_map_node *node;
	object *result = NULL;
	int index = object_hash (key) % self->array_length;
	list *list = self->array[index];
	if (list) {
		int i;
		for (i = 0; i < list_count (list); ++i) {
			hash_map_node *node = (hash_map_node *)list_get (list, i);
			number *num = (number *)node->key;
			if (object_equals (key, hash_map_node_get_key (node))) {
				result = hash_map_node_get_obj (node);
			}
		}
	}
	return result;
}

void
hash_map_set (hash_map *self, object *key, object *value) {
	hash_map_node *node = hash_map_node_create ();
	int index = object_hash (key) % self->array_length;
	list **list = &self->array[index];
	if (!*list) {
		*list = list_create ();
	}

	hash_map_node_set_key (node, key);
	hash_map_node_set_obj (node, value);

	list_add (*list, (object *)node);
	object_release ((object *)node);
	++self->count;
}

unsigned
hash_map_count (hash_map *self) {
	return self->count;
}

void
hash_map_rehash (hash_map *self) {
}

hash_map_node *hash_map_node_create (void) {
	hash_map_node *self = Calloc (1, sizeof (struct hash_map_node));
	hash_map_node_init (self);
	object_retain ((object *)self);
	return self;
}
void hash_map_node_init (hash_map_node *self) {
	object_init ((object *)self);
	((object *)self)->object_dealloc = _object_dealloc_hash_map_node;
}
object *
hash_map_node_get_key (hash_map_node *self) {
	return self->key;
}
void
hash_map_node_set_key (hash_map_node *self, object *key) {
	RETAINED_MEMBER_SWAP (self,key,key);
}
object *
hash_map_node_get_obj (hash_map_node *self) {
	return self->obj;
}
void
hash_map_node_set_obj (hash_map_node *self, object *obj) {
	RETAINED_MEMBER_SWAP (self,obj,obj);
}
void
_object_dealloc_hash_map_node (object *_self) {
	hash_map_node *self = (hash_map_node *)_self;
	hash_map_node_set_key (self,NULL);
	hash_map_node_set_obj (self,NULL);
}