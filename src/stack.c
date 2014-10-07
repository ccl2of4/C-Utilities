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
	((struct object *)self)->object_dealloc = _object_dealloc_stack;
	self->array = array_create ();
}

void
_object_dealloc_stack (object_ref _self) {
	struct stack *self = _self;
	object_release (self->array);
}

void
stack_push (stack_ref _self, object_ref obj) {
	struct stack *self = _self;
	array_add (self->array, obj);
}

void stack_pop (stack_ref _self) {
	struct stack *self = _self;
	assert (array_count (self->array) > 0);
	array_remove (self->array, array_count (self->array) - 1);
}

object_ref
stack_top (stack_ref _self) {
	struct stack *self = _self;
	return array_object_at_index (self->array, array_count (self->array) - 1);
}
