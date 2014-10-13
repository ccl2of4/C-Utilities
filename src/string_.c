#include <string.h>
#include "string_.h"
#include "_string_.h"
#include "utils.h"

string_ref
string_create (void) {
	struct string *self = Calloc (1, sizeof (struct string));
	string_init (self);
	object_retain (self);
	self->c_array = malloc (sizeof (char));
	return self;
}

string_ref
string_create_with_c_str (char *str) {
	struct string *self = Calloc (1, sizeof (struct string));
	string_init (self);
	object_retain (self);
	self->c_array = malloc (sizeof (char) * (strlen (str) + 1));
	strcpy (self->c_array, str);
	return self;
}

void
string_init (string_ref _self) {
	struct string *self = _self;
	object_init (self);
	self->magic_num = class_magic_number_string;
	((struct object *)self)->object_dealloc = _object_dealloc__string;
	((struct object *)self)->object_equals = _object_equals__string;
	((struct object *)self)->object_hash = _object_hash__string;
}

char *
string_c_str (string_ref _self) {
	struct string *self = _self;
	TYPE_CHECK(self, string);
	return self->c_array;
}

void
_object_dealloc__string (object_ref _self) {
	struct string *self = _self;
	TYPE_CHECK(self, string);
	Free (self->c_array);
}

bool
_object_equals__string (object_ref _self, object_ref _other) {
	struct string *self = _self;
	struct string *other = _other;
	TYPE_CHECK (self,string);
	if (!IS_TYPE(other,string))
		return false;
	return !strcmp(string_c_str (self), string_c_str (other));
}

int
_object_hash__string (object_ref _self) {
	struct string *self = _self;
	TYPE_CHECK (self,string);
	int result = 5381;
	int index = 0;
	char c;
	while ((c = self->c_array[index++]))
		result = ((result << 5) + result) + c;
	return result;
}