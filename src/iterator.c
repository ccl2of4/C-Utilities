#include "iterator.h"
#include "_iterator.h"
#include "utils.h"

void
iterator_init (iterator_ref _self) {
	struct iterator *self = _self;
	object_init (self);
	self->magic_num = class_magic_number_iterator;
	self->iterator_has_next = _iterator_has_next__iterator;
	self->iterator_next = _iterator_next__iterator;
}

object_ref
_iterator_next__iterator (iterator_ref _self) {
	struct iterator *self = _self;
	TYPE_CHECK(self, iterator);
	return;
}

bool
_iterator_has_next__iterator (iterator_ref _self) {
	struct iterator *self = _self;
	TYPE_CHECK(self, iterator);
	return;
}


object_ref 
iterator_next (iterator_ref _self) {
	struct iterator *self = _self;
	TYPE_CHECK(self, iterator);
	return self->iterator_next (self);
}

bool
iterator_has_next (iterator_ref _self) {
	struct iterator *self = _self;
	TYPE_CHECK(self, iterator);
	return self->iterator_has_next (self);
}
