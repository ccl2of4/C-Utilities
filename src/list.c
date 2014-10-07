#include "list.h"
#include "_list.h"
#include "utils.h"

list *
list_create (void) {
	list *list = Calloc (1,sizeof (struct list));
	list_init (list);
	object_retain ((object *)list);
	return list;
}

void
list_init (list *list) {
	object_init (&list->base);
	((object *)list)->object_dealloc = _object_dealloc_list;
}

void
_object_dealloc_list (object *t) {
	list *list = (struct list *)t;
	list_set_head (list, NULL);
}

list_node *
list_get_head (list *this) {
	return this->head;
}

void
list_set_head (list *this, list_node *head) {
	if (this->head != head) {
		if (this->head) {
			object_release ((object *)this->head);
		}
		this->head = head;
		if (this->head)
			object_retain ((object *)this->head);
	}
}

unsigned
list_count (list *list) {
	assert (list);
	return list->count;
}

void
list_add (list *list, object *obj) {
	assert (list && obj);
	return list_insert (list, obj, list->count);
}

void
list_insert (list *list, object *obj, unsigned idx) {
	struct list_node *new_node = list_node_create ();
	struct list_node *left_node = NULL;
	struct list_node *right_node = list_get_head (list);
	assert (list && obj && (idx <= list->count));

	while (idx--) {
		left_node = right_node;
		right_node = right_node ? list_node_get_next (right_node) : NULL;
	}

	list_node_set_obj(new_node, obj);

	if (left_node)
		list_node_set_next (left_node, new_node);
	else
		list_set_head (list, new_node);

	list_node_set_next (new_node, right_node);

	object_release ((object *)new_node);
	++list->count;
}

void
list_remove (list *list, unsigned idx) {
	assert (list && (idx < list->count));
	struct list_node *node = list_get_head (list);
	struct list_node *left_node = node;
	struct list_node *right_node;

	while (idx--) {
		node = list_node_get_next (node);
		left_node = node;
	}

	right_node = list_node_get_next(node);
	list_node_set_next(left_node, right_node);
	--list->count;
}

object *
list_get (list *list, unsigned idx) {
	struct list_node *node = list_get_head (list);
	assert (list && (idx < list->count));
	while (idx--) {
		node = node->next;
	}
	return list_node_get_obj (node);
}

list_node *
list_node_create (void) {
	list_node *node = Calloc (1,sizeof (struct list_node));
	list_node_init (node);
	object_retain ((object *)node);
	return node;
}

void
list_node_init (list_node *node) {
	object_init (&node->base);
	((object *)node)->object_dealloc = _object_dealloc_list_node;
}

object *
list_node_get_obj (list_node *node) {
	return node->obj;
}

void
list_node_set_obj (list_node *node, object *obj) {
	RETAINED_MEMBER_SWAP (node,obj,obj);
}

list_node *
list_node_get_next (list_node *this) {
	return this->next;
}

void
list_node_set_next (list_node *self, list_node *next) {
	RETAINED_MEMBER_SWAP (self,next,next);
}

void
_object_dealloc_list_node (object *t) {
	list_node* list_node = (struct list_node *)t;
	list_node_set_obj (list_node, NULL);
	list_node_set_next (list_node, NULL);
}