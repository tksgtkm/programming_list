#include <stdio.h>
#include <stdlib.h>

#include "member.h"
#include "open_hash.h"

static int hash(int key, int size) {
  return key % size;
}

static int rehash(int key, int size) {
  return (key + 1) % size;
}

static void set_bucket(Bucket *n, const Member *x, Status stat) {
  n->data = *x;
  n->stat = stat;
}

int Initialize(OpenedHash *h, int size) {
  int i;

  if ((h->table = calloc(size, sizeof(Bucket))) == NULL) {
    h->size = 0;
    return 0;
  }

  h->size = size;
  for (i = 0; i < size; i++)
    h->table[i].stat = Empty;
  return 1;
}

Bucket *Search(const OpenedHash *h, const Member *x) {
  int i;
  int key = hash(x->no, h->size);
  Bucket *p = &h->table[key];

  for (i = 0; p->stat != Empty && i < h->size; i++) {
    if (p->stat ==  Occupied && p->data.no == x->no)
      return p;
    key = rehash(key, h->size);
    p = &h->table[key];
  }
  return NULL;
}

int Add(OpenedHash *h, const Member *x) {
  int i;
  int key = hash(x->no, h->size);
  Bucket *p = &h->table[key];

  if (Search(h, x))
    return 1;

  for (i = 0; i < h->size; i++) {
    if (p->stat == Empty || p->stat == Deleted) {
      set_bucket(p, x, Occupied);
      return 0;
    }
    key = rehash(key, h->size);
    p = &h->table[key];
  }
  return 2;
}

int Remove(OpenedHash *h, const Member *x) {
  Bucket *p = Search(h, x);

  if (p == NULL)
    return 1;

  p->stat = Deleted;
  return 0;
}

void Dump(const OpenedHash *h) {
  int i;

  for (i = 0; i < h->size; i++) {
    printf("%02d : ", i);
    switch(h->table[i].stat) {
      case Occupied:
        printf("%d (%s)\n", h->table[i].data.no, h->table[i].data.name);
        break;
      case Empty:
        printf("-- not register --\n");
        break;
      case Deleted:
        printf("-- deleted --\n");
        break;
    }
  }
}

void Clear(OpenedHash *h) {
  int i;
  for (i = 0; i < h->size; i++) {
    h->table[i].stat = Empty;
  }
}

void Terminate(OpenedHash *h) {
  free(h->table);
  h->size = 0;
}
