#include "list.h"
#include "_list.h"
#include "utils.h"

list_ref
list_create (void) {
	struct list *self = Calloc (1,sizeof (struct list));
	list_init (self);
	object_retain (self);
	return self;
}

void
list_init (list_ref _self) {
	struct list *self = _self;
	object_init (self);
	((struct object *)self)->object_dealloc = _object_dealloc_list;
}

void
_object_dealloc_list (object_ref _self) {
	struct list *self = _self;
	list_set_head (self, NULL);
}

list_node *
list_get_head (list_ref _self) {
	struct list *self = _self;
	return self->head;
}

void
list_set_head (list_ref _self, list_node *head) {
	struct list *self = _self;
	RETAINED_MEMBER_SWAP (self,head,head);
}

unsigned
list_count (list_ref _self) {
	struct list *self = _self;
	return self->count;
}

void
list_add (list_ref _self, object_ref obj) {
	struct list *self = _self;
	assert (obj);
	return list_insert (self, obj, self->count);
}

void
list_insert (list_ref _self, object_ref obj, unsigned idx) {
	struct list *self = _self;
	struct list_node *new_node = list_node_create ();
	struct list_node *left_node = NULL;
	struct list_node *right_node = list_get_head (self);
	assert (obj && (idx <= self->count));

	while (idx--) {
		left_node = right_node;
		right_node = right_node ? list_node_get_next (right_node) : NULL;
	}

	list_node_set_obj(new_node, obj);

	if (left_node)
		list_node_set_next (left_node, new_node);
	else
		list_set_head (self, new_node);

	list_node_set_next (new_node, right_node);

	object_release ((struct object *)new_node);
	++self->count;
}

void
list_remove (list_ref _self, unsigned idx) {
	struct list *self = _self;
	assert ((idx < self->count));
	struct list_node *node = list_get_head (self);
	struct list_node *left_node = node;
	struct list_node *right_node;

	while (idx--) {
		node = list_node_get_next (node);
		left_node = node;
	}

	right_node = list_node_get_next(node);
	list_node_set_next(left_node, right_node);
	--self->count;
}

object_ref 
list_get (list_ref _self, unsigned idx) {
	struct list *self = _self;
	struct list_node *node = list_get_head (self);
	assert ((idx < self->count));
	while (idx--) {
		node = node->next;
	}
	return list_node_get_obj (node);
}

list_node *
list_node_create (void) {
	list_node *node = Calloc (1,sizeof (struct list_node));
	list_node_init (node);
	object_retain ((struct object *)node);
	return node;
}

void
list_node_init (list_node *node) {
	object_init (&node->base);
	((struct object *)node)->object_dealloc = _object_dealloc_list_node;
}

object_ref 
list_node_get_obj (list_node *node) {
	return node->obj;
}

void
list_node_set_obj (list_node *node, object_ref obj) {
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
_object_dealloc_list_node (object_ref t) {
	list_node* list_node = (struct list_node *)t;
	list_node_set_obj (list_node, NULL);
	list_node_set_next (list_node, NULL);
}