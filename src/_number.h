#ifndef _number_h
#define _number_h

#include "_type.h"

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
};

void number_init (number *);

#endif