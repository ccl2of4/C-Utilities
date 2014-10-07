#include <stdlib.h>
#include <stdio.h>

#include "types.h"
#include "utils.h"

static void
test_number (void) {
	number *num1 = number_create_int (-10);
	number *num2 = number_create_int (-10);
	number *num3 = number_create_int (17);
	
	assert (number_int_value (num1) == -10);
	assert (number_int_value (num2) == -10);
	assert (number_int_value (num3) == 17);
	assert (type_equals ((type *)num1, (type *)num2));
	assert (!type_equals ((type *)num1, (type *)num3));
	assert (type_hash ((type *)num1) == type_hash ((type *)num2));
	assert (type_hash ((type *)num1) != type_hash ((type *)num3));
	assert (type_hash ((type *)num2) != type_hash ((type *)num3));

	type_release ((type *)num1);
	type_release ((type *)num2);
	type_release ((type *)num3);
}

static void
test_array (void) {
	int i;
	array *array = array_create ();

	for (i = 0; i < 10; ++i) {
		number *num = number_create_int (i);
		array_add (array, (type *)num);
		type_release ((type *)num);
	}

	for (i = 9; i >= 0; --i) {
		number *num = (number *)array_object_at_index (array, i);
		assert (number_int_value (num) == i);
	}

	for (i = 0; array_count (array); ++i) {
		number *num = (number *)type_retain (array_object_at_index (array, 0));
		array_remove (array, 0);
		assert (number_int_value (num) == i);
		type_release ((type *)num);
	}

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
	int i;
	stack *stack = stack_create ();

	for (i = 0; i < 10; ++i) {
		number *num = number_create_int (i);
		stack_push (stack, (type *)num);
		type_release ((type *)num);
	}

	for (i = 0; i < 10; ++i) {
		number *num = (number *)type_retain(stack_top (stack));
		stack_pop (stack);
		assert (number_int_value (num) == 9 - i);
		type_release ((type *)num);
	}

	type_release ((type *)stack);
}

static void
test_queue (void) {
	int i;
	queue *queue = queue_create ();

	for (i = 0; i < 1; ++i) {
		number *num = number_create_int (i);
		queue_push (queue, (type *)num);
		type_release ((type *)num);
	}

	for (i = 0; i < 1; ++i) {
		number *num = (number *)type_retain (queue_front (queue));
		queue_pop (queue);
		assert (number_int_value (num) == i);
		type_release ((type *)num);
	}

	type_release ((type *)queue);
}

static void
test_hash_map (void) {
	int i;
	hash_map *hash_map = hash_map_create ();

	for (i = 0; i < 10; ++i) {
		number *key = number_create_int (i);
		number *object = number_create_int (i + 1);
		hash_map_set (hash_map, (type *)key, (type *)object);
		type_release ((type *)key);
		type_release ((type *)object);
	}

	for (i = 0; i < 10; ++i) {
		number *key = number_create_int (i);
		number *object = (number *)hash_map_get (hash_map, (type *)key);
		assert (object);
		assert (number_int_value (object) == i + 1);
		type_release ((type *)key);
	}

	type_release ((type *)hash_map);
}

int
main (int argc, char **argv) {
	test_number ();
	test_array ();
	test_list ();
	test_stack ();
	test_queue ();
	test_hash_map ();
}
