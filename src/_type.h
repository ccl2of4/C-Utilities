#ifndef _type_h
#define _type_h

struct type {
	void (*type_dealloc)(type *);
	unsigned retain_count;
};

void type_init (type *);
void _type_dealloc_type (type *);

#endif