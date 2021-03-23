#include <stdlib.h>
#include <stdio.h>

typedef int key_t;
typedef int object_t;
typedef struct {key_t key; object_t *object;} heap_el_t;
typedef struct {int max_size;
                int current_size;
                heap_el_t *heap;
              } heap_t;

heap_t *create_heap(int size);

int heap_empty(heap_t *hp);

heap_el_t *find_min(heap_t *hp);

int insert(key_t new_key, object_t *new_object, heap_t *hp);

object_t *delete_min(heap_t *hp);

void remove_heap(heap_t *hp);
