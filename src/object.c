#include "object.h"
#include "_object.h"
#include "utils.h"

object *object_create (void) {
	object *self = Calloc (1, sizeof (struct object));
	object_init (self);
	object_retain (self);
	return self;
}

void object_init (object *self) {
	self->object_dealloc = _object_dealloc_type;
	self->object_equals = _object_equals_type;
	self->object_hash = _object_hash_type;
}

object *object_retain (object *self) {
	assert (self);
	++self->retain_count;
	return self;
}

void object_release (object *self) {
	assert (self);
	if(!--self->retain_count) {
		object_dealloc (self);
		Free (self);
	}
}

void
_object_dealloc_type (object *self) {
	return;
}

bool
_object_equals_type (object *self, object *other) {
	return self == other;
}

int
_object_hash_type (object *self) {
	return (long long)self;
}


void object_dealloc (object *self) {self->object_dealloc (self);}
bool object_equals (object *self, object *other) {return self->object_equals (self,other);}
int object_hash (object *self) {return self->object_hash (self);}