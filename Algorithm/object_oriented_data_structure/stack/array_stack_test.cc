#include <iostream>

#include "bc_stack.h"
#include "array_stack.h"

using namespace std;

int main() {
  Array_Stack array_stk_obj(8);
  char s[] = "SAUREN";
  array_stk_obj.build_stack(s);
  array_stk_obj.print_stack();
  // delete [] s;
  return 0;
}
