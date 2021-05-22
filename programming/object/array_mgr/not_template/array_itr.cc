#include "array_itr.h"

namespace marsdb {
  ArrayItr::ArrayItr(ArrayMgr* in_array, int i_elements) {
    the_array = in_array;
    numb_elements = i_elements;
    current_index = 0;
  }

  bool ArrayItr::GetNext(int& value) {
    bool result = false;
    if (current_index < numb_elements) {
      the_array->GetElement(current_index, value);
      result = true;
      current_index++;
    }
    return result;
  }
}
