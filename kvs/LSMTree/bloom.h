#pragma once

#ifndef bloom_h
#define bloom_h

#include <stdio.h>
#include <cstdint>
#include <vector>
#include <array>
#include <math.h>

#include "hash.h"

using namespace std;

template<class Key>
class BloomFilter {
public:
  BloomFilter(uint64_t n, double fp) {
    double denom = 0.480453013918201;
    double size = -1 * (double) n * (log(fp)/denom);
    m_bits = vector<bool>((int) size);

    double ln2 = 0.693147180559945;
    m_numhashes = (int)ceil((size/n)*ln2);
  }

  array<uint64_t, 2> hash(const Key *data, size_t len) {
    array<uint64_t, 2> hashvalue;

    hash_x64_128(data, (int)len, 0, hashvalue.data());
    return hashvalue;
  }

  uint64_t nthhash(uint32_t n, uint64_t hashA, uint64_t hashB, uint64_t filtersize) {
    return (hashA + n*hashB)%filtersize;
  }

  void add(const Key *data, size_t len) {
    auto hashvalues = hash(data, len);
    for (int n = 0; n < m_numhashes; n++) {
      m_bits[nthhash(n, hashvalues[0], hashvalues[1], m_bits.size())] = true;
    }
  }

  bool may_contain(const Key *data, size_t len) {
    auto hashvalues = hash(data, len);
    for (int n = 0; n < m_numhashes; n++) {
      if (!m_bits[nthhash(n, hashvalues[0], hashvalues[1], m_bits.size())]) {
        return false;
      }
    }
    return true;
  }

private:
  uint8_t m_numhashes;
  vector<bool> m_bits;
};

#endif
