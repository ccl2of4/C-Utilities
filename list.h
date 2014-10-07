#ifndef list_h
#define list_h

#include "types.h"

list *list_create (void);

unsigned list_count (list *);

void list_add (list *, type *);
void list_insert (list *, type *, unsigned);
void list_remove (list *, unsigned);
type *list_get (list *, unsigned);

#endif