#include "queue.h"
#include "list.h"
#include "utils.h"

struct queue {
	list *list;
};

queue *
queue_create (void) {
	queue *queue = Malloc (sizeof (struct queue));
	queue->list = list_create ();
	return queue;
}

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

void
queue_push (queue *queue, const void *obj) {
	list_add (queue->list, obj);
}

void *
queue_pop (queue *queue) {
	assert (list_count (queue->list) > 0);
	return list_remove (queue->list, 0);
}

void *
queue_front (queue *queue) {
	return list_get (queue->list, 0);
}