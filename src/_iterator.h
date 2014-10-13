#ifndef _iterator_h
#define _iterator_h

#include "_iterator.h"
#include "_object.h"

struct iterator {
	struct object base;
	enum class_magic_number magic_num;
	object_ref (*iterator_next)(iterator_ref);
	bool (*iterator_has_next)(iterator_ref);
};

void iterator_init (iterator_ref);
object_ref _iterator_next__iterator (iterator_ref);
bool _iterator_has_next__iterator (iterator_ref);

#endif