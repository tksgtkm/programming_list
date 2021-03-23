#include <stdlib.h>

#include "array_heap.h"

int main() {
  heap_t *heap;
  char nextop;
  heap = create_heap(1000);
  printf("Made Heap\n");
  while((nextop = getchar()) != 'q') {
    if (nextop == 'i') {
      int inskey, *insobj, success;
      insobj = (object_t *)malloc(sizeof(object_t));
      scanf(" %d,%d", &inskey, insobj);
      success = insert(inskey, insobj, heap);
      if (success == 0)
        printf("insert successful, key = %d, object value = %d, current heap size is %d\n",
               inskey, *insobj, heap->current_size);
      else
        printf("insert failed, success = %d\n", success);
    }
    if (nextop == 'd') {
      object_t *delobj;
      getchar();
      delobj = delete_min(heap);
      if (delobj == NULL)
        printf("delete failed\n");
      else
        printf("delete successful, deleted object %d\n", *delobj);
    }
  }
  return 0;
}
