#include "object.h"
#include "_object.h"
#include "utils.h"

object_ref object_create (void) {
	struct object *self = Calloc (1, sizeof (struct object));
	object_init (self);
	object_retain (self);
	return self;
}

void object_init (object_ref _self) {
	struct object *self = _self;
	self->magic_num = class_magic_number_object;
	self->object_dealloc = _object_dealloc_type;
	self->object_equals = _object_equals_type;
	self->object_hash = _object_hash_type;
}

object_ref object_retain (object_ref _self) {
	struct object *self = _self;
	TYPE_CHECK (self, object);
	++self->retain_count;
	return self;
}

void object_release (object_ref _self) {
	struct object *self = _self;
	TYPE_CHECK (self, object);
	if(!--self->retain_count) {
		object_dealloc (self);
		Free (self);
	}
}

void
_object_dealloc_type (object_ref _self) {
	struct object *self = _self;
	TYPE_CHECK (self, object);
	return;
}

bool
_object_equals_type (object_ref _self, object_ref other) {
	struct object *self = _self;
	TYPE_CHECK (self, object);
	return self == other;
}

int
_object_hash_type (object_ref _self) {
	struct object *self = _self;
	TYPE_CHECK (self, object);
	return (long long)self;
}


void object_dealloc (object_ref _self) {
	struct object *self = _self;
	TYPE_CHECK (self, object);
	self->object_dealloc (self);
}
bool object_equals (object_ref _self, object_ref _other) {
	struct object *self = _self;
	struct object *other = _other;
	TYPE_CHECK (self, object);
	return self->object_equals (self,other);
}
int object_hash (object_ref _self) {
	struct object *self  = _self;
	TYPE_CHECK (self, object);
	return self->object_hash (self);
}