#ifndef string_h
#define string_h

#include "types.h"

string_ref string_create (void);

char *string_c_str (string_ref);
void string_append (string_ref, string_ref);
void string_append_c_str (string_ref, char *);

#endif