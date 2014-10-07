#include "queue.h"
#include "_queue.h"
#include "list.h"
#include "utils.h"

queue *
queue_create (void) {
	queue *queue = Calloc (1, sizeof (struct queue));
	queue_init (queue);
	object_retain ((object *)queue);
	return queue;
}

void
queue_init (queue *queue) {
	object_init (&queue->base);
	((object *)queue)->object_dealloc = _object_dealloc_queue;
	queue->list = list_create ();
}

void _object_dealloc_queue (object *t) {
	queue *q = (queue *)t;
	object_release ((object *)q->list);
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
queue_push (queue *queue, object *obj) {
	list_add (queue->list, obj);
}

void
queue_pop (queue *queue) {
	assert (list_count (queue->list) > 0);
	list_remove (queue->list, 0);
}

object *
queue_front (queue *queue) {
	return list_get (queue->list, 0);
}