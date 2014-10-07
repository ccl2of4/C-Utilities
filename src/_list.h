#ifndef _list_h
#define _list_h

#include "_object.h"

typedef struct list_node {
	struct object base;
	struct list_node *next;
	object_ref obj;
} list_node;

struct list {
	struct object base;
	unsigned count;
	struct list_node *head;
};

void list_init (list_ref);
list_node *list_get_head (list_ref);
void list_set_head (list_ref, list_node *);
void _object_dealloc_list (object_ref);

list_node *list_node_create (void);
list_node *list_node_get_next (list_node *);
void list_node_set_next (list_node *, list_node *);
object_ref list_node_get_obj (list_node *);
void list_node_set_obj (list_node *, object_ref);
void list_node_init (list_node *);
void _object_dealloc_list_node (object_ref);

#endif