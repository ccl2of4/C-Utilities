#ifndef type_h
#define type_h

#include "types.h"

type *type_create (void);
type *type_retain (type *);
void type_release (type *);
void type_dealloc (type *);

bool type_equals (type *, type *);
int type_hash (type *);

#endif