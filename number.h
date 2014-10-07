#ifndef number_h
#define number_h

#include "types.h"

/* creation */
number *number_create_char (char);
number *number_create_short (short);
number *number_create_int (int);
number *number_create_long (long);
number *number_create_long_long (long long);
number *number_create_unsigned_char (unsigned char);
number *number_create_unsigned_short (unsigned short);
number *number_create_unsigned_int (unsigned);
number *number_create_unsigned_long (unsigned long);
number *number_create_unsigned_long_long (unsigned long long);
number *number_create_float (float);
number *number_create_double (double);

/* access */
char number_char_value (number *);
short number_short_value (number *);
int number_int_value (number *);
long number_long_value (number *);
long long number_long_long_value (number *);
unsigned char number_unsigned_char_value (number *);
unsigned short number_unsigned_short_value (number *);
unsigned number_unsigned_int_value (number *);
unsigned long number_unsigned_long_value (number *);
unsigned long long number_unsigned_long_long_value (number *);
float number_float_value (number *);
double number_double_value (number *);

#endif