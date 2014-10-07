#include <stdlib.h>
#include <stdio.h>

#include "types.h"
#include "utils.h"

static void
test_number (void) {
	number_ref num1 = number_create_int (-10);
	number_ref num2 = number_create_int (-10);
	number_ref num3 = number_create_int (17);
	
	assert (number_int_value (num1) == -10);
	assert (number_int_value (num2) == -10);
	assert (number_int_value (num3) == 17);
	assert (object_equals (num1, num2));
	assert (!object_equals (num1, num3));
	assert (object_hash (num1) == object_hash (num2));
	assert (object_hash (num1) != object_hash (num3));
	assert (object_hash (num2) != object_hash (num3));

	object_release (num1);
	object_release (num2);
	object_release (num3);
}

static void
test_array (void) {
	int i;
	array_ref array = array_create ();

	for (i = 0; i < 10; ++i) {
		number_ref num = number_create_int (i);
		array_add (array, num);
		object_release (num);
	}

	for (i = 9; i >= 0; --i) {
		number_ref num = array_object_at_index (array, i);
		assert (number_int_value (num) == i);
	}

	for (i = 0; array_count (array); ++i) {
		number_ref num = object_retain (array_object_at_index (array, 0));
		array_remove (array, 0);
		assert (number_int_value (num) == i);
		object_release (num);
	}

	object_release (array);
}

static void
test_list (void) {
	int i;
	list_ref list = list_create ();

	for (i = 0; i < 10; ++i) {
		number_ref num = number_create_int (i);
		list_add (list, num);
		object_release (num);
	}

	for (i = 0; i < 10; ++i) {
		number_ref num = list_get (list, i);
		assert (number_int_value (num) == i);
	}
	
	object_release (list);
}

static void
test_stack (void) {
	int i;
	stack_ref stack = stack_create ();

	for (i = 0; i < 10; ++i) {
		number_ref num = number_create_int (i);
		stack_push (stack, num);
		object_release (num);
	}

	for (i = 0; i < 10; ++i) {
		number_ref num = object_retain(stack_top (stack));
		stack_pop (stack);
		assert (number_int_value (num) == 9 - i);
		object_release (num);
	}

	object_release (stack);
}

static void
test_queue (void) {
	int i;
	queue_ref queue = queue_create ();

	for (i = 0; i < 1; ++i) {
		number_ref num = number_create_int (i);
		queue_push (queue, num);
		object_release (num);
	}

	for (i = 0; i < 1; ++i) {
		number_ref num = object_retain (queue_front (queue));
		queue_pop (queue);
		assert (number_int_value (num) == i);
		object_release (num);
	}

	object_release (queue);
}

static void
test_hash_map (void) {
	int i;
	hash_map_ref hash_map = hash_map_create ();

	for (i = 0; i < 10; ++i) {
		number_ref key = number_create_int (i);
		number_ref obj = number_create_int (i + 1);
		hash_map_set (hash_map, key, obj);
		object_release (key);
		object_release (obj);
	}

	for (i = 0; i < 10; ++i) {
		number_ref key = number_create_int (i);
		number_ref obj = hash_map_get (hash_map, key);
		assert (obj);
		assert (number_int_value (obj) == i + 1);
		object_release (key);
	}

	object_release (hash_map);
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
