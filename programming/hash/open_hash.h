#ifndef __OpenHash
#define __OpenHash

#include "member.h"

typedef enum {
  Occupied, Empty, Deleted
} Status;

typedef struct {
  Member data;
  Status stat;
} Bucket;

typedef struct {
  int size;
  Bucket *table;
} OpenedHash;

int Initialize(OpenedHash *h, int size);

Bucket *Search(const OpenedHash *h, const Member *x);

int Add(OpenedHash *h, const Member *x);

int Remove(OpenedHash *h, const Member *x);

void Dump(const OpenedHash *h);

void Clear(OpenedHash *h);

void Terminate(OpenedHash *h);

#endif
