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
	struct list_node *node = list->head;
	while (node) {
		struct list_node *next_node = node->next;
		type_release ((type *)node);
		node = next_node;
	}
}


/*
void
list_free_with_func (list *list, free_func func) {
	assert (list && func);
	struct list_node *node = list->head;
	while (node) {
		func ((void *)node->obj);
		node = node->next;
	}
	list_free (list);
}

void
list_free (list *list) {
	assert (list);
	struct list_node *node = list->head;
	unsigned idx = 0;
	while (node) {
		struct list_node *next_node = node->next;
		Free (node);
		node = next_node;
	}
	Free (list);
}
*/
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
	struct list_node *right_node = list->head;
	assert (list && obj && (idx <= list->count));

	while (idx--) {
		left_node = right_node;
		right_node = right_node ? right_node->next : NULL;
	}

	list_node_set_obj(new_node, obj);

	if (left_node)
		left_node->next = new_node;
	else
		list->head = new_node;
	new_node->next = right_node;

	++list->count;
}

void
list_remove (list *list, unsigned idx) {
	assert (list && (idx < list->count));
	struct list_node *left_node = NULL;
	struct list_node *node = list->head;
	struct list_node *right_node;

	while (idx--) {
		left_node = node;
		node = node->next;
	}

	right_node = node->next;
	left_node->next = right_node;
	--list->count;
	if (node) type_release ((type *)node);
}

type *
list_get (list *list, unsigned idx) {
	struct list_node *node = list->head;
	assert (list && (idx < list->count));
	while (idx--) {
		node = node->next;
	}
	return list_node_get_obj (node);
}
/*
void
list_foreach (list *list, foreach_func func) {
	struct list_node *node = list->head;
	unsigned idx = 0;
	bool stop = false;
	assert (list && func);
	while (node && !stop) {
		func ((void *)node->obj, idx++, &stop);
		node = node->next;
	}
}
*/

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

void
_type_dealloc_list_node (type *t) {
	list_node* list_node = (struct list_node *)t;
	list_node_set_obj (list_node, NULL);
}