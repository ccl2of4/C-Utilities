#include "list.h"
#include "_list.h"
#include "utils.h"

list *
list_create (void) {
	list *list = Calloc (1,sizeof (struct list));
	list_init (list);
	type_retain ((type *)list);
	return list;
}

void
list_init (list *list) {
	type_init (&list->base);
	((type *)list)->type_dealloc = _type_dealloc_list;
}

void
_type_dealloc_list (type *t) {
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
			type_release ((type *)this->head);
		}
		this->head = head;
		if (this->head)
			type_retain ((type *)this->head);
	}
}

unsigned
list_count (list *list) {
	assert (list);
	return list->count;
}

void
list_add (list *list, type *obj) {
	assert (list && obj);
	return list_insert (list, obj, list->count);
}

void
list_insert (list *list, type *obj, unsigned idx) {
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

	type_release ((type *)new_node);
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

type *
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
	type_retain ((type *)node);
	return node;
}

void
list_node_init (list_node *node) {
	type_init (&node->base);
	((type *)node)->type_dealloc = _type_dealloc_list_node;
}

type *
list_node_get_obj (list_node *node) {
	return node->obj;
}

void
list_node_set_obj (list_node *node, type *obj) {
	if (node->obj != obj) {
		if (node->obj)
			type_release (node->obj);
		node->obj = obj;
		if (node->obj)
			type_retain (node->obj);
	}
}

list_node *
list_node_get_next (list_node *this) {
	return this->next;
}

void
list_node_set_next (list_node *this, list_node *next) {
	if (this->next != next) {
		if (this->next)
			type_release ((type *)this->next);
		this->next = next;
		if (this->next)
			type_retain ((type *)this->next);
	}
}

void
_type_dealloc_list_node (type *t) {
	list_node* list_node = (struct list_node *)t;
	list_node_set_obj (list_node, NULL);
	list_node_set_next (list_node, NULL);
}