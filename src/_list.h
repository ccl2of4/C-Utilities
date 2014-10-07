#ifndef _list_h
#define _list_h

#include "_type.h"

typedef struct list_node {
	struct type base;
	struct list_node *next;
	type *obj;
} list_node;

struct list {
	struct type base;
	unsigned count;
	struct list_node *head;
};

void list_init (list *);
void _type_dealloc_list (type *);

list_node *list_node_create (void);
type *list_node_get_obj (list_node *);
void list_node_set_obj (list_node *, type *);
void list_node_init (list_node *);
void _type_dealloc_list_node (type *);

#endif