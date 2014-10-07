#include "stack.h"
#include "_stack.h"
#include "array.h"
#include "utils.h"

stack *
stack_create (void) {
	stack *stack = Calloc (1, sizeof (struct stack));
	stack_init (stack);
	object_retain ((object *)stack);
	return stack;
}

void
stack_init (stack *stack) {
	object_init (&stack->base);
	((object *)stack)->object_dealloc = _object_dealloc_stack;
	stack->array = array_create ();
}

void
_object_dealloc_stack (object *t) {
	stack *s = (stack *)t;
	object_release ((object *)s->array);
}

/*
void
stack_free_with_func (stack *stack, free_func func) {
	assert (stack && func);
	array_free_with_func (stack->array, func);
	Free (stack);
}

void
stack_free (stack *stack) {
	assert (stack);
	array_free (stack->array);
	Free (stack);
}
*/
void
stack_push (stack *stack, object *obj) {
	array_add (stack->array, obj);
}

void stack_pop (stack *stack) {
	assert (array_count (stack->array) > 0);
	array_remove (stack->array, array_count (stack->array) - 1);
}

object *
stack_top (stack *stack) {
	return array_object_at_index (stack->array, array_count (stack->array) - 1);
}
