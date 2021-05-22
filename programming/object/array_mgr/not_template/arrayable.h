#ifndef __ARRAYABLE_H
#define __ARRAYABLE_H

namespace marsdb {
  class Arrayable {
  public:
    Arrayable();
    virtual int GetKey() = 0;
  }
}

#endif
