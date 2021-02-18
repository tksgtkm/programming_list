#ifndef __HASH_H
#define __HASH_H

#include <stdint.h>

void hash_x86_32(const void * key, int len, uint32_t seed, void * out);
void hash_x86_128(const void * key, int len, uint32_t seed, void * out);
void hash_x64_128(const void * key, int len, uint32_t seed, void * out);

#endif
