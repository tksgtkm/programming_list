#pragma once

#ifndef __SKIPLIST_H
#define __SKIPLIST_H

#include <cstdint>
#include <cstdlib>
#include <strings.h>
#include <random>
#include <vector>
#include <string>

#include "run.h"

using namespace std;

default_random_engine generator;
uniform_real_distribution<double> distribution(0.0, 1.0);
const double NODE_PROBABILITY = 0.5;

template<class K, class V, unsigned MAXLEVEL>
class SkipList_Node {

public:
  const K key;
  V value;
  SkipList_Node<K, V, MAXLEVEL>* _forward[MAXLEVEL+1];

  SkipList_Node(const K searchkey):key(searchkey) {
    for (int i = 1; i <= MAXLEVEL; i++) {
      _forward[i] = NULL;
    }
  }

  SkipList_Node(const K search_key, const V val):key(search_key), value(val) {
    for(int i = 1; i <= MAXLEVEL; i++) {
      _forward[i] = NULL;
    }
  }
  virtual ~SkipList_Node(){}
};

template<class K, class V, int MAXLEVEL = 12>
class SkipList : public Run<K, V> {
public:
  typedef SkipList_Node<K, V, MAXLEVEL> Node;

  const int max_level;
  K min;
  K max;

  SkipList(const K minkey, const K maxkey):p_listhead(NULL), p_listtail(NULL),
    cur_max_level(1), max_level(MAXLEVEL), min((K) NULL), max((K) NULL),
    _minkey(minkey), _maxkey(maxkey), _n(0) {
    p_listhead = new Node(_minkey);
    p_listtail = new Node(_maxkey);
    for (int i = 1; i <= MAXLEVEL; i++) {
      p_listhead->_forward[i] = p_listtail;
    }
  }

  ~SkipList() {
    Node* curr_node = p_listhead->_forward[1];
    while (curr_node != p_listtail) {
      Node* temp_node = curr_node;
      curr_node = curr_node->_forward[1];
      delete temp_node;
    }
    delete p_listhead;
    delete p_listtail;
  }

  void insert_key(const K &key, const V &value) {
    if (key > max) {
      max = key;
    } else if (key < min) {
      min = key;
    }
    Node* update[MAXLEVEL];
    Node* curr_node = p_listhead;
    for (int level = cur_max_level; level > 0; level--) {
      while (curr_node->_forward[level]->key < key) {
        curr_node = curr_node->_forward[level];
      }
      update[level] = curr_node;
    }
    curr_node = curr_node->_forward[1];
    if (curr_node->key == key) {
      curr_node->value = value;
    } else {
      int insert_level = generate_node_level();

      if (insert_level > cur_max_level && insert_level < MAXLEVEL - 1) {
        for (int lv = cur_max_level + 1; lv <= insert_level; lv++) {
          update[lv] = p_listhead;
        }
        cur_max_level = insert_level;
      }
      curr_node = new Node(key, value);
      for (int level = 1; level <= cur_max_level; level++) {
        curr_node->_forward[level] = update[level]->_forward[level];
        update[level]->_forward[level] = curr_node;
      }
      ++_n;
    }
  }

  void delete_key(const K &search_key) {
    Node* update[MAXLEVEL];
    Node* curr_node = p_listhead;
    for (int level = cur_max_level; level >= 1; level--) {
      while(curr_node->_forward[level]->key < search_key) {
        curr_node = curr_node->_forward[level];
      }
      update[level] = curr_node;
    }
    curr_node = curr_node->_forward[1];
    if (curr_node->key == search_key) {
      for (int level = 1; level <= cur_max_level; level++) {
        if (update[level]->_forward[level] != curr_node) {
          break;
        }
        update[level]->_forward[level] = curr_node->_forward[level];
      }
      delete curr_node;
      while(cur_max_level > 1 && p_listhead->_forward[cur_max_level] == NULL) {
        cur_max_level--;
      }
    }
    _n--;
  }

  V lookup(const K &search_key, bool &found) {
    Node* curr_node = p_listhead;
    for (int level = cur_max_level; level >= 1; level--) {
      while (curr_node->_forward[level]->key < search_key) {
        curr_node = curr_node->_forward[level];
      }
    }
    curr_node = curr_node->_forward[1];
    if (curr_node->key == search_key) {
      found = true;
      return curr_node->value;
    } else {
      return (V) NULL;
    }
  }

  vector<KVPair<K, V>> get_all() {
    vector<KVPair<K, V>> vec = vector<KVPair<K, V>>();
    auto node = p_listhead->_forward[1];
    while (node != p_listtail) {
      KVPair<K, V> kv = {node->key, node->value};
      vec.push_back(kv);
      node = node->_forward[1];
    }
    return vec;
  }

  vector<KVPair<K, V>> get_all_in_range(const K &key1, const K &key2) {
    if (key1 > max || key2 < min) {
      return (vector<KVPair<K, V>>) {};
    }

    vector<KVPair<K, V>> vec = vector<KVPair<K, V>>();
    auto node = p_listhead->_forward[1];
    while (node->key < key1) {
      node = node->_forward[1];
    }
    while (node->key < key2) {
      KVPair<K, V> kv = {node->key, node->value};
      vec.push_back(kv);
      node = node->_forward[1];
    }
    return vec;
  }

  bool eltin(K &key) {
    return lookup(key);
  }

  inline bool empty() {
    return (p_listhead->forward[1] == p_listtail);
  }

  unsigned long long num_elements() {
    return _n;
  }

  K get_min() {
    return min;
  }

  K get_max() {
    return max;
  }

  void set_size(unsigned long size) {
    _maxsize = size;
  }

  size_t get_size_bytes() {
    return _n * (sizeof(K) + sizeof(V));
  }

  int generate_node_level() {
    return ffs(rand() & ((1 << MAXLEVEL) - 1)) - 1;
  }

  K _minkey;
  K _maxkey;
  unsigned long long _n;
  size_t _maxsize;
  int cur_max_level;
  Node* p_listhead;
  Node* p_listtail;
  uint32_t _keys_per_level[MAXLEVEL];
};

#endif
