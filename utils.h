#ifndef macros_h
#define macros_h

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stddef.h>

#define MAX(A,B) (((B) < (A)) ? (A) : (B))
#define MIN(A,B) (((A) < (B)) ? (A) : (B))

void *Malloc (size_t size);
void *Calloc (size_t num, size_t size);
void *Realloc (void *, size_t);
void Free (void *);

#define RETAINED_MEMBER_SWAP(self, a, b) do {\
	if (self->a != b) {\
		if (self->a)\
			object_release (self->a);\
		self->a = b;\
		if (self->a)\
			object_retain (self->a);\
	}\
} while (0)

#endif