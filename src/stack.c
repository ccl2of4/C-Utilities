#include "stack.h"
#include "_stack.h"
#include "array.h"
#include "utils.h"

stack_ref
stack_create (void) {
	struct stack *self = Calloc (1, sizeof (struct stack));
	stack_init (self);
	object_retain (self);
	return self;
}

void
stack_init (stack_ref _self) {
	struct stack *self = _self;
	object_init (self);
	self->magic_num = class_magic_number_stack;
	((struct object *)self)->object_dealloc = _object_dealloc__stack;
	self->array = array_create ();
}

void
_object_dealloc__stack (object_ref _self) {
	struct stack *self = _self;
	TYPE_CHECK(self, stack);
	object_release (self->array);
}

void
stack_push (stack_ref _self, object_ref obj) {
	struct stack *self = _self;
	TYPE_CHECK(self, stack);
	array_add (self->array, obj);
}

void stack_pop (stack_ref _self) {
	struct stack *self = _self;
	TYPE_CHECK(self, stack);
	assert (array_count (self->array) > 0);
	array_remove (self->array, array_count (self->array) - 1);
}

object_ref
stack_top (stack_ref _self) {
	struct stack *self = _self;
	TYPE_CHECK(self, stack);
	return array_object_at_index (self->array, array_count (self->array) - 1);
}
