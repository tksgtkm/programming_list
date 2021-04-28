#ifndef __Lnk_Stack_H
#define __Lnk_Stack_H

#include "bc_stack.h"

class Lnk_Stack : public Stack {
private:
  typedef struct STACK_ELEMENT {
    DATA_TYPE data;
    STACK_ELEMENT *next;
  } *STACK_PTR;
  STACK_ELEMENT *top_of_stack;
  void init_stack() {top_of_stack = NULL;}
  void clear_stack(void);
public:
  Lnk_Stack();
  ~Lnk_Stack();
  BOOLEAN is_empty() {return top_of_stack == NULL;}
  void build_stack(DATA_TYPE *str);
  void push(DATA_TYPE new_data);
  DATA_TYPE pop(void);
  DATA_TYPE get_top_of_stack(void);
  void print_stack(void);
};

#endif
