/* ============================================ */
/* C implementation of mutable/resizeable array */
/* ============================================ */

typedef struct array array;

/* construction/destruction */
array *array_create(unsigned);
array *array_free(array *);

/* accessors*/
int array_index_of_object(array *, void *);
void *array_object_at_index(array *, unsigned);
unsigned array_count(array *);

/* mutators */
void array_add(array *, void *);
void array_insert(array *, void *, unsigned);
void array_remove_object_at_index(array *, unsigned);

/* sorted behavior */
void array_sort(array *, int (*compar)(const void *, const void *));
int array_insert_ordered(array *, void *, int (*compar)(const void *, const void *));
void *array_search (array *, const void *, int (*compar)(const void *, const void *));
