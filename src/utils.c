#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

void *
Malloc (size_t size) {
	void *result = malloc (size);
	if (!result) {
		printf ("Out of memory.\n");
		exit (1);
	}
	return result;
}

void
*Calloc (size_t num, size_t size) {
	void *result = calloc (num, size);
	if (!result) {
		printf ("Out of memory.\n");
		exit (1);
	}
	return result;
}

void
*Realloc (void *ptr, size_t size) {
	void *result = realloc (ptr, size);
	if (!result) {
		printf ("Out of memory.\n");
		exit (1);
	}
	return result;
}

void
Free (void *ptr) {
	free (ptr);
}