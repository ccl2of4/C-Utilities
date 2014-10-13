#include "hash_map.h"
#include "_hash_map.h"
#include "array.h"

#include <string.h>
#include "utils.h"
#include "list.h"

static void hash_map_print_array (hash_map_ref _self) {
	struct hash_map *self = _self;
	TYPE_CHECK(self,hash_map);
	int i;
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
	self->magic_num = class_magic_number_hash_map;
	((struct object *)self)->object_dealloc = _object_dealloc_hash_map;
	hash_map_resize_array (self, DEFAULT_ARRAY_LENGTH);
}

void
_object_dealloc_hash_map (object_ref _self) {
	struct hash_map *self = _self;
	int i;
	TYPE_CHECK(self,hash_map);
	for (i = 0; i < self->array_length; ++i) {
		list_ref list =  self->array[i];
		if (list) object_release (list);
	}
	Free (self->array);
}

void hash_map_resize_array (hash_map_ref _self, unsigned new_length) {
	struct hash_map *self = _self;
	TYPE_CHECK(self,hash_map);
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
	TYPE_CHECK(self,hash_map);
	TYPE_CHECK(key, object);
	hash_map_node *node;
	object_ref result = NULL;
	int index = abs(object_hash (key)) % self->array_length;
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
	TYPE_CHECK(self,hash_map);
	TYPE_CHECK(key, object);
	TYPE_CHECK(obj, object);
	hash_map_do_set (self, key, obj);
	hash_map_check_for_rehash (self);
}

void
hash_map_do_set (hash_map_ref _self, object_ref key, object_ref obj) {
	struct hash_map *self = _self;
	TYPE_CHECK(self,hash_map);
	TYPE_CHECK(key, object);
	TYPE_CHECK(obj, object);
	hash_map_node *node = hash_map_node_create ();
	int index = abs(object_hash (key)) % self->array_length;
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
	TYPE_CHECK(self,hash_map);
	TYPE_CHECK(key, object);
	hash_map_do_remove (self, key);
	hash_map_check_for_rehash (self);
}

void
hash_map_do_remove (hash_map_ref _self, object_ref key) {
	struct hash_map *self = _self;
	TYPE_CHECK(self,hash_map);
	TYPE_CHECK(key, object);
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
	TYPE_CHECK(self,hash_map);
	return self->count;
}

array_ref
hash_map_create_keys_array (hash_map_ref _self) {
	struct hash_map *self = _self;
	TYPE_CHECK(self,hash_map);
	return hash_map_create_array (self, false);
}

array_ref
hash_map_create_objects_array (hash_map_ref _self) {
	struct hash_map *self = _self;
	TYPE_CHECK(self,hash_map);
	return hash_map_create_array (self, true);
}

array_ref
hash_map_create_array (hash_map_ref _self, bool objects) {
	struct hash_map *self = _self;
	TYPE_CHECK(self,hash_map);
	iterator_ref iterator = hash_map_create_iterator (self);
	array_ref keys_array = array_create ();
	while (iterator_has_next (iterator)) {
		hash_map_node_ref node = iterator_next (iterator);
		assert (node);
		if (objects) {
			object_ref obj = hash_map_node_get_obj (node);
			assert (obj);
			array_add (keys_array, obj);

		}
		else {
			object_ref key = hash_map_node_get_key (node);
			assert (key);
			array_add (keys_array, key);
		}
	}
	object_release (iterator);
	return keys_array;
}

void
hash_map_check_for_rehash (hash_map_ref _self) {
	struct hash_map *self = _self;
	TYPE_CHECK(self,hash_map);

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
	TYPE_CHECK(self,hash_map);

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

iterator_ref
hash_map_create_iterator (hash_map_ref _self) {
	struct hash_map *self = _self;
	TYPE_CHECK(self,hash_map);

	return hash_map_iterator_create (self);
}

/* hash_map_node */

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
	self->magic_num = class_magic_number_hash_map_node;
	((struct object *)self)->object_dealloc = _object_dealloc_hash_map_node;
}
object_ref
hash_map_node_get_key (hash_map_node_ref _self) {
	struct hash_map_node *self = _self;
	TYPE_CHECK(self,hash_map_node);
	return self->key;
}
void
hash_map_node_set_key (hash_map_node_ref _self, object_ref key) {
	struct hash_map_node *self = _self;
	TYPE_CHECK(self,hash_map_node);
	RETAINED_MEMBER_SWAP (self,key,key);
}
object_ref
hash_map_node_get_obj (hash_map_node_ref _self) {
	struct hash_map_node *self = _self;
	TYPE_CHECK(self,hash_map_node);
	return self->obj;
}
void
hash_map_node_set_obj (hash_map_node_ref _self, object_ref obj) {
	struct hash_map_node *self = _self;
	TYPE_CHECK(self,hash_map_node);
	RETAINED_MEMBER_SWAP (self,obj,obj);
}
void
_object_dealloc_hash_map_node (object_ref _self) {
	struct hash_map_node *self = _self;
	TYPE_CHECK(self,hash_map_node);
	hash_map_node_set_key (self,NULL);
	hash_map_node_set_obj (self,NULL);
}

/* hash_map_iterator */
hash_map_iterator_ref
hash_map_iterator_create (hash_map_ref hash_map) {
	struct hash_map_iterator *self = Calloc (1, sizeof (struct hash_map_iterator));
	hash_map_iterator_init (self);
	object_retain (self);
	self->hash_map = hash_map;
	hash_map_iterator_find_next (self);
	return self;
}

void
hash_map_iterator_init (hash_map_iterator_ref _self) {
	struct hash_map_iterator *self = _self;
	iterator_init (self);
	self->magic_num = class_magic_number_hash_map_iterator;
	((struct iterator *)self)->iterator_has_next = _iterator_has_next__hash_map_iterator;
	((struct iterator *)self)->iterator_next = _iterator_next__hash_map_iterator;
}

void
hash_map_iterator_find_next (hash_map_iterator_ref _self) {
	struct hash_map_iterator *self = _self;
	TYPE_CHECK(self,hash_map_iterator);
	struct hash_map *hash_map = self->hash_map;
	while (!self->current_list_iterator && self->current_idx < hash_map_count (self->hash_map)) {
		list_ref list = hash_map->array[self->current_idx];
		if (list) {
			self->current_list_iterator = list_create_iterator (list);
			if (!iterator_has_next (self->current_list_iterator)) {
				object_release (self->current_list_iterator);
				self->current_list_iterator = NULL;
				list = NULL;
			}
		}
		++self->current_idx;
	}
}


object_ref
_iterator_next__hash_map_iterator (hash_map_iterator_ref _self) {
	struct hash_map_iterator *self = _self;
	TYPE_CHECK(self,hash_map_iterator);
	hash_map_node_ref retval;
	
	assert (self->current_list_iterator && iterator_has_next (self->current_list_iterator));
	retval = iterator_next (self->current_list_iterator);
	assert (retval);

	if (!iterator_has_next (self->current_list_iterator)) {
		object_release (self->current_list_iterator);
		self->current_list_iterator = NULL;
		hash_map_iterator_find_next (self);
	}

	return retval;
}
bool
_iterator_has_next__hash_map_iterator (hash_map_iterator_ref _self) {
	struct hash_map_iterator *self = _self;
	TYPE_CHECK(self,hash_map_iterator);
	return !!self->current_list_iterator;
}