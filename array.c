#include <stdlib.h>
#include <stdio.h>
#include "array.h"

#define DEFAULT_SIZE 10
#define RESIZE_FACTOR 2

struct array {
	void **contents;
	unsigned buffer_size;
	unsigned count;
};

void array_resize(array *arr);

array *
array_create(unsigned buffer_size)
{
	if(!buffer_size) buffer_size = DEFAULT_SIZE;
	array *arr = malloc(sizeof(struct array));
	if(!arr) { printf("Out of memory.\n"); exit(1); }
	arr->count = 0;
	arr->contents = NULL;
	array_resize(arr);
	return arr;
}

array *
array_free (array *arr)
{
	free(arr->contents);
	return arr;
}

void
array_resize(array *arr)
{
	if(!arr->contents) {
		arr->contents = malloc((arr->buffer_size = DEFAULT_SIZE) * sizeof(void *));
		if(!arr->contents) { printf("Out of memory.\n"); exit(1); }
	}
	else {
		arr->contents = realloc(arr->contents,(arr->buffer_size *= 2) * sizeof(void *));
		if(!arr->contents) { printf("Out of memory.\n"); exit(1); }
	}
}

unsigned
array_count(array *arr)
{
	return arr->count;
}

void
array_add(array *arr, void *obj)
{
	return array_insert (arr, obj, arr->count);
}

void
array_insert(array *arr, void *obj, unsigned index)
{
	int i;
	void *temp1 = NULL;
	void *temp2 = NULL;

	if(!obj) return;
	if(arr->count >= arr->buffer_size - 1)
		array_resize(arr);
	temp1 = obj;
	for(i = index; i < arr->count; i++) {
		temp2 = arr->contents[i];
		arr->contents[i] = temp1;
		temp1 = temp2;
	}
	arr->contents[i] = temp1;
	arr->count++;
}

void
array_remove_object_at_index(array *arr, unsigned index)
{
	int i;
	if(index >= arr->count) return;
	arr->contents[index] = NULL;
	for(i = index; i < (arr->count - 1); i++) {
		arr->contents[index] = arr->contents[index + 1];
		++index;		
	}
	arr->count--;
}

int
array_index_of_object(array *arr, void *obj)
{
	int result = 0;
	while(result < arr->count) {
		if(obj == arr->contents[result]) return result;
		++result;
	}
	return -1;
}

void *
array_object_at_index(array *arr, unsigned index)
{
	if(index >= arr->count) return NULL;
	return arr->contents[index];
}

void
array_sort(array *arr, int (*compar)(const void*, const void*))
{
	qsort(arr->contents, arr->count, sizeof(void *), compar);
}

int
array_insert_ordered(array *arr, void *obj, int (*compar)(const void*, const void*))
{
	int index = 0;
	while(index < arr->count && compar(&obj,&arr->contents[index]) >= 0) ++index;
    array_insert(arr,obj,index);
	return index;
}

void *
array_search (array *arr, const void *key, int (*compar)(const void *, const void *))
{
	return *(void **)bsearch (key, arr->contents, arr->count, sizeof(void *), compar);
}
