#ifndef list_h
#define list_h

#include "types.h"

list *list_create (void);
void list_free (list *);
void list_free_with_func (list *, free_func);

unsigned list_count (list *);

void list_add (list *, const void *);
void list_insert (list *, const void *, unsigned);
void *list_remove (list *, unsigned);
void *list_get (list *, unsigned);

void list_foreach (list *, foreach_func);

#endif