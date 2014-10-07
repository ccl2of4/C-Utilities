#ifndef list_h
#define list_h

#include "types.h"

list *list_create (void);

unsigned list_count (list *);

void list_add (list *, object *);
void list_insert (list *, object *, unsigned);
void list_remove (list *, unsigned);
object *list_get (list *, unsigned);

#endif