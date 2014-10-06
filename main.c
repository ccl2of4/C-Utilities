#include <stdlib.h>
#include <stdio.h>

#include "array.h"
#include "list.h"
#include "utils.h"

void
free_f (void *obj) {
	Free ((int *)obj);
}

static void
test_array (void) {
	int i;
	array *array = array_create ();
	for (i = 0; i < 10; ++i) {
		int *num = Malloc (sizeof(int));
		*num = i;
		array_add (array, num);
		assert (array_count (array) == i + 1);
	}
	for (i = 0; i < array_count (array); ++i) {
		int *num = array_object_at_index (array, i);
		assert (*num == i);
	}
	array_free_with_func (array, free_f);
}

void foreach_f (void *obj, unsigned idx, bool *stop) {
	assert (idx < 5);
	assert (*(int *)obj == idx);
	if (idx == 4) *stop = true;
}

static void
test_list (void) {
	int i;
	list *list = list_create ();
	for (i = 0; i < 10; ++i) {
		int *num = Malloc (sizeof(int));
		*num = i;
		list_add (list, num);
		assert (list_count (list) == i + 1);
	}
	list_foreach (list, foreach_f);
	list_free_with_func (list, free_f);
}

int
main (int argc, char **argv) {
	test_array ();
	test_list ();
}
