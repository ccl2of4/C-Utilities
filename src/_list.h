#ifndef _list_h
#define _list_h

#include "_object.h"
#include "_iterator.h"

typedef void * list_node_ref;
typedef void * list_iterator_ref;

struct list_node {
	struct object base;
	enum class_magic_number magic_num;
	struct list_node *next;
	object_ref obj;
};

struct list {
	struct object base;
	enum class_magic_number magic_num;
	unsigned count;
	list_node_ref head;
};

struct list_iterator {
	struct iterator base;
	enum class_magic_number magic_num;
	list_node_ref current_node;
};

// list
void list_init (list_ref);
list_node_ref list_get_head (list_ref);
void list_set_head (list_ref, list_node_ref);
void _object_dealloc_list (object_ref);

// list_node
list_node_ref list_node_create (void);
list_node_ref list_node_get_next (list_node_ref);
void list_node_set_next (list_node_ref, list_node_ref);
object_ref list_node_get_obj (list_node_ref);
void list_node_set_obj (list_node_ref, object_ref);
void list_node_init (list_node_ref);
void _object_dealloc_list_node (object_ref);

// list_iterator
list_iterator_ref list_iterator_create (list_node_ref);
void list_iterator_init (list_iterator_ref);
object_ref _iterator_next__list_iterator (iterator_ref);
bool _iterator_has_next__list_iterator (iterator_ref);

#endif