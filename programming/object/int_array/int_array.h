#ifndef __INTARRAY_H
#define __INTARRAY_H

class IntArray {
  int nelem;
  int* vec;

public:
  IntArray(int size) : nelem(size) {
    vec = new int[nelem];
  }

  int size() const {
    return nelem;
  }

  int& operator[](int i) {
    return vec[i];
  }
};

#endif
