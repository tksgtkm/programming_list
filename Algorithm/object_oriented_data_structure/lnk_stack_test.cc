#include <iostream>

#include "bc_stack.h"
#include "lnk_stack.h"

int main() {
  Lnk_Stack lnk_stk_obj;
  char s[] = "SAUREN";
  lnk_stk_obj.build_stack(s);
  lnk_stk_obj.print_stack();
}
