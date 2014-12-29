#ifndef _object_h
#define _object_h

struct object {
	enum class_magic_number magic_num;
	unsigned retain_count;
	void (*object_dealloc)(object_ref);
	bool (*object_equals)(object_ref, object_ref);
	int (*object_hash)(object_ref);
};

void object_init (object_ref);

//override
void _object_dealloc__object (object_ref);
bool _object_equals__object (object_ref, object_ref);
int _object_hash__object (object_ref);

#endif