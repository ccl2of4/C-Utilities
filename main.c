#include <stdlib.h>
#include <stdio.h>

#include "types.h"
#include "utils.h"

static void
test_number (void) {
	number *num = number_create_int (-10);
	assert (number_int_value (num) == -10);
	type_release ((type *)num);
}

static void
test_array (void) {
	array *array = array_create ();
	type_release ((type *)array);
}

static void
test_list (void) {
	int i;
	list *list = list_create ();

	for (i = 0; i < 10; ++i) {
		number *num = number_create_int (i);
		list_add (list, (type *)num);
		type_release ((type *)num);
	}

	for (i = 0; i < 10; ++i) {
		number *num = (number *)list_get (list, i);
		assert (number_int_value (num) == i);
	}

	type_release ((type *)list);
}

static void
test_stack (void) {
	stack *stack = stack_create ();
	type_release ((type *)stack);
}

static void
test_queue (void) {
	queue *queue = queue_create ();
	type_release ((type *)queue);
}

int
main (int argc, char **argv) {
	test_number ();
	test_array ();
	test_list ();
	test_stack ();
	test_queue ();
}
