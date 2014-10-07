#ifndef number_h
#define number_h

#include "types.h"

//inherited from object
object_ref object_retain (object_ref);
void object_release (object_ref);
void object_dealloc (object_ref);
bool object_equals (object_ref, object_ref);
int object_hash (object_ref);


//number

/* this class needs refactoring */

/* creation */
number_ref number_create_char (char);
number_ref number_create_short (short);
number_ref number_create_int (int);
number_ref number_create_long (long);
number_ref number_create_long_long (long long);
number_ref number_create_unsigned_char (unsigned char);
number_ref number_create_unsigned_short (unsigned short);
number_ref number_create_unsigned_int (unsigned);
number_ref number_create_unsigned_long (unsigned long);
number_ref number_create_unsigned_long_long (unsigned long long);
number_ref number_create_float (float);
number_ref number_create_double (double);

/* access */
char number_char_value (number_ref);
short number_short_value (number_ref);
int number_int_value (number_ref);
long number_long_value (number_ref);
long long number_long_long_value (number_ref);
unsigned char number_unsigned_char_value (number_ref);
unsigned short number_unsigned_short_value (number_ref);
unsigned number_unsigned_int_value (number_ref);
unsigned long number_unsigned_long_value (number_ref);
unsigned long long number_unsigned_long_long_value (number_ref);
float number_float_value (number_ref);
double number_double_value (number_ref);

#endif