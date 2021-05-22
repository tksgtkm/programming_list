#ifndef __Array_ITR_H
#define __Array_ITR_H

#include "array_mng.h"

namespace marsdb {
  class ArrayItr {
  private:
    ArrayMgr *the_array;
    int numb_elements;
    int current_index;
  public:
    ArrayItr (ArrayMgr*, int);
    bool GetNext(int&);
  };
}

#endif
