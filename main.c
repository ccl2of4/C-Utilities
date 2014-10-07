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
	assert (object_equals ((object *)num1, (object *)num2));
	assert (!object_equals ((object *)num1, (object *)num3));
	assert (object_hash ((object *)num1) == object_hash ((object *)num2));
	assert (object_hash ((object *)num1) != object_hash ((object *)num3));
	assert (object_hash ((object *)num2) != object_hash ((object *)num3));

	object_release ((object *)num1);
	object_release ((object *)num2);
	object_release ((object *)num3);
}

static void
test_array (void) {
	int i;
	array *array = array_create ();

	for (i = 0; i < 10; ++i) {
		number *num = number_create_int (i);
		array_add (array, (object *)num);
		object_release ((object *)num);
	}

	for (i = 9; i >= 0; --i) {
		number *num = (number *)array_object_at_index (array, i);
		assert (number_int_value (num) == i);
	}

	for (i = 0; array_count (array); ++i) {
		number *num = (number *)object_retain (array_object_at_index (array, 0));
		array_remove (array, 0);
		assert (number_int_value (num) == i);
		object_release ((object *)num);
	}

	object_release ((object *)array);
}

static void
test_list (void) {
	int i;
	list *list = list_create ();

	for (i = 0; i < 10; ++i) {
		number *num = number_create_int (i);
		list_add (list, (object *)num);
		object_release ((object *)num);
	}

	for (i = 0; i < 10; ++i) {
		number *num = (number *)list_get (list, i);
		assert (number_int_value (num) == i);
	}
	
	object_release ((object *)list);
}

static void
test_stack (void) {
	int i;
	stack *stack = stack_create ();

	for (i = 0; i < 10; ++i) {
		number *num = number_create_int (i);
		stack_push (stack, (object *)num);
		object_release ((object *)num);
	}

	for (i = 0; i < 10; ++i) {
		number *num = (number *)object_retain(stack_top (stack));
		stack_pop (stack);
		assert (number_int_value (num) == 9 - i);
		object_release ((object *)num);
	}

	object_release ((object *)stack);
}

static void
test_queue (void) {
	int i;
	queue *queue = queue_create ();

	for (i = 0; i < 1; ++i) {
		number *num = number_create_int (i);
		queue_push (queue, (object *)num);
		object_release ((object *)num);
	}

	for (i = 0; i < 1; ++i) {
		number *num = (number *)object_retain (queue_front (queue));
		queue_pop (queue);
		assert (number_int_value (num) == i);
		object_release ((object *)num);
	}

	object_release ((object *)queue);
}

static void
test_hash_map (void) {
	int i;
	hash_map *hash_map = hash_map_create ();

	for (i = 0; i < 10; ++i) {
		number *key = number_create_int (i);
		number *obj = number_create_int (i + 1);
		hash_map_set (hash_map, (object *)key, (object *)obj);
		object_release ((object *)key);
		object_release ((object *)obj);
	}

	for (i = 0; i < 10; ++i) {
		number *key = number_create_int (i);
		number *obj = (number *)hash_map_get (hash_map, (object *)key);
		assert (obj);
		assert (number_int_value (obj) == i + 1);
		object_release ((object *)key);
	}

	object_release ((object *)hash_map);
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
