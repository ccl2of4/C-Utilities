#ifndef _type_h
#define _type_h

struct type {
	void (*type_dealloc)(type *);
	bool (*type_equals)(type *, type *);
	int (*type_hash)(type *);
	unsigned retain_count;
};

void type_init (type *);
void _type_dealloc_type (type *);
bool _type_equals_type (type *, type *);
int _type_hash_type (type *);

#endif