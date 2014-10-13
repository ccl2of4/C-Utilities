#ifndef string_h
#define string_h

#include "types.h"

string_ref string_create (void);
string_ref string_create_with_c_str (char *);

char *string_c_str (string_ref);

#endif