#pragma once

#ifndef __LSM_H
#define __LSM_H

#include <cstdio>
#include <cstdint>
#include <stdlib.h>
#include <future>
#include <vector>
#include <mutex>
#include <thread>

#include "run.h"
#include "skiplist.h"
#include "bloom.h"
#include "disk_level.h"

template <class K, class V>
class LSM {
  typedef SkipList<K, V> RunType;

public:
  V V_TOMBSTONE = (V) TOMBSTONE;
  mutex *merge_lock;

  vector<Run<K, V> *> C_0;

  vector<BloomFilter<K> *> filters;
  vector<DiskLevel<K, V> *> disk_levels;

  LSM<K, V>(const LSM<K, V> &other) = default;
  LSM<K, V>(LSM<K, V> &&other) = default;

  LSM<K, V>(unsigned long elts_per_run, unsigned int num_runs, double merged_frac, double bf_fp, unsigned int page_size,
            unsigned int disk_runs_per_level): _elts_per_run(elts_per_run), _num_runs(num_runs), _frac_runs_merged(merged_frac), _disk_runs_per_level(disk_runs_per_level), _num_to_merge(ceil(_frac_runs_merged * _num_runs)), _page_size(page_size) {
    _active_run = 0;
    _bf_false_positive_rate = bf_fp;
    _n = 0;

    DiskLevel<K, V> * disk_level = new DiskLevel<K, V>(page_size, 1, _num_to_merge * _elts_per_run, _disk_runs_per_level, ceil(_disk_runs_per_level * _frac_runs_merged), _bf_false_positive_rate);

    disk_levels.push_back(disk_level);
    _num_disk_levels = 0;

    for (int i = 0; i < _num_runs; i++) {
      RunType * run = new RunType(INT32_MIN, INT32_MAX);
      run->set_size(_elts_per_run);
      C_0.push_back(run);
      BloomFilter<K> * bf = new BloomFilter<K>(_elts_per_run, _bf_false_positive_rate);
      filters.push_back(bf);
    }
    merge_lock = new mutex();
  }

  ~LSM<K, V>() {
    if (merge_thread.joinable()) {
      merge_thread.join();
    }
    delete merge_lock;
    for (int i = 0; i < C_0.size(); ++i) {
      delete C_0[i];
      delete filters[i];
    }
    for (int i = 0; i < disk_levels.size(); ++i) {
      delete disk_levels[i];
    }
  }

  void insert_key(K &key, V &value) {
    if (C_0[_active_run]->num_elements() >= _elts_per_run) {
      ++_active_run;
    }
    if (_active_run >= _num_runs) {
      do_merge();
    }
    C_0[_active_run]->insert_key(key, value);
    filters[_active_run]->add(&key, sizeof(K));
  }

  bool lookup(K &key, V &value) {
    bool found = false;
    for (int i = _active_run; i >= 0; --i) {
      if (key < C_0[i]->get_min() || key > C_0[i]->get_max() || filters[i]->may_contain(&key, sizeof(K)))
        continue;

      value = C_0[i]->lookup(key, found);
      if (found) {
        return value != V_TOMBSTONE;
      }
    }

    if (merge_thread.joinable()) {
      merge_thread.join();
    }
    for (int i = 0; i < _num_disk_levels; i++) {
      value = disk_levels[i]->lookup(key, found);
      if (found) {
        return value != V_TOMBSTONE;
      }
    }
    return false;
  }

  void delete_key(K &key) {
    insert_key(key, V_TOMBSTONE);
  }

  vector<KVPair<K, V>> range(K &key1, K &key2) {
    if (key2 <= key1) {
      return (vector<KVPair<K, V>> {});
    }
    auto ht = HashTable<K, V>(4096 * 1000);
    vector<KVPair<K, V>> elts_in_range = vector<KVPair<K, V>>();

    for (int i = _active_run; i >= 0; --i) {
      vector<KVPair<K, V>> cur_elts = C_0[i]->get_all_in_range(key1, key2);
      if (cur_elts.size() != 0) {
        elts_in_range.reserve(elts_in_range.size() + cur_elts.size());
        for (int c = 0; c < cur_elts.size(); c++) {
          V dummy = ht.put_if_empty(cur_elts[c].key, cur_elts[c].value);
          if (!dummy && cur_elts[c].value != V_TOMBSTONE) {
            elts_in_range.push_back(cur_elts[c]);
          }
        }
      }
    }

    if (merge_thread.joinable()) {
      merge_thread.join();
    }

    for (int j = 0; j < _num_disk_levels; j++) {
      for (int r = disk_levels[j]->_active_run - 1; r >= 0; --r) {
        unsigned long i1, i2;
        disk_levels[j]->runs[r]->range(key1, key2, i1, i2);
        if (i2 - i1 != 0) {
          auto old_size = elts_in_range.size();
          elts_in_range.reserve(old_size + (i2 - i1));
          for (unsigned long m = i1; m < i2; ++m) {
            auto KV = disk_levels[j]->runs[r]->map[m];
            V dummy = ht.put_if_empty(KV.key, KV.value);
            if (!dummy && KV.value != V_TOMBSTONE) {
              elts_in_range.push_back(KV);
            }
          }
        }
      }
    }
    return elts_in_range;
  }

  void print_elts() {
    if (merge_thread.joinable())
      merge_thread.join();
    cout << "MEMORY BUFFER" << endl;
    for (int i = 0; i <= _active_run; i++) {
      cout << "MEMORY BUFFER RUN" << i << endl;
      auto all = C_0[i]->get_all();
      for (KVPair<K, V> &c : all) {
        cout << c.key << ":" << c.value << " ";
      }
      cout << endl;
    }

    cout << "\nDISK BUFFER" << endl;
    for (int i = 0; i < _num_disk_levels; i++) {
      cout << "DISK LEVEL " << i << endl;
      for (int j = 0; j < disk_levels[i]->_active_run; j++) {
        cout << "RUN " << j << endl;
        for (int k = 0; k < disk_levels[i]->runs[j]->get_capacity(); k++) {
          cout << disk_levels[i]->runs[j]->map[k].key << ":" << disk_levels[i]->runs[j]->map[k].value << " ";
        }
        cout << endl;
      }
      cout << endl;
    }
  }

  void print_stats() {
    cout << "Number of Elements: " << size() << endl;
    cout << "Number of Elements in Buffer (including deletes): " << num_buffer() << endl;

    for (int i = 0; i < disk_levels.size(); ++i) {
      cout << "Number of Elements in Disk Level " << i << "(including deletes): " << disk_levels[i]->num_elements() << endl;
    }
    cout << "KEY VALUE DUMP BY LEVEL: " << endl;
    print_elts();
  }

  unsigned int _active_run;
  unsigned long _elts_per_run;
  double _bf_false_positive_rate;
  unsigned int _num_runs;
  double _frac_runs_merged;
  unsigned int _num_disk_levels;
  unsigned int _disk_runs_per_level;
  unsigned int _num_to_merge;
  unsigned int _page_size;
  unsigned long _n;
  thread merge_thread;

  void merge_runs_to_level(int level) {
    bool is_last = false;

    if (level == _num_disk_levels) {
      DiskLevel<K, V> * new_level = new DiskLevel<K, V>(_page_size, level + 1,
        disk_levels[level - 1]->_run_size * disk_levels[level - 1]->_merge_size, _disk_runs_per_level, ceil(_disk_runs_per_level * _frac_runs_merged), _bf_false_positive_rate);
      disk_levels.push_back(new_level);
      _num_disk_levels++;
    }

    if (disk_levels[level]->level_full()) {
      merge_runs_to_level(level + 1);
    }

    if (level + 1 == _num_disk_levels && disk_levels[level]->level_empty()) {
      is_last = true;
    }

    vector<DiskRun<K, V> *> runs_to_merge = disk_levels[level - 1]->get_run_to_merge();
    unsigned long run_len = disk_levels[level - 1]->_run_size;
    disk_levels[level]->add_runs(runs_to_merge, run_len, is_last);
    disk_levels[level - 1]->free_merged_runs(runs_to_merge);
  }

  void merge_runs(vector<Run<K, V> *> runs_to_merge, vector<BloomFilter<K> *> bf_to_merge) {
    vector<KVPair<K, V>> to_merge = vector<KVPair<K, V>>();
    to_merge.reserve(_elts_per_run * _num_to_merge);
    for (int i = 0; i < runs_to_merge.size(); i++) {
      auto all = (runs_to_merge)[i]->get_all();
      to_merge.insert(to_merge.begin(), all.begin(), all.end());
      delete (runs_to_merge)[i];
      delete (bf_to_merge)[i];
    }
    sort(to_merge.begin(), to_merge.end());
    merge_lock->lock();
    if (disk_levels[0]->level_full()) {
      merge_runs_to_level(1);
    }
    disk_levels[0]->add_run_by_array(&to_merge[0], to_merge.size());
    merge_lock->unlock();
  }

  void do_merge() {
    if (_num_to_merge == 0) {
      return;
    }
    vector<Run<K, V> *> runs_to_merge = vector<Run<K, V> *>();
    vector<BloomFilter<K> *> bf_to_merge = vector<BloomFilter<K> *>();
    for (int i = 0; i < _num_to_merge; i++) {
      runs_to_merge.push_back(C_0[i]);
      bf_to_merge.push_back(filters[i]);
    }
    if (merge_thread.joinable()) {
      merge_thread.join();
    }
    merge_thread = thread(&LSM::merge_runs, this, runs_to_merge, bf_to_merge);

    C_0.erase(C_0.begin(), C_0.begin() + _num_to_merge);
    filters.erase(filters.begin(), filters.begin() + _num_to_merge);
    _active_run -= _num_to_merge;
    for (int i = _active_run; i < _num_runs; i++) {
      RunType * run = new RunType(INT32_MIN, INT32_MIN);
      run->set_size(_elts_per_run);
      C_0.push_back(run);
      BloomFilter<K> * bf = new BloomFilter<K>(_elts_per_run, _bf_false_positive_rate);
      filters.push_back(bf);
    }
  }

  unsigned long num_buffer() {
    if (merge_thread.joinable())
      merge_thread.join();
    unsigned long total = 0;
    for (int i = 0; i <= _active_run; ++i)
      total += C_0[i]->num_elements();
    return total;
  }

  unsigned long size() {
    K min = INT_MIN;
    K max = INT_MAX;
    auto r = range(min, max);
    return r.size();
  }
};

#endif
