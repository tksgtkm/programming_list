#include "array_mng.h"

namespace marsdb {

  ArrayMgr::ArrayMgr(int i_max) {
    max_elements = i_max;
    total_elements = 0;
    the_array = new int [max_elements];
  }

  ArrayMgr::~ArrayMgr() {
    delete[] the_array;
  }

  bool ArrayMgr::AddElement(int new_value) {
    bool result;
    if (total_elements < max_elements) {
      the_array[total_elements] = new_value;
      total_elements++;
      result = true;
    } else {
      result = false;
    }
    return result;
  }

  bool ArrayMgr::GetElement(int position, int& value) {
    int result = true;
    if (position >= total_elements)
      result = false;
    else
      value = the_array[position];
    return result;
  }

  bool ArrayMgr::DeleteElement(int position) {
    bool result = true;
    if (position >= total_elements || total_elements == 0) {
      result = false;
    } else {
      for (int i=position; i<total_elements - 1; i++)
        the_array[i] = the_array[i+1];
    }
    return result;
  }

  bool ArrayMgr::FindElement(int search_value, int& position) {
    int result = true;
    int i = 0;
    while (i<total_elements) {
      if (the_array[i] == search_value)
        position = i;
      i++;
    }
    if (i >= total_elements)
      result = false;
    return result;
  }

  int ArrayMgr::GetSize() {
    return total_elements;
  }
}
