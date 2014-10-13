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
	iterator_ref iterator;

	for (i = 0; i < 10; ++i) {
		number_ref num = number_create_int (i);
		array_add (array, num);
		object_release (num);
	}

	for (i = 9; i >= 0; --i) {
		number_ref num = array_object_at_index (array, i);
		assert (number_int_value (num) == i);
	}

	for (iterator = array_create_iterator (array), i = 0; iterator_has_next (iterator); ++i) {
		number_ref num = iterator_next (iterator);
		assert (i < 10);
		assert (number_int_value (num) == i);
	}

	object_release (iterator);
	object_release (array);
}

static void
test_list (void) {
	int i;
	list_ref list = list_create ();
	iterator_ref iterator;

	for (i = 0; i < 10; ++i) {
		number_ref num = number_create_int (i);
		list_add (list, num);
		object_release (num);
	}

	for (iterator = list_create_iterator (list), i = 0; iterator_has_next (iterator); ++i) {
		number_ref num = iterator_next (iterator);
		assert (i < 10);
		assert (number_int_value (num) == i);
	}
	
	object_release (iterator);
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
	array_ref keys_array;
	array_ref objects_array;

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

	keys_array = hash_map_create_keys_array (hash_map);
	assert (array_count (keys_array) == 10);
	for (i = 0; i < 10; ++i) {
		number_ref key = array_object_at_index (keys_array, i);
		int val = number_int_value (key);
		assert (val >= 0 && val < 10 );
	}
	object_release (keys_array);

	objects_array = hash_map_create_objects_array (hash_map);
	assert (array_count (objects_array) == 10);
	for (i = 0; i < 10; ++i) {
		number_ref obj = array_object_at_index (objects_array, i);
		int val = number_int_value (obj);
		assert (val > 0 && val <= 10 );
	}
	object_release (objects_array);

	for (i = 9; i >= 0; --i) {
		number_ref key = number_create_int (i);
		hash_map_remove (hash_map, key);
		number_ref obj = hash_map_get (hash_map, key);
		assert (!obj);
		object_release (key);
	}

	assert (!hash_map_count (hash_map));

	object_release (hash_map);
}

static void
test_string (void) {
	string_ref str1 = string_create_with_c_str ("hello");
	string_ref str2 = string_create_with_c_str ("hello");
	string_ref str3 = string_create_with_c_str ("hello again");
	string_ref str4 = string_create_with_c_str ("goodbye");
	string_ref str5 = string_create_with_c_str ("goodbye goodbye");
	hash_map_ref hash_map = hash_map_create ();

	assert (object_equals (str1, str2));
	assert (!object_equals (str1, str3));
	assert (!object_equals (str3, str4));

	hash_map_set (hash_map, str1, str2);
	hash_map_set (hash_map, str2, str1);
	hash_map_set (hash_map, str3, str3);
	hash_map_set (hash_map, str4, str5);
	hash_map_set (hash_map, str5, str4);

	assert (object_equals (hash_map_get (hash_map, str1), str2));
	assert (object_equals (hash_map_get (hash_map, str2), str1));
	assert (object_equals (hash_map_get (hash_map, str3), str3));
	assert (object_equals (hash_map_get (hash_map, str4), str5));
	assert (object_equals (hash_map_get (hash_map, str5), str4));

	object_release (str1);
	object_release (str2);
	object_release (str3);
	object_release (str4);
	object_release (str5);
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
	test_string ();
}
