#include "type.h"
#include "_type.h"
#include "utils.h"

type *type_create (void) {
	type *self = Calloc (1, sizeof (struct type));
	type_init (self);
	type_retain (self);
	return self;
}

void type_init (type *self) {
	self->type_dealloc = _type_dealloc_type;
	self->type_equals = _type_equals_type;
	self->type_hash = _type_hash_type;
}

type *type_retain (type *self) {
	assert (self);
	++self->retain_count;
	return self;
}

void type_release (type *self) {
	assert (self);
	if(!--self->retain_count) {
		type_dealloc (self);
		Free (self);
	}
}

void
_type_dealloc_type (type *self) {
	return;
}

bool
_type_equals_type (type *self, type *other) {
	return self == other;
}

int
_type_hash_type (type *self) {
	return (long long)self;
}


void type_dealloc (type *self) {self->type_dealloc (self);}
bool type_equals (type *self, type *other) {return self->type_equals (self,other);}
int type_hash (type *self) {return self->type_hash (self);}