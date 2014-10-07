#include "type.h"
#include "_type.h"
#include "utils.h"

type *type_create (void) {
	type *t = Calloc (1, sizeof (struct type));
	type_init (t);
	type_retain (t);
	return t;
}

void type_init (type *t) {
	t->type_dealloc = _type_dealloc_type;
}

type *type_retain (type *t) {
	assert (t);
	++t->retain_count;
	return t;
}

void type_release (type *t) {
	assert (t);
	if(!--t->retain_count) {
		t->type_dealloc (t);
		Free (t);
	}
}

void _type_dealloc_type (type *t) {
	return;
}