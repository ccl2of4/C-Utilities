/* ============================================ */
/* C implementation of mutable/resizeable array */
/* ============================================ */

typedef struct array array_t;

/* construction/destruction */
array_t *array_create(unsigned);
array_t *array_free(array_t *);

/* accessors*/
int array_index_of_object(array_t *, void *);
void *array_object_at_index(array_t *, unsigned);
unsigned array_count(array_t *);

/* mutators */
void array_add(array_t *, void *);
void array_insert(array_t *, void *, unsigned);
void array_remove_object_at_index(array_t *, unsigned);

/* sorted behavior */
void array_sort(array_t *, int (*compar)(const void *, const void *));
int array_insert_ordered(array_t *, void *, int (*compar)(const void *, const void *));
void *array_search (array_t *, const void *, int (*compar)(const void *, const void *));