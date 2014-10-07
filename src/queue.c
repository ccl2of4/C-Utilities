#include "queue.h"
#include "_queue.h"
#include "list.h"
#include "utils.h"

queue *
queue_create (void) {
	queue *queue = Calloc (1, sizeof (struct queue));
	queue_init (queue);
	type_retain ((type *)queue);
	return queue;
}

void
queue_init (queue *queue) {
	type_init (&queue->base);
	((type *)queue)->type_dealloc = _type_dealloc_queue;
	queue->list = list_create ();
}

void _type_dealloc_queue (type *t) {
	queue *q = (queue *)t;
	type_release ((type *)q->list);
}

/*
void
queue_free_with_func (queue *queue, free_func func) {
	assert (queue && func);
	list_free_with_func (queue->list, func);
	Free (queue);
}

void
queue_free (queue *queue) {
	assert (queue);
	list_free (queue->list);
	Free (queue);
}
*/
void
queue_push (queue *queue, type *obj) {
	list_add (queue->list, obj);
}

void
queue_pop (queue *queue) {
	assert (list_count (queue->list) > 0);
	list_remove (queue->list, 0);
}

type *
queue_front (queue *queue) {
	return list_get (queue->list, 0);
}