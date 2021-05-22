#ifndef __Array_Ctrl_H
#define __Array_Ctrl_H

#include "array_mng.h"

constexpr int MAX_ELEMENTS = 10;
constexpr int ADD = 1;
constexpr int DELETE = 2;
constexpr int RETRIEVE = 3;
constexpr int FIND = 4;
constexpr int LIST = 5;
constexpr int SIZE = 6;
constexpr int EXIT = 9;

namespace marsdb {
  class ArrayCtrl {
  private:
    ArrayMgr *initial_array;
    int menu();
    void add();
    void remove();
    void retrieve();
    void find();
    void list();
    void size();
  public:
    ArrayCtrl();
    void run();
  };
}

#endif
