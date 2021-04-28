#include <cstdio>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define MIN(x, y) ((x >= y) ? x : y)

typedef int DATA_TYPE;

enum STATUS {UNSORTED, SORTED, DATA_AVAILABLE, END_OF_FILE};

void merge_sort(char *sorted_file_name) {
  FILE *sorted_file, *tmp_file_1, *tmp_file_2;
  enum STATUS status = UNSORTED, status_a, status_b;
  DATA_TYPE a, b, last = 0;
  int file = 1;
  if ((sorted_file = fopen(sorted_file_name, "r+")) == NULL || (tmp_file_1 = fopen("tmp_1.bin", "w+")) == NULL || (tmp_file_2 = fopen("tmp_2.bin", "w+")) == NULL) {
    cout << "Error: file could not open\n";
    exit(-1);
  }
  while (status == UNSORTED) {
    rewind(sorted_file);
    fclose(tmp_file_1);
    fclose(tmp_file_2);
    remove("tmp_1.bin");
    remove("tmp_2.bin");
    tmp_file_1 = fopen("tmp_1.bin", "w+");
    tmp_file_2 = fopen("tmp_2.bin", "w+");
    while (fscanf(sorted_file, "%d", &a) != EOF) {
      if (a < last) {
        if (file == 1)
          file = 2;
        else
          file = 1;
      }
      last = a;
      if (file == 1)
        fprintf(tmp_file_1, "%d", a);
      else
        fprintf(tmp_file_2, "%d", a);
    }
    fclose(sorted_file);
    remove(sorted_file_name);
    sorted_file = fopen(sorted_file_name, "w+");
    rewind(tmp_file_1);
    rewind(tmp_file_2);
    status_a = DATA_AVAILABLE;
    status_b = DATA_AVAILABLE;
    if (fscanf(tmp_file_1, "%d", &a) == EOF) {
      status = SORTED;
      status_a = END_OF_FILE;
    }
    if (fscanf(tmp_file_2, "%d", &b) == EOF) {
      status = SORTED;
      status_b = END_OF_FILE;
    }
    last = MIN(a, b);
    while (status_a != END_OF_FILE && status_b != END_OF_FILE) {
      if (a <= b && a >= last) {
        fprintf(sorted_file, "%d", a);
        last = a;
        if (fscanf(tmp_file_1, "%d", &a) == EOF)
          status_a = END_OF_FILE;
      } else if (b <= a && b >= last) {
        fprintf(sorted_file, "%d", b);
        last = b;
        if (fscanf(tmp_file_2, "%d", &b) == EOF)
          status_b = END_OF_FILE;
      } else if (a >= last) {
        fprintf(sorted_file, "%d", a);
        last = a;
        if (fscanf(tmp_file_1, "%d", &a) == EOF)
          status_a = END_OF_FILE;
      } else if (b >= last) {
        fprintf(sorted_file, "%d", b);
        last = b;
        if (fscanf(tmp_file_2, "%d", &b) == EOF)
          status_b = END_OF_FILE;
      } else {
        last = MIN(a, b);
      }
    }
    while (status_a != END_OF_FILE) {
      fprintf(sorted_file, "%d", a);
      if (fscanf(tmp_file_1, "%d", &a) == EOF)
        status_a = END_OF_FILE;
    }
    while (status_b != END_OF_FILE) {
      fprintf(sorted_file, "%d", b);
      if (fscanf(tmp_file_2, "%d", &b) == EOF)
        status_b = END_OF_FILE;
    }
  }
  fclose(sorted_file);
  fclose(tmp_file_1);
  fclose(tmp_file_2);
  remove("tmp_1.bin");
  remove("tmp_2.bin");
}

int main() {
  system("cp unsorted.bin sorted.bin");

  char s[] = "sorted.bin";

  merge_sort(s);

  return 0;
}
