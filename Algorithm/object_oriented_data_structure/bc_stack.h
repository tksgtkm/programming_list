#ifndef __BC_Stack_H
#define __BC_Stack_H

typedef int BOOLEAN;
typedef char DATA_TYPE;

class Stack {
public:
  virtual BOOLEAN   is_empty() = 0;
  virtual void      build_stack(DATA_TYPE *A) = 0;
  virtual void      push(DATA_TYPE new_delta) = 0;
  virtual DATA_TYPE pop(void) = 0;
  virtual DATA_TYPE get_top_of_stack(void) = 0;
  virtual void      print_stack(void) = 0;
};

#endif
