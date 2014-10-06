#include "array.h"
#include "utils.h"

#define DEFAULT_SIZE 10
#define RESIZE_FACTOR 2

struct array {
	const void ** contents;
	unsigned buffer_size;
	unsigned count;
};

void array_resize(array *arr);

array *
array_create(void)
{
	array *arr = Calloc(1,sizeof(struct array));
	array_resize(arr);
	return arr;
}

void
array_free_with_func (array *arr, free_func func)
{
	int i;
	assert (arr && func);
	for (i = 0; i < array_count (arr); ++i)
		func (array_object_at_index (arr, i));
	array_free (arr);
}

void
array_free (array *arr) {
	assert (arr);
	Free(arr->contents);
	Free (arr);
}

void
array_resize(array *arr)
{
	assert (arr);
	if(!arr->contents)
		arr->contents = Malloc((arr->buffer_size = DEFAULT_SIZE) * sizeof(void *));
	else
		arr->contents = Realloc(arr->contents,(arr->buffer_size *= 2) * sizeof(void *));
}

unsigned
array_count(array *arr)
{
	assert (arr);
	return arr->count;
}

void
array_add(array *arr, const void *obj)
{
	return array_insert (arr, obj, arr->count);
}

void
array_insert(array *arr, const void *obj, unsigned index)
{
	int i;
	const void *temp1 = NULL;
	const void *temp2 = NULL;
	assert (arr && obj && (index <= arr->count));

	if(arr->count >= arr->buffer_size - 1)
		array_resize(arr);
	temp1 = obj;
	for(i = index; i < arr->count; ++i) {
		temp2 = arr->contents[i];
		arr->contents[i] = temp1;
		temp1 = temp2;
	}
	arr->contents[i] = temp1;
	arr->count++;
}

void *
array_remove(array *arr, unsigned index)
{
	int i;
	const void *retval;
	assert (arr && (index > arr->count));
	retval = arr->contents[index];

	arr->contents[index] = NULL;
	for(i = index; i < (arr->count - 1); ++i) {
		arr->contents[index] = arr->contents[index + 1];
		++index;		
	}
	arr->count--;
	return (void *)retval;
}

int
array_index_of_object(array *arr, const void *obj)
{
	int result = 0;
	assert (arr && obj);
	while(result < arr->count) {
		if(obj == arr->contents[result]) return result;
		++result;
	}
	return -1;
}

void *
array_object_at_index(array *arr, unsigned index)
{
	assert (arr && (index < arr->count));
	return (void *)arr->contents[index];
}

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
