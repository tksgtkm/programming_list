#pragma once

#include <stdlib.h>
#include <cstdint>
#include <climits>

#include "hash.h"

#ifndef __HASHMAP_H
#define __HASHMAP_H

template <typename K, typename V>
class HashTable {
public:
  unsigned long _size;
  unsigned long _elts;
  KVPair<K, V> EMPTY = {INT_MIN, INT_MIN};

  HashTable(unsigned long size): _size(2 * size), _elts(0) {
    table = new KVPair<K, V> [_size]();
    fill(table + 0, table + _size, (KVPair<K, V>) EMPTY);
  }

  ~HashTable() {
    delete [] table;
  }

  void resize() {
    _size *= 2;
    auto new_table = new KVPair<K, V> [_size]();
    fill(new_table + 0, new_table + _size, (KVPair<K, V>) EMPTY);

    for (unsigned long i = 0; i < _size / 2; i++) {
      if (table[i] != EMPTY) {
        unsigned long new_hash = hash_func(table[i].key);

        for (int j = 0;; j++) {
          if (new_table[(new_hash + j) % _size] == EMPTY) {
            new_table[(new_hash + j) % _size] = table[i];
            break;
          }
        }
      }
    }
    delete [] table;
    table = new_table;
  }

  bool get(const K &key, V &value) {
    unsigned long hash_value = hash_func(key);
    for (int i = 0;; ++i) {
      if (table[(hash_value + i) % _size] == EMPTY) {
        return false;
      } else if (table[(hash_value + i) % _size].key == key) {
        value = table[(hash_value + i) % _size].value;
        return true;
      }
    }
    return false;
  }

  void put(const K &key, const V &value) {
    if (_elts * 2 > _size) {
      resize();
    }
    unsigned long hash_value = hash_func(key);
    KVPair<K, V> node;

    for (unsigned long i = 0;; i++) {
      if (table[(hash_value + i) % _size] == EMPTY) {
        table[(hash_value + i) % _size].key = key;
        table[(hash_value + i) % _size].value = value;
        ++_elts;
        return;
      } else if (table[(hash_value + i) % _size].key == key) {
        table[(hash_value + i) % _size].value = value;
        return;
      }
    }
  }

  V put_if_empty(const K &key, const V &value) {
    if (_elts * 2 > _size) {
      resize();
    }
    unsigned long hash_value = hash_func(key);

    for (unsigned long i = 0;; i++) {
      if (table[(hash_value + i) % _size] == EMPTY) {
        table[(hash_value + i) % _size].key = key;
        table[(hash_value + i) % _size].value = value;
        ++_elts;
        return (V) NULL;
      } else if (table[(hash_value + i) % _size].key == key) {
        return table[(hash_value + i) % _size].value;
      }
    }
  }

  unsigned long hash_func(const K key) {
    array<unsigned long, 2> hash_value;
    hash_x64_128(&key, sizeof(K), 0, hash_value.data());
    return (hash_value[0] % _size);
  }

private:
  KVPair<K, V> *table;
};

#endif
