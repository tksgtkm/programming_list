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

    StatiHeap(unsigned sz, KVIntPair_t mx) {
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
                _pageSize(page_size), _mergeSize(merge_size), _active_run(0), _bf_fp(bf_fp) {
  KVPAIRMAX = (KVPair_t) {INT_MAX, 0};
  KVINTPAIRMAX = KVIntPair_t(KVINTPAIRMAX, -1);

  for(int i = 0; i < _num_runs; i++) {
    DiskRun<K, V> * run = new DiskRun<K, V>(_run_size, page_size, level, i, _bf_fp);
    runs.push_back(run);
  }
}

~DIskLevel<K, V>(){
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
    
  }
}
