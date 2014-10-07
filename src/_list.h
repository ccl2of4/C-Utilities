#ifndef _list_h
#define _list_h

#include "_object.h"

typedef struct list_node {
	struct object base;
	struct list_node *next;
	object *obj;
} list_node;

struct list {
	struct object base;
	unsigned count;
	struct list_node *head;
};

void list_init (list *);
list_node *list_get_head (list *);
void list_set_head (list *, list_node *);
void _object_dealloc_list (object *);

list_node *list_node_create (void);
list_node *list_node_get_next (list_node *);
void list_node_set_next (list_node *, list_node *);
object *list_node_get_obj (list_node *);
void list_node_set_obj (list_node *, object *);
void list_node_init (list_node *);
void _object_dealloc_list_node (object *);

#endif