#ifndef __Array_MNG_H
#define __Array_MNG_H

namespace marsdb {

  class ArrayMgr {
  private:
    int total_elements;
    int max_elements;
    int *the_array;

  public:
    ArrayMgr(int);
    ~ArrayMgr();

    bool AddElement(int);

    bool GetElement(int, int&);

    bool DeleteElement(int);

    bool FindElement(int, int&);

    int GetSize();
  };
}

#endif
