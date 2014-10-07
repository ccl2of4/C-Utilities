#ifndef type_h
#define type_h

#include "types.h"

type *type_create (void);
type *type_retain (type *);
void type_release (type *);

#endif