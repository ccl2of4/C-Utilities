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
	((struct object *)self)->object_dealloc = _object_dealloc_array;
	array_resize (self);
}

void
_object_dealloc_array (object_ref _self) {
	struct array *self = _self;
	int i;
	for (i = 0; i < array_count (self); ++i)
		object_release (array_object_at_index (self, i));
	Free (self->contents);
}

void
array_resize(array_ref _self)
{
	struct array *self = _self;
	if(!self->contents)
		self->contents = Malloc((self->buffer_size = DEFAULT_SIZE) * sizeof(object_ref));
	else
		self->contents = Realloc(self->contents,(self->buffer_size *= 2) * sizeof(object_ref));
}

unsigned
array_count(array_ref _self)
{
	struct array *self = _self;
	return self->count;
}

void
array_add(array_ref _self, object_ref obj)
{
	struct array *self = _self;
	return array_insert (self, obj, self->count);
}

void
array_insert(array_ref _self, object_ref obj, unsigned index)
{
	struct array *self = _self;
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
	assert (0);
}

object_ref
array_object_at_index(array_ref _self, unsigned index)
{
	struct array *self = _self;
	assert ((index < self->count));
	return self->contents[index];
}