#ifndef _number_h
#define _number_h

#include "_type.h"

typedef enum number_type {
	number_type_char,
	number_type_short,
	number_type_int,
	number_type_long,
	number_type_long_long,
	number_type_float,
	number_type_double,
} number_type;

struct number {
	struct type base;
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

void number_init (number *);
bool _type_equals_number (type *, type *);
int _type_hash_number (type *);

#endif