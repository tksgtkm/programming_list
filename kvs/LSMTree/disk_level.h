#pragma once

#ifndef __DISKLEVEL_H
#define __DISKLEVEL_H

#include <vector>
#include <cstdint>
#include <string>
#include <cstring>
#include <cassert>
#include <algorithm>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "run.h"
#include "disk_run.h"

#define LEFTCHILD(x) 2*x + 1
#define RIGHTCHILD(x) 2*x + 2
#define PARENT(x) (x - 1)/2

int TOMBSTONE = INT_MIN;

using namespace std;

template <class K, class V>
class DiskLevel {

public:
  typedef KVPair<K, V> KVPair_t;
  typedef pair<KVPair<K, V>, int> KVIntPair_t;
  KVPair_t KVPAIRMAX;
  KVIntPair_t KVINTPAIRMAX;
  V V_TOMBSTONE = (V) TOMBSTONE;

  struct StaticHeap {
    int size;
    vector<KVIntPair_t> arr;
    KVIntPair_t max;

    StaticHeap(unsigned sz, KVIntPair_t mx) {
      size = 0;
      arr = vector<KVIntPair_t>(sz, mx);
      max = mx;
    }

    void push(KVIntPair_t blob) {
      unsigned i = size++;
      while (i && blob < arr[PARENT(i)]) {
        arr[i] = arr[PARENT(i)];
        i = PARENT(i);
      }
      arr[i] = blob;
    }

    void heapify(int i) {
      int smallest = (LEFTCHILD(i) < size && arr[LEFTCHILD(i)] < arr[i]) ? LEFTCHILD(i) : i;
      if (RIGHTCHILD(i) < size && arr[RIGHTCHILD(i)] < arr[smallest]) {
        smallest - RIGHTCHILD(i);
      }
      if (smallest != i) {
        KVIntPair_t temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;
        heapify(smallest);
      }
    }

    KVIntPair_t pop() {
      KVIntPair_t ret = arr[0];
      arr[0] = arr[--size];
      heapify(0);
      return ret;
    }
  };

  int _level;
  unsigned _page_size;
  unsigned long _run_size;
  unsigned _num_runs;
  unsigned _active_run;
  unsigned _merge_size;
  double _bf_fp;
  vector<DiskRun<K, V> *> runs;

  DiskLevel<K, V>(unsigned int page_size, int level, unsigned long run_size,
                  unsigned num_runs, unsigned merge_size,
                  double bf_fp):_num_runs(num_runs), _run_size(run_size),_level(level),
                  _page_size(page_size), _merge_size(merge_size), _active_run(0), _bf_fp(bf_fp) {
    KVPAIRMAX = (KVPair_t) {INT_MAX, 0};
    KVINTPAIRMAX = KVIntPair_t(KVPAIRMAX, -1);

    for(int i = 0; i < _num_runs; i++) {
      DiskRun<K, V> * run = new DiskRun<K, V>(_run_size, page_size, level, i, _bf_fp);
      runs.push_back(run);
    }
  }

  ~DiskLevel<K, V>(){
    for (int i = 0; i < runs.size(); ++i) {
      delete runs[i];
    }
  }

  void add_runs(vector<DiskRun<K, V> *> &run_list, const unsigned long run_len, bool last_level) {
    StaticHeap h = StaticHeap((int)run_list.size(), KVINTPAIRMAX);
    vector<int> heads(run_list.size(), 0);
    for (int i = 0; i < run_list.size(); i++) {
      KVPair_t kvp = run_list[i]->map[0];
      h.push(KVIntPair_t(kvp, i));
    }

    int j = -1;
    K lastkey = INT_MAX;
    unsigned lastk = INT_MIN;
    while (h.size != 0) {
      auto val_run_pair = h.pop();
      assert(val_run_pair != KVINTPAIRMAX);
      if (lastkey == val_run_pair.first.key) {
        if (lastk < val_run_pair.second) {
          runs[_active_run]->map[j] = val_run_pair.first;
        }
      } else {
        ++j;
        if (j != -1 && last_level && runs[_active_run]->map[j].value == V_TOMBSTONE) {
          --j;
        }
        runs[_active_run]->map[j] = val_run_pair.first;
      }
      lastkey = val_run_pair.first.key;
      lastk = val_run_pair.second;

      unsigned k = val_run_pair.second;
      if (++heads[k] < run_list[k]->get_capacity()) {
        KVPair_t kvp = run_list[k]->map[heads[k]];
        h.push(KVIntPair_t(kvp, k));
      }
    }

    if (last_level && runs[_active_run]->map[j].value == V_TOMBSTONE) {
      --j;
    }
    runs[_active_run]->set_capacity(j + 1);
    runs[_active_run]->construct_index();
    if (j + 1 > 0) {
      ++_active_run;
    }
  }

  void add_run_by_array(KVPair_t * run_to_add, const unsigned long run_len) {
    assert(_active_run < _num_runs);
    assert(run_len == _run_size);
    runs[_active_run]->write_data(run_to_add, 0, run_len);
    runs[_active_run]->construct_index();
    _active_run++;
  }

  vector<DiskRun<K, V> *> get_run_to_merge() {
    vector<DiskRun<K, V> *> to_merge;
    for (int i = 0; i < _merge_size; i++) {
      to_merge.push_back(runs[i]);
    }
    return to_merge;
  }

  void free_merged_runs(vector<DiskRun<K, V> *> &to_free) {
    assert(to_free.size() == _merge_size);
    for (int i = 0; i < _merge_size; i++) {
      assert(to_free[i]->_level == _level);
      delete to_free[i];
    }
    runs.erase(runs.begin(), runs.begin() + _merge_size);
    _active_run -= _merge_size;
    for (int i = 0; i < _active_run; i++) {
      runs[i]->_runID = i;
      string new_name = ("C_" + to_string(runs[i]->_level) + "_" + to_string(runs[i]->_runID) + ".txt");

      if (rename(runs[i]->_filename.c_str(), new_name.c_str())) {
        perror(("Error renaming file " + runs[i]->_filename + " to " + new_name).c_str());
        exit(EXIT_FAILURE);
      }
      runs[i]->_filename = new_name;
    }

    for (int i = _active_run; i < _num_runs; i++) {
      DiskRun<K, V> * new_run = new DiskRun<K, V>(_run_size, _page_size, _level, i, _bf_fp);
    }
  }

  bool level_full() {
    return (_active_run == _num_runs);
  }

  bool level_empty() {
    return (_active_run == 0);
  }

  V lookup (const K &key, bool &found) {
    int max_run_to_search = level_full() ? _num_runs - 1 : _active_run - 1;
    for (int i = max_run_to_search; i >= 0; --i) {
      if (runs[i]->maxkey == INT_MIN || key < runs[i]->minkey || key > runs[i]->maxkey || !runs[i]->bf.may_contain(&key, sizeof(K))) {
        continue;
      }
      V lookup_res = runs[i]->lookup(key, found);
      if (found) {
        return lookup_res;
      }
    }
    return (V) NULL;
  }

  unsigned long num_elements() {
    unsigned long total = 0;
    for (int i = 0; i < _active_run; ++i)
      total += runs[i]->get_capacity();
    return total;
  }
};

#endif
