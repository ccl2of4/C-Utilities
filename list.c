#include "list.h"
#include "utils.h"

struct list_node {
	struct list_node *next;
	const void *obj;
};

struct list {
	unsigned count;
	struct list_node *head;
};

list *
list_create (void) {
	list *list = Calloc (1,sizeof (struct list));
	return list;
}

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

unsigned
list_count (list *list) {
	assert (list);
	return list->count;
}

void
list_add (list *list, const void *obj) {
	assert (list && obj);
	return list_insert (list, obj, list->count);
}

void
list_insert (list *list, const void *obj, unsigned idx) {
	struct list_node *new_node = Malloc (sizeof (struct list_node));
	struct list_node *left_node = NULL;
	struct list_node *right_node = list->head;
	assert (list && obj && (idx <= list->count));

	while (idx--) {
		left_node = right_node;
		right_node = right_node ? right_node->next : NULL;
	}


	new_node->obj = obj;

	if (left_node)
		left_node->next = new_node;
	else
		list->head = new_node;
	new_node->next = right_node;

	++list->count;
}

void *
list_remove (list *list, unsigned idx) {
	assert (list && (idx < list->count));
	const void *retval;
	struct list_node *left_node = NULL;
	struct list_node *node = list->head;
	struct list_node *right_node;

	while (idx--) {
		left_node = node;
		node = node->next;
	}

	right_node = node->next;
	retval = node->obj;
	left_node->next = right_node;
	--list->count;
	return (void *)retval;
}

void *
list_get (list *list, unsigned idx) {
	struct list_node *node = list->head;
	assert (list && (idx < list->count));
	while (idx--) {
		node = node->next;
	}
	return (void *)node->obj;
}

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
