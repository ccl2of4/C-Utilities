#include "string_.h"
#include "_string_.h"
#include "utils.h"

string_ref
string_create (void) {
	struct string *self = Calloc (1, sizeof (struct string));
	string_init (self);
	object_retain (self);
	return self;
}

void
string_init (string_ref _self) {
	struct string *self = _self;
	object_init (self);
}


char *
string_c_str (string_ref _self) {
	struct string *self = _self;

}

void
string_append (string_ref _self, string_ref _other) {
	struct string *self = _self;
	struct string *other = _other;

}

void
string_append_c_str (string_ref _self, char *c_str) {
	struct string *self = _self;

}

void
string_c_array_resize(string_ref _self)
{
	struct string *self = _self;
}

void
_object_dealloc__string (object_ref _self) {
	struct string *self = _self;
	Free (self->c_array);
}
