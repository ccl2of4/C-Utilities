#include "hash_map.h"
#include "_hash_map.h"
#include "array.h"

#include <string.h>
#include "utils.h"
#include "list.h"

static void hash_map_print_array (hash_map_ref _self) {
	int i;
	struct hash_map *self = _self;
	printf ("==\n");
	for (i = 0; i < self->array_length ; ++i) {
		long val = (long)self->array[i];
		printf ("%lx",val);
	}
	printf ("\n==\n");
}

hash_map_ref
hash_map_create (void) {
	struct hash_map *self = Calloc (1, sizeof (struct hash_map));
	hash_map_init (self);
	object_retain (self);
	return self;
}

void
hash_map_init (hash_map_ref _self) {
	struct hash_map *self = _self;
	object_init (self);
	((struct object *)self)->object_dealloc = _object_dealloc_hash_map;
	hash_map_resize_array (self, DEFAULT_ARRAY_LENGTH);
}

void
_object_dealloc_hash_map (object_ref _self) {
	struct hash_map *self = _self;
	int i;
	for (i = 0; i < self->array_length; ++i) {
		list_ref list =  self->array[i];
		if (list) object_release (list);
	}
	Free (self->array);
}

void hash_map_resize_array (hash_map_ref _self, unsigned new_length) {
	struct hash_map *self = _self;
	if (!self->array) {
		self->array = Calloc (new_length, sizeof (list_ref));
	} else {
		self->array = Realloc (self->array, new_length * sizeof (list_ref));
		memset (self->array, 0, new_length * sizeof (list_ref));
	}
	self->array_length = new_length;
}

object_ref
hash_map_get (hash_map_ref _self, object_ref key) {
	struct hash_map *self = _self;
	hash_map_node *node;
	object_ref result = NULL;
	int index = object_hash (key) % self->array_length;
	list_ref list = self->array[index];
	if (list) {
		int i;
		for (i = 0; i < list_count (list); ++i) {
			hash_map_node *node = list_get (list, i);
			if (object_equals (key, hash_map_node_get_key (node))) {
				result = hash_map_node_get_obj (node);
			}
		}
	}
	return result;
}

void
hash_map_set (hash_map_ref _self, object_ref key, object_ref obj) {
	struct hash_map *self = _self;
	hash_map_do_set (self, key, obj);
	hash_map_check_for_rehash (self);
}

void
hash_map_do_set (hash_map_ref _self, object_ref key, object_ref obj) {
	struct hash_map *self = _self;
	hash_map_node *node = hash_map_node_create ();
	int index = object_hash (key) % self->array_length;
	list_ref *list = self->array + index;
	if (!*list) {
		*list = list_create ();
	}

	hash_map_node_set_key (node, key);
	hash_map_node_set_obj (node, obj);

	list_add (*list, (struct object *)node);
	object_release ((struct object *)node);
	++self->count;
}

void
hash_map_remove (hash_map_ref _self, object_ref key) {
	struct hash_map *self = _self;
	hash_map_do_remove (self, key);
	hash_map_check_for_rehash (self);
}

void
hash_map_do_remove (hash_map_ref _self, object_ref key) {
	struct hash_map *self = _self;
	int index = object_hash (key) % self->array_length;
	list_ref *list = self->array + index;
	if (*list) {
		iterator_ref iterator = list_create_iterator (*list);
		int idx = -1;
		bool found = false;
		while (!found && iterator_has_next (iterator)) {
			hash_map_node_ref node = iterator_next (iterator);
			found = object_equals (key, hash_map_node_get_key (node));
			++idx;
		}
		if (found) {
			int old_count = list_count (*list);
			list_remove (*list, idx);
			assert (list_count (*list) == old_count - 1);
			--self->count;
		}
		object_release (iterator);
	}
}

unsigned
hash_map_count (hash_map_ref _self) {
	struct hash_map *self = _self;
	return self->count;
}

void
hash_map_check_for_rehash (hash_map_ref _self) {
	struct hash_map *self = _self;

	float percent_load;
	percent_load = ((float)self->count)/((float)self->array_length);

	if (percent_load > REHASH_UP_FACTOR) {
		hash_map_rehash (self, self->array_length * ARRAY_RESIZE_FACTOR);
	}

	else if (percent_load < REHASH_DOWN_FACTOR && self->array_length > DEFAULT_ARRAY_LENGTH) {
		hash_map_rehash (self, self->array_length * REHASH_DOWN_FACTOR * ARRAY_RESIZE_FACTOR);
	}
}

void
hash_map_rehash (hash_map_ref _self, unsigned new_size) {
	struct hash_map *self = _self;
	int i;
	array_ref array = array_create ();
	iterator_ref iterator;
	for (i = 0; i < self->array_length; ++i) {
		list_ref *list = self->array + i;
		if (*list) {
			iterator_ref iterator = list_create_iterator (*list);
			while (iterator_has_next (iterator)) {
				array_add (array, iterator_next (iterator));
			}

			object_release (iterator);
			object_release (*list);
			*list = NULL;
		}
	}
	assert (array_count (array) == self->count);
	self->count = 0;

	hash_map_resize_array (self, new_size);

	iterator = array_create_iterator (array);
	while (iterator_has_next (iterator)) {
		hash_map_node_ref node = iterator_next (iterator);
		hash_map_do_set (self, hash_map_node_get_key (node), hash_map_node_get_obj (node));
	}
	object_release (iterator);
	object_release (array);
}

hash_map_node_ref
hash_map_node_create (void) {
	hash_map_node *self = Calloc (1, sizeof (struct hash_map_node));
	hash_map_node_init (self);
	object_retain ((struct object *)self);
	return self;
}
void
hash_map_node_init (hash_map_node_ref _self) {
	struct hash_map_node *self = _self;
	object_init (self);
	((struct object *)self)->object_dealloc = _object_dealloc_hash_map_node;
}
object_ref
hash_map_node_get_key (hash_map_node_ref _self) {
	struct hash_map_node *self = _self;
	return self->key;
}
void
hash_map_node_set_key (hash_map_node_ref _self, object_ref key) {
	struct hash_map_node *self = _self;
	RETAINED_MEMBER_SWAP (self,key,key);
}
object_ref
hash_map_node_get_obj (hash_map_node_ref _self) {
	struct hash_map_node *self = _self;
	return self->obj;
}
void
hash_map_node_set_obj (hash_map_node_ref _self, object_ref obj) {
	struct hash_map_node *self = _self;
	RETAINED_MEMBER_SWAP (self,obj,obj);
}
void
_object_dealloc_hash_map_node (object_ref _self) {
	struct hash_map_node *self = _self;
	hash_map_node_set_key (self,NULL);
	hash_map_node_set_obj (self,NULL);
}