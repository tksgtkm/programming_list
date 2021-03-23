#include <stdlib.h>
#include <stdio.h>

#include "array_heap.h"

heap_t *create_heap(int size) {
  heap_t *hp;
  hp = (heap_t *)malloc(sizeof(heap_t));
  hp->heap = (heap_el_t *)malloc(size*sizeof(heap_el_t));
  hp->max_size = size;
  hp->current_size = 0;
  return hp;
}

int heap_empty(heap_t *hp) {
  return (hp->current_size == 0);
}

heap_el_t *find_min(heap_t *hp) {
  return (hp->heap);
}

int insert(key_t new_key, object_t *new_object, heap_t *hp) {
  if (hp->current_size < hp->max_size) {
    int gap;
    gap = hp->current_size++;
    while(gap > 0 && new_key < (hp->heap[(gap - 1)/2]).key) {
      (hp->heap[gap]).key = (hp->heap[(gap - 1)/2]).key;
      (hp->heap[gap]).object = (hp->heap[(gap - 1)/2]).object;
      gap = (gap - 1)/2;
    }
    (hp->heap[gap]).key = new_key;
    (hp->heap[gap]).object = new_object;
    return 0;
  } else {
    return -1;
  }
}

object_t *delete_min(heap_t *hp) {
  object_t *del_obj;
  int reached_top = 0;
  int gap, newgap, last;
  if (hp->current_size == 0)
    return NULL;
  del_obj = (hp->heap[0]).object;
  gap = 0;
  while (!reached_top) {
    if (2*gap + 2 < hp->current_size) {
      if ((hp->heap[2*gap + 1]).key < (hp->heap[2*gap + 2]).key)
        newgap = 2*gap + 1;
      else
        newgap = 2*gap + 2;
      (hp->heap[gap]).key = (hp->heap[newgap]).key;
      (hp->heap[gap]).object = (hp->heap[newgap]).object;
      gap = newgap;
    } else if (2*gap + 2 == hp->current_size) {
      newgap = 2*gap + 1;
      (hp->heap[gap]).key = (hp->heap[newgap]).key;
      (hp->heap[gap]).object = (hp->heap[newgap]).object;
      hp->current_size -= 1;
      return del_obj;
    } else {
      reached_top = 1;
    }
  }
  last += --hp->current_size;
  while(gap > 0 && (hp->heap[last]).key < (hp->heap[(gap - 1)/2]).key) {
    (hp->heap[gap]).key = (hp->heap[(gap - 1)/2]).key;
    (hp->heap[gap]).object = (hp->heap[(gap - 1)/2]).object;
    gap = (gap - 1)/2;
  }
  (hp->heap[gap]).key = (hp->heap[last]).key;
  (hp->heap[gap]).object = (hp->heap[last]).object;
  return del_obj;
}

void remove_heap(heap_t *hp) {
  free(hp->heap);
  free(hp);
}
