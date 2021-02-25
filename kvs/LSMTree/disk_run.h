#pragma once

#ifndef __DISKRUN_H
#define __DISKRUN_H

#include <vector>
#include <cstdint>
#include <cstring>
#include <string>
#include <cassert>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

#include "run.h"

using namespace std;

template <class K, class V> class DiskLevel;

template <class K, class V>

class DiskRun {
  friend class DiskLevel<K, V>;
public:
  typedef KVPair<K, V> KVPair_t;

  static int compare_KVS(const void * a, const void * b) {
    if (*(KVPair<K, V>*)a <  *(KVPair<K, V>*)b) return -1;
    if (*(KVPair<K, V>*)a == *(KVPair<K, V>*)b) return 0;
    if (*(KVPair<K, V>*)a >  *(KVPair<K, V>*)b) return 1;
    return 10;
  }

  KVPair_t *map;
  int fd;
  unsigned int page_size;
  BloomFilter<K> bf;

  K minkey = INT_MIN;
  K maxkey = INT_MIN;

  DiskRun<K, V> (unsigned long capacity, unsigned int page_size, int level, int runID, double bf_fp):_capacity(capacity),_level(level), _imax_FP(0), page_size(page_size), _runID(runID), _bf_fp(bf_fp), bf(capacity, bf_fp) {
    _filename = "C_" + to_string(level) + "_" + to_string(runID) + ".txt";

    size_t filesize = capacity * sizeof(KVPair_t);

    long result;

    fd = open(_filename.c_str(), O_RDWR | O_CREAT | O_TRUNC, (mode_t) 0600);
    if (fd == -1) {
      perror("Error opening file for writing");
      exit(EXIT_FAILURE);
    }

    result = lseek(fd, filesize - 1, SEEK_SET);
    if (result == -1) {
      close(fd);
      perror("Error calling lseek() to 'stretch' the file");
      exit(EXIT_FAILURE);
    }

    result = write(fd, "", 1);
    if (result != 1) {
      close(fd);
      perror("Error writing last byte of the file");
      exit(EXIT_FAILURE);
    }

    map = (KVPair<K, V>*) mmap(0, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
      close(fd);
      perror("Error mapping the file");
      exit(EXIT_FAILURE);
    }
  }

  ~DiskRun<K, V>(){
    fsync(fd);
    do_unmap();

    if (remove(_filename.c_str())) {
      perror(("Error removing file " + string(_filename)).c_str());
      exit(EXIT_FAILURE);
    }
  }

  void set_capacity(unsigned long new_cap) {
    _capacity = new_cap;
  }

  unsigned long get_capacity() {
    return _capacity;
  }

  void write_data(const KVPair_t *run, const size_t offset, const unsigned long len) {
    memcpy(map + offset, run, len * sizeof(KVPair_t));
    _capacity = len;
  }

  void construct_index() {
    _fence_pointers.reserve(_capacity/page_size);
    _imax_FP = -1;
    for (int j = 0; j < _capacity; j++) {
      bf.add((K*) &map[j].key, sizeof(K));
      if (j%page_size == 0) {
        _fence_pointers.push_back(map[j].key);
        _imax_FP++;
      }
    }
    if(_imax_FP >= 0) {
      _fence_pointers.resize(_imax_FP + 1);
    }

    minkey = map[0].key;
    maxkey = map[_capacity - 1].key;
  }

  unsigned long binary_search(const unsigned long offset, const unsigned long n, const K &key, bool &found) {
    if (n == 0) {
      found = true;
      return offset;
    }
    unsigned long min = offset, max = offset + n - 1;
    unsigned long middle = (min + max) >> 1;
    while (min <= max) {
      if (key > map[middle].key) {
        min = middle + 1;
      } else if (key == map[middle].key) {
        found = true;
        return middle;
      } else {
        max = middle - 1;
      }
      middle = (min + max) >> 1;
    }
    return min;
  }

  void get_flanking_FP(const K &key, unsigned long &start, unsigned long &end) {
    if (_imax_FP == 0) {
      start = 0;
      end = _capacity;
    } else if (key < _fence_pointers[1]) {
      start = 0;
      end = page_size;
    } else if (key >= _fence_pointers[_imax_FP]) {
      start = _imax_FP*page_size;
      end = _capacity;
    } else {
      unsigned min = 0, max = _imax_FP;
      while (min < max) {
        unsigned middle = (min + max) >> 1;
        if (key > _fence_pointers[middle]) {
          if (key < _fence_pointers[middle + 1]) {
            start = middle*page_size;
            end = (middle + 1)*page_size;
            return;
          }
          min = middle + 1;
        } else if(key < _fence_pointers[middle]) {
          if (key >= _fence_pointers[middle - 1]) {
            start = (middle + 1)*page_size;
            end = middle*page_size;
            return;
          }
          max = middle - 1;
        } else {
          start = middle*page_size;
          end = start;
          return;
        }
      }
    }
  }

  unsigned long get_index(const K &key, bool &found) {
    unsigned long start, end;
    get_flanking_FP(key, start, end);
    unsigned long ret = binary_search(start, end - start, key, found);
    return ret;
  }

  V lookup(const K &key, bool &found) {
    unsigned long idx = get_index(key, found);
    V ret = map[idx].value;
    return found ? ret : (V) NULL;
  }

  void range(const K &key1, const K &key2, unsigned long &i1, unsigned long &i2) {
    i1 = 0;
    i2 = 0;
    if (key1 > maxkey || key2 < minkey) {
      return;
    }
    if (key1 >= minkey) {
      bool found = false;
      i1 = get_index(key1, found);
    }
    if (key2 > maxkey) {
      i2 = _capacity;
      return;
    } else {
      bool found = false;
      i2 = get_index(key2, found);
    }
  }

  void print_elts() {
    for (int j = 0; j < _capacity; j++) {
      cout << map[j].key << " ";
    }
    cout << endl;
  }

private:
  unsigned long _capacity;
  string _filename;
  int _level;
  vector<K> _fence_pointers;
  unsigned _imax_FP;
  unsigned _runID;
  double _bf_fp;

  void do_map() {
    size_t filesize = _capacity*sizeof(KVPair_t);
    fd = open(_filename.c_str(), O_RDWR | O_CREAT | O_TRUNC, (mode_t) 0600);
    if (fd == -1) {
      perror("Error opening file for writing");
      exit(EXIT_FAILURE);
    }

    map = (KVPair<K, V>*) mmap(0, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
      close(fd);
      perror("Error mapping the file");
      exit(EXIT_FAILURE);
    }
  }

  void do_unmap() {
    size_t filesize = _capacity*sizeof(KVPair_t);

    if (munmap(map, filesize) == -1) {
      perror("Error un_mapping the file");
    }

    close(fd);
    fd = -5;
  }

  void double_size() {
    unsigned long new_capacity = _capacity*2;

    size_t new_filesize = new_capacity*sizeof(KVPair_t);
    int result = lseek(fd, new_filesize - 1, SEEK_SET);
    if (result == -1) {
      close(fd);
      perror("Error calling lseek() to 'stretch' the file");
      exit(EXIT_FAILURE);
    }

    result = write(fd, "", 1);
    if (result != 1) {
      close(fd);
      perror("Error writing last byte of the file");
      exit(EXIT_FAILURE);
    }

    map = (KVPair<K, V>*) mmap(0, new_filesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
      close(fd);
      perror("Error mmapping the file");
      exit(EXIT_FAILURE);
    }
    _capacity = new_capacity;
  }
};

#endif
