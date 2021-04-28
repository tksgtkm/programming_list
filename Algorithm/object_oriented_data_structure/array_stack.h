#ifndef __Array_Stack_H
#define __Array_Stack_H

#include "array_stack.h"

class Array_Stack : public Stack {
private:
  void init_stack();
protected:
  DATA_TYPE *stack;
  int STK_SIZ;
  int top_of_stack;
public:
  Array_Stack(int stk_siz);
  ~Array_Stack();

  BOOLEAN is_empty() {return top_of_stack == -1;}
  void push(DATA_TYPE new_data);
  DATA_TYPE pop(void);
  void build_stack(DATA_TYPE *str);
  DATA_TYPE get_top_of_stack(void);
  void print_stack(void);
};

#endif
