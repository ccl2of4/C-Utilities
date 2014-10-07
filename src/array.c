#include "array.h"
#include "_array.h"
#include "utils.h"

array *
array_create(void)
{
	array *arr = Calloc(1,sizeof(struct array));
	array_init (arr);
	type_retain ((type *)arr);
	return arr;
}

void
array_init (array *arr) {
	type_init (&arr->base);
	((type *)arr)->type_dealloc = _type_dealloc_array;
	array_resize (arr);
}

void
_type_dealloc_array (type *t) {
	array* arr = (array *)t;
	int i;
	for (i = 0; i < array_count (arr); ++i)
		type_release (array_object_at_index (arr, i));
	Free (arr->contents);
}

void
array_resize(array *arr)
{
	assert (arr);
	if(!arr->contents)
		arr->contents = Malloc((arr->buffer_size = DEFAULT_SIZE) * sizeof(type *));
	else
		arr->contents = Realloc(arr->contents,(arr->buffer_size *= 2) * sizeof(type *));
}

unsigned
array_count(array *arr)
{
	assert (arr);
	return arr->count;
}

void
array_add(array *arr, type *obj)
{
	return array_insert (arr, obj, arr->count);
}

void
array_insert(array *arr, type *obj, unsigned index)
{
	int i;
	type *temp1 = NULL;
	type *temp2 = NULL;
	assert (arr && obj && (index <= arr->count));

	if(arr->count >= arr->buffer_size - 1)
		array_resize(arr);
	temp1 = obj;
	for(i = index; i < arr->count; ++i) {
		temp2 = arr->contents[i];
		arr->contents[i] = temp1;
		temp1 = temp2;
	}
	type_retain (obj);
	arr->contents[i] = temp1;
	arr->count++;
}

void
array_remove(array *arr, unsigned index)
{
	int i;
	type *retval;
	assert (arr && (index < arr->count));
	retval = arr->contents[index];

	arr->contents[index] = NULL;
	for(i = index; i < (arr->count - 1); ++i) {
		arr->contents[index] = arr->contents[index + 1];
		++index;		
	}
	arr->count--;
	type_release (retval);
}

int
array_index_of_object(array *arr, type *obj)
{
	int result = 0;
	assert (arr && obj);
	while(result < arr->count) {
		if(obj == arr->contents[result]) return result;
		++result;
	}
	return -1;
}

type *
array_object_at_index(array *arr, unsigned index)
{
	assert (arr && (index < arr->count));
	return arr->contents[index];
}

/*
void
array_sort(array *arr, int (*compar)(const void*, const void*))
{
	assert (arr && compar);
	qsort(arr->contents, arr->count, sizeof(void *), compar);
}

int
array_insert_ordered(array *arr, void *obj, int (*compar)(const void*, const void*))
{
	int index = 0;
	assert (arr && obj && compar);
	while(index < arr->count && compar(&obj,&arr->contents[index]) >= 0) ++index;
	array_insert(arr,obj,index);
	return index;
}

void *
array_search (array *arr, const void *key, int (*compar)(const void *, const void *))
{
	assert (arr && key && compar);
	return *(void **)bsearch (key, arr->contents, arr->count, sizeof(void *), compar);
}
*/