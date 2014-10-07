#include "stack.h"
#include "_stack.h"
#include "array.h"
#include "utils.h"

stack *
stack_create (void) {
	stack *stack = Calloc (1, sizeof (struct stack));
	stack_init (stack);
	type_retain ((type *)stack);
	return stack;
}

void
stack_init (stack *stack) {
	type_init (&stack->base);
	((type *)stack)->type_dealloc = _type_dealloc_stack;
	stack->array = array_create ();
}

void
_type_dealloc_stack (type *t) {
	stack *s = (stack *)t;
	type_release ((type *)s->array);
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
stack_push (stack *stack, type *obj) {
	array_add (stack->array, obj);
}

void stack_pop (stack *stack) {
	assert (array_count (stack->array) > 0);
	array_remove (stack->array, array_count (stack->array) - 1);
}

type *
stack_top (stack *stack) {
	return array_object_at_index (stack->array, array_count (stack->array) - 1);
}