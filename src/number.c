#include "number.h"
#include "_number.h"
#include "utils.h"

number *number_create (void) {
	number *number = Calloc (1, sizeof (struct number));
	number_init (number);
	type_retain ((type *)number);
	return number;
}

void number_init (number *number) {
	type_init (&number->base);
}

/*
number *number_free (number *number) {
	Free (number);	
}
*/

number *number_create_char (char val) {
	number *number = number_create ();
	number->char_val = val;
}
number *number_create_short (short val) {
	number *number = number_create ();
	number->char_val = val;
}
number *number_create_int (int val) {
	number *number = number_create ();
	number->int_val = val;
}
number *number_create_long (long val) {
	number *number = number_create ();
	number->long_val = val;
}
number *number_create_long_long (long long val) {
	number *number = number_create ();
	number->long_long_val = val;
}
number *number_create_unsigned_char (unsigned char val) {
	return number_create_char ((char)val);
}
number *number_create_unsigned_short (unsigned short val) {
	return number_create_short ((int)val);
}
number *number_create_unsigned_int (unsigned val) {
	return number_create_int ((int)val);
}
number *number_create_unsigned_long (unsigned long val) {
	return number_create_long ((long)val);
}
number *number_create_unsigned_long_long (unsigned long long val) {
	return number_create_long_long ((long long)val);
}
number *number_create_float (float val) {
	number *number = number_create ();
	number->float_val = val;
}
number *number_create_double (double val) {
	number *number = number_create ();
	number->double_val = val;
}


char number_char_value (number *number) {
	return number->char_val;
}
short number_short_value (number *number) {
	return number->short_val;
}
int number_int_value (number *number) {
	return number->int_val;
}
long number_long_value (number *number) {
	return number->long_val;
}
long long number_long_long_value (number *number) {
	return number->long_long_val;
}
unsigned char number_unsigned_char_value (number *number) {
	return (unsigned char)number->char_val;
}
unsigned short number_unsigned_short_value (number *number) {
	return (unsigned short)number->short_val;
}
unsigned number_unsigned_int_value (number *number) {
	return (unsigned)number->int_val;
}
unsigned long number_unsigned_long_value (number *number) {
	return (unsigned long)number->long_val;
}
unsigned long long number_unsigned_long_long_value (number *number) {
	return (unsigned long long)number->long_long_val;
}
float number_float_value (number *number) {
	return number->float_val;
}
double number_double_value (number *number) {
	return number->double_val;
}