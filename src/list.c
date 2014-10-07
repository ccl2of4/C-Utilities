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

list_node_ref
list_get_head (list_ref _self) {
	struct list *self = _self;
	return self->head;
}

void
list_set_head (list_ref _self, list_node_ref head) {
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
	list_node_ref new_node = list_node_create ();
	list_node_ref left_node = NULL;
	list_node_ref right_node = list_get_head (self);
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
	list_node_ref node = list_get_head (self);
	list_node_ref left_node = node;
	list_node_ref right_node;

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
	list_node_ref node = list_get_head (self);
	assert ((idx < self->count));
	while (idx--) {
		node = list_node_get_next (node);
	}
	return list_node_get_obj (node);
}

iterator_ref
list_create_iterator (list_ref _self) {
	struct list *self = _self;
	list_iterator_ref result = list_iterator_create (list_get_head (self));
	return result;
}

/* list_node */

list_node_ref
list_node_create (void) {
	struct list_node *self = Calloc (1,sizeof (struct list_node));
	list_node_init (self);
	object_retain (self);
	return self;
}

void
list_node_init (list_node_ref _self) {
	struct list_node *self = _self;
	object_init (self);
	((struct object *)self)->object_dealloc = _object_dealloc_list_node;
}

object_ref 
list_node_get_obj (list_node_ref _self){
	struct list_node *self = _self;
	return self->obj;
}

void
list_node_set_obj (list_node_ref _self, object_ref obj) {
	struct list_node *self = _self;
	RETAINED_MEMBER_SWAP (self,obj,obj);
}

list_node_ref
list_node_get_next (list_node_ref _self) {
	struct list_node *self = _self;
	return self->next;
}

void
list_node_set_next (list_node_ref _self, list_node_ref _next) {
	struct list_node *self = _self;
	struct list_node *next = _next;
	RETAINED_MEMBER_SWAP (self,next,next);
}

void
_object_dealloc_list_node (object_ref _self) {
	struct list_node* self = _self;
	list_node_set_obj (self, NULL);
	list_node_set_next (self, NULL);
}

/* list_iterator */
list_iterator_ref
list_iterator_create (list_node_ref head) {
	struct list_iterator *self = Calloc (1, sizeof (struct list_iterator));
	list_iterator_init (self);
	object_retain (self);
	self->current_node = head;
	return self;
}

void
list_iterator_init (list_iterator_ref _self) {
	struct list_iterator *self = _self;
	iterator_init (self);
	((struct iterator *)self)->iterator_has_next = _iterator_has_next__list_iterator;
	((struct iterator *)self)->iterator_next = _iterator_next__list_iterator;
}

object_ref
_iterator_next__list_iterator (iterator_ref _self) {
	struct list_iterator *self = _self;
	assert (iterator_has_next (self));
	object_ref result = list_node_get_obj (self->current_node);
	self->current_node = list_node_get_next (self->current_node);
	return result;
}

bool
_iterator_has_next__list_iterator (iterator_ref _self) {
	struct list_iterator *self = _self;
	return !!self->current_node;
}