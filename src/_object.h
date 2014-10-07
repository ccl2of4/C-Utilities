#ifndef _object_h
#define _object_h

struct object {
	void (*object_dealloc)(object_ref);
	bool (*object_equals)(object_ref, object_ref);
	int (*object_hash)(object_ref);
	unsigned retain_count;
};

void object_init (object_ref);
void _object_dealloc_type (object_ref);
bool _object_equals_type (object_ref, object_ref);
int _object_hash_type (object_ref);

#endif