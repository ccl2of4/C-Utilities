#ifndef _number_h
#define _number_h

#include "_object.h"

typedef enum number_type {
	number_object_char,
	number_object_short,
	number_object_int,
	number_object_long,
	number_object_long_long,
	number_object_float,
	number_object_double,
} number_type;

struct number {
	struct object base;
	enum class_magic_number magic_num;
	union {
		char char_val;
		short short_val;
		int int_val;
		long long_val;
		long long long_long_val;
		float float_val;
		double double_val;
	};
	number_type number_type;
};

void number_init (number_ref);
bool _object_equals_number (object_ref, object_ref);
int _object_hash_number (object_ref);

#endif