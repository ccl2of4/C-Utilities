#ifndef macros_h
#define macros_h

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>

#define MAX(A,B) (((B) < (A)) ? (A) : (B))
#define MIN(A,B) (((A) < (B)) ? (A) : (B))

void *Malloc (size_t size);
void *Calloc (size_t num, size_t size);
void *Realloc (void *, size_t);
void Free (void *);

#endif