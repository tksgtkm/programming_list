#include <stdio.h>

int global_var;
int global_initialized_var = 5;

void function() {
  int stack_var;
  printf("exist address: 0x%08x stack_var() in function().\n", &stack_var);
}

int main() {
  int stack_var;
  static int static_initialized_var = 5;
  static int static_var;
  int *heap_var_ptr;

  heap_var_ptr = (int *)malloc(4);

  printf("global_initialized_varはアドレス0x%08xにあります。\n", &global_initialized_var);
  printf("static_initialized_varはアドレス0x%08xにあります。\n\n", &static_initialized_var);

  printf("static_varはアドレス0x%08xにあります。\n", &static_var);
  printf("global_varはアドレス0x%08xにあります。\n\n", &global_var);

  printf("heap_var_ptrはアドレス0x%08xを指しています。\n\n", heap_var_ptr);

  printf("stack_varはアドレス0x%08xにあります。\n", &stack_var); 
  function();
}
