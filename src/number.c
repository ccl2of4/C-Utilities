#include "number.h"
#include "_number.h"
#include "utils.h"

number_ref number_create (void) {
	struct number *self = Calloc (1, sizeof (struct number));
	number_init (self);
	object_retain (self);
	return self;
}

void number_init (number_ref _self) {
	struct number *self = _self;
	object_init (self);
	self->magic_num = class_magic_number_number;
	((struct object *)self)->object_equals = _object_equals_number;
	((struct object *)self)->object_hash = _object_hash_number;
}

bool
_object_equals_number (object_ref _self, object_ref _other) {
	struct number *self = _self;
	struct number *other = _other;
	if (self->number_type != other->number_type) return false;
	switch (self->number_type) {
		case number_object_char:
			return self->char_val == other->char_val;
		case number_object_short:
			return self->short_val == other->short_val;
		case number_object_int:
			return self->int_val == other->int_val;
		case number_object_long:
			return self->long_val == other->long_val;
		case number_object_long_long:
			return self->long_long_val == other->long_long_val;
		case number_object_float:
			return self->float_val == other->float_val;
		case number_object_double:
			return self->double_val == other->double_val;
	}
}

int
_object_hash_number (object_ref _self) {
	struct number *self = _self;
	switch (self->number_type) {
		case number_object_char:
			return self->char_val;
		case number_object_short:
			return self->short_val;
		case number_object_int:
			return self->int_val;
		case number_object_long:
			return self->long_val;
		case number_object_long_long:
			return self->long_long_val;
		case number_object_float:
			return self->float_val;
		case number_object_double:
			return self->double_val;
	}
}


number_ref number_create_char (char val) {
	struct number *self = number_create ();
	self->char_val = val;
	self->number_type = number_object_char;
}
number_ref number_create_short (short val) {
	struct number *self = number_create ();
	self->char_val = val;
	self->number_type = number_object_char;
}
number_ref number_create_int (int val) {
	struct number *self = number_create ();
	self->int_val = val;
	self->number_type = number_object_int;
}
number_ref number_create_long (long val) {
	struct number *self = number_create ();
	self->long_val = val;
	self->number_type = number_object_long;
}
number_ref number_create_long_long (long long val) {
	struct number *self = number_create ();
	self->long_long_val = val;
	self->number_type = number_object_long_long;
}
number_ref number_create_unsigned_char (unsigned char val) {
	return number_create_char ((char)val);
}
number_ref number_create_unsigned_short (unsigned short val) {
	return number_create_short ((int)val);
}
number_ref number_create_unsigned_int (unsigned val) {
	return number_create_int ((int)val);
}
number_ref number_create_unsigned_long (unsigned long val) {
	return number_create_long ((long)val);
}
number_ref number_create_unsigned_long_long (unsigned long long val) {
	return number_create_long_long ((long long)val);
}
number_ref number_create_float (float val) {
	struct number *self = number_create ();
	self->float_val = val;
	self->number_type = number_object_float;
}
number_ref number_create_double (double val) {
	struct number *self = number_create ();
	self->double_val = val;
	self->number_type = number_object_double;
}


char number_char_value (number_ref _self) {
	struct number *self = _self;
	return self->char_val;
}
short number_short_value (number_ref _self) {
	struct number *self = _self;
	return self->short_val;
}
int number_int_value (number_ref _self) {
	struct number *self = _self;
	return self->int_val;
}
long number_long_value (number_ref _self) {
	struct number *self = _self;
	return self->long_val;
}
long long number_long_long_value (number_ref _self) {
	struct number *self = _self;
	return self->long_long_val;
}
unsigned char number_unsigned_char_value (number_ref _self) {
	struct number *self = _self;
	return (unsigned char)self->char_val;
}
unsigned short number_unsigned_short_value (number_ref _self) {
	struct number *self = _self;
	return (unsigned short)self->short_val;
}
unsigned number_unsigned_int_value (number_ref _self) {
	struct number *self = _self;
	return (unsigned)self->int_val;
}
unsigned long number_unsigned_long_value (number_ref _self) {
	struct number *self = _self;
	return (unsigned long)self->long_val;
}
unsigned long long number_unsigned_long_long_value (number_ref _self) {
	struct number *self = _self;
	return (unsigned long long)self->long_long_val;
}
float number_float_value (number_ref _self) {
	struct number *self = _self;
	return self->float_val;
}
double number_double_value (number_ref _self) {
	struct number *self = _self;
	return self->double_val;
}