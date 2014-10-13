#include "array.h"
#include "_array.h"
#include "utils.h"

array_ref
array_create(void)
{
	struct array *self = Calloc(1,sizeof(struct array));
	array_init (self);
	object_retain (self);
	return self;
}

void
array_init (array_ref _self) {
	struct array *self = _self;
	object_init (self);
	self->magic_num = class_magic_number_array;
	((struct object *)self)->object_dealloc = _object_dealloc_array;
	array_resize (self);
}

void
_object_dealloc_array (object_ref _self) {
	struct array *self = _self;
	TYPE_CHECK(self, array);
	int i;
	for (i = 0; i < array_count (self); ++i)
		object_release (array_object_at_index (self, i));
	Free (self->contents);
}

void
array_resize(array_ref _self)
{
	struct array *self = _self;
	TYPE_CHECK(self, array);
	if(!self->contents)
		self->contents = Malloc((self->buffer_size = DEFAULT_SIZE) * sizeof(object_ref));
	else
		self->contents = Realloc(self->contents,(self->buffer_size *= 2) * sizeof(object_ref));
}

unsigned
array_count(array_ref _self)
{
	struct array *self = _self;
	TYPE_CHECK(self, array);
	return self->count;
}

void
array_add(array_ref _self, object_ref obj)
{
	struct array *self = _self;
	TYPE_CHECK(self, array);
	TYPE_CHECK(obj, object);
	return array_insert (self, obj, self->count);
}

void
array_insert(array_ref _self, object_ref obj, unsigned index)
{
	struct array *self = _self;
	TYPE_CHECK(self, array);
	TYPE_CHECK(obj, object);
	int i;
	object_ref temp1 = NULL;
	object_ref temp2 = NULL;
	assert (obj && (index <= self->count));

	if(self->count >= self->buffer_size - 1)
		array_resize(self);

	temp1 = obj;
	for(i = index; i < self->count; ++i) {
		temp2 = self->contents[i];
		self->contents[i] = temp1;
		temp1 = temp2;
	}
	object_retain (obj);
	self->contents[i] = temp1;
	self->count++;
}

void
array_remove(array_ref _self, unsigned index)
{
	struct array *self = _self;
	TYPE_CHECK(self, array);
	int i;
	object_ref removed_obj;
	assert((index < self->count));
	removed_obj = self->contents[index];

	self->contents[index] = NULL;
	for(i = index; i < (self->count - 1); ++i) {
		self->contents[index] = self->contents[index + 1];
		++index;		
	}
	self->count--;
	object_release (removed_obj);
}

int
array_index_of_object(array_ref _self, object_ref obj)
{
	struct array *self = _self;
	TYPE_CHECK(self, array);
	TYPE_CHECK(obj, object);
	assert(!"Method not implemented.");
}

object_ref
array_object_at_index(array_ref _self, unsigned index)
{
	struct array *self = _self;
	TYPE_CHECK(self, array);
	assert ((index < self->count));
	return self->contents[index];
}

iterator_ref
array_create_iterator (array_ref _self) {
	struct array *self = _self;
	TYPE_CHECK(self, array);
	return array_iterator_create (self);
}

/* array_iterator */
array_iterator_ref
array_iterator_create (array_ref array) {
	struct array_iterator *self = Calloc (1, sizeof (struct array_iterator));
	array_iterator_init (self);
	object_retain (self);
	self->array = array;
	return self;
}

void
array_iterator_init (array_iterator_ref _self) {
	struct array_iterator *self = _self;
	iterator_init (self);
	self->magic_num = class_magic_number_array_iterator;
	((struct iterator *)self)->iterator_has_next = _iterator_has_next__array_iterator;
	((struct iterator *)self)->iterator_next = _iterator_next__array_iterator;
}

object_ref
_iterator_next__array_iterator (array_iterator_ref _self) {
	struct array_iterator *self = _self;
	TYPE_CHECK(self,array_iterator);
	return array_object_at_index (self->array, self->current_idx++);
}

bool
_iterator_has_next__array_iterator (array_iterator_ref _self) {
	struct array_iterator *self = _self;
	TYPE_CHECK(self,array_iterator);
	return self->current_idx < array_count (self->array);
}