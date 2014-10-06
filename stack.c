#include "stack.h"
#include "array.h"
#include "utils.h"

struct stack {
	array *array;
};

stack *
stack_create (void) {
	stack *stack = Malloc (sizeof (struct stack));
	stack->array = array_create ();
	return stack;
}

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

void
stack_push (stack *stack, const void *obj) {
	array_add (stack->array, obj);
}

void *
stack_pop (stack *stack) {
	assert (array_count (stack->array) > 0);
	return array_remove (stack->array, array_count (stack->array) - 1);
}

void *
stack_top (stack *stack) {
	return array_object_at_index (stack->array, array_count (stack->array) - 1);
}
