#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <random>
#include <algorithm>

#include <math.h>
#include <stdio.h>

#include "skiplist.h"
#include "bloom.h"
#include "hashmap.h"
#include "lsm.h"

using namespace std;

struct timespec start, finish;
double elapsed;

struct LSMParams {
  const int num_inserts;
  const int num_runs;
  const int elts_per_run;
  const int bf_fp;
  const int page_size;
  const int disk_runs_per_level;
  const int merge_fraction;
};

void insert_lookup_test() {
  std::random_device                 rand_dev;
  std::mt19937                       generator(rand_dev());
  std::uniform_int_distribution<int> distribution(INT32_MIN, INT32_MAX);

  const int num_inserts = 1000000;
  const int num_runs = 20;
  const int buffer_capacity = 800;
  const double bf_fp = .001;
  const int page_size = 512;
  const int disk_runs_per_level = 20;
  const double merge_fraction = 1;
  LSM<int32_t, int32_t> lsmtree = LSM<int32_t, int32_t>(buffer_capacity, num_runs, merge_fraction, bf_fp, page_size, disk_runs_per_level);

  std::vector<int> to_insert;
  for (int i = 0; i < num_inserts; i++) {
    int insert = static_cast<int>(distribution(generator));
    to_insert.push_back(insert);
  }

  std::cout << "Starting inserts" << std::endl;
  clock_gettime(CLOCK_MONOTONIC, &start);
  for (int i = 0; i < num_inserts; i++) {
    if (i % 100000 == 0) cout << "insert " << i << endl;
    lsmtree.insert_key(to_insert[i], i);
  }
  clock_gettime(CLOCK_MONOTONIC, &finish);
  double total_insert = (finish.tv_sec - start.tv_sec);
  total_insert += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

  std::cout << "Time: " << total_insert << " s" << std::endl;
  std::cout << "Inserts per second: " << (int) num_inserts / total_insert << " s" << std::endl;

  std::cout << "Starting lookups" << std::endl;
  clock_gettime(CLOCK_MONOTONIC, &start);
  int lookup;
  for (int i = 0 ; i < num_inserts; i++) {
      if ( i % 100000 == 0 ) cout << "lookup " << i << endl;

      lsmtree.lookup(to_insert[i], lookup);
  }
  clock_gettime(CLOCK_MONOTONIC, &finish);
  double total_lookup = (finish.tv_sec - start.tv_sec);
  total_lookup += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
  std::cout << "Time: " << total_lookup << " s" << std::endl;
  std::cout << "Lookups per second: " << (int) num_inserts / total_lookup << " s" << std::endl;
}

void update_delete_test(){
    const int num_inserts = 500;
    const int num_runs = 3;
    const int buffer_capacity = 50;
    const double bf_fp = .01;
    const int pageSize = 1024;
    const int disk_runs_per_level = 2;
    const double merge_fraction = 1;
    LSM<int32_t, int32_t> lsmtree = LSM<int32_t, int32_t>(buffer_capacity, num_runs,merge_fraction, bf_fp, pageSize, disk_runs_per_level);

    std::vector<int> to_insert;
    for (int i = 0; i < num_inserts; i++) {
        to_insert.push_back(i);
    }

    for (int i = 0; i < num_inserts; i++) {
        lsmtree.insert_key(i, to_insert[i]);
    }
    int lookup;
    for (int i = 0; i < num_inserts; i++) {

        lsmtree.lookup(i, lookup);
        assert(to_insert[i] == lookup);
    }
    lsmtree.print_stats(); // this is a good demo
    cout << "-----------------------------------------" << endl;
    for (int i = 0; i < num_inserts; i++) {
        to_insert[i] = num_inserts - i;
    }

    for (int i = 0; i < num_inserts; i++) {
        lsmtree.insert_key(i, to_insert[i]);
    }
    lsmtree.print_stats(); // this is a good demo
    cout << "-----------------------------------------" << endl;
    for (int i = 0; i < num_inserts; i++) {
        lsmtree.lookup(i, lookup);
        assert(to_insert[i] == lookup);
    }

    for (int i = 0; i < num_inserts; i++) {
        lsmtree.delete_key(i);

    }
    lsmtree.print_stats(); // this is a good demo
    cout << "-----------------------------------------" << endl;

    int negone = -1;
    for (int i = 0; i < num_inserts * 10; i++) {
        lsmtree.insert_key(i,  negone);
    }
    for (int i = 0; i < num_inserts * 10; i++) {

        lsmtree.lookup(i, lookup);
        assert(lookup == -1);
    }
    lsmtree.print_stats(); // this is a good demo
    cout << "-----------------------------------------" << endl;




}

void load_from_bin(LSM<int, int> &lsm, string filename) {
  FILE *int_array_file;
  long size;

  int_array_file = fopen(filename.c_str(), "rb");
  fseek(int_array_file, 0, SEEK_END);
  size = ftell(int_array_file);

  int new_array[size / sizeof(int)];

  rewind(int_array_file);
  size_t num;
  num = fread(new_array, sizeof(int), size/sizeof(int) + 1, int_array_file);
  assert(num == size / sizeof(int));

  int *ptr = new_array;
  int read = 0;
  int k, v;
  while (read + 1 < num) {
    k = *ptr;
    v = *(ptr + 1);
    lsm.insert_key(k, v);
    ptr += 2;
    read += 2;
  }
}

void queryline(LSM<int, int> &lsm, const string &line, vector<string> &strings) {
  unsigned long pos = line.find(' ');
  unsigned long ip = 0;
  strings.clear();

  while (pos != string::npos) {
    strings.push_back(line.substr(ip, pos - ip + 1));
    ip = pos + 1;
    pos = line.find(' ', ip);
  }
  strings.push_back(line.substr(ip, (pos < line.size() ? pos : line.size()) - ip + 1));
  switch((char)strings[0].c_str()[0]) {
    case 'p': {
      int pk = stoi(strings[1]);
      int v = stoi(strings[2]);
      lsm.insert_key(pk, v);
    }
      break;
    case 'g': {
      int lk = stoi(strings[1]);
      int v;
      bool found = lsm.lookup(lk, v);
      if (found) {
        cout << v;
      }
      cout << endl;
    }
      break;
    case 'r': {
      int lk1 = stoi(strings[1]);
      int lk2 = stoi(strings[2]);
      auto res = lsm.range(lk1, lk2);
      if (!res.empty()) {
        for (int i = 0; i < res.size(); ++i) {
          cout << res[i].key << ":" << res[i].value << " ";
        }
      }
      cout << endl;
    }
      break;
    case 'd': {
      int dk = stoi(strings[1]);
      lsm.delete_key(dk);
    }
      break;
    case 'l': {
      string ls = strings[1];
      load_from_bin(lsm, ls);
    }
      break;
    case 's': {
      lsm.print_stats();
    }
  }
}

int main(int argc, char *argv[]) {
  insert_lookup_test();
  update_delete_test();
  auto lsm = LSM<int, int>(800, 20, 1.0, 0.00100, 1024, 20);
  auto strings = vector<string>(3);
  if (argc == 2) {
    while (true) {
      cout << "> ";
      string input;
      getline(cin, input);
      queryline(lsm, input, strings);
    }
  } else {
    string line;
    ifstream f;
    for (int i = 0; i < argc; ++i) {
      f.open(argv[i]);
      if (!f.is_open()) {
        perror("Error open");
        exit(EXIT_FAILURE);
      }
      while (getline(f, line)) {
        queryline(lsm, line, strings);
      }
    }
  }
  return 0;
}
