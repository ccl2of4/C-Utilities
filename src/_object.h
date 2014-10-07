#ifndef _object_h
#define _object_h

struct object {
	void (*object_dealloc)(object *);
	bool (*object_equals)(object *, object *);
	int (*object_hash)(object *);
	unsigned retain_count;
};

void object_init (object *);
void _object_dealloc_type (object *);
bool _object_equals_type (object *, object *);
int _object_hash_type (object *);

#endif