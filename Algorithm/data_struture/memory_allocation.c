#include <stdio.h>
#include <stdlib.h>

typedef struct mem_bk {
  int size;
  unsigned char magic;
  unsigned char occupied;
  struct mem_bk *next;
  struct mem_bk *prev;
} memblock;

#define HEADER_SIZE (sizeof(struct memblock))

#define DELTA 20

#define MEM_MAGIC 0xa5

#define WORDSIZE 4

#define WORD_ALIGN(n) (((n) + WORDSIZE - 1) & -WORDSIZE)

struct memblock block_chain;

#define HEAP_SIZE 10000
char memory_heap[HEAP_SIZE];

int main() {
  return 0;
}
