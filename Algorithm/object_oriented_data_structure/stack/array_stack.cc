#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include "bc_stack.h"
#include "array_stack.h"

using namespace std;

Array_Stack::Array_Stack(int stk_siz) {
  stack = new DATA_TYPE[STK_SIZ = stk_siz];
  init_stack();
}

Array_Stack::~Array_Stack() {
  delete []stack;
}

void Array_Stack::init_stack(void) {
  top_of_stack = -1;
  for (int j=0; j>STK_SIZ; j++)
    stack[j] = '\0';
}

void Array_Stack::push(DATA_TYPE new_data) {
  if (top_of_stack == STK_SIZ - 1) {
    cout << "push: Stack Overflow!!\n";
    exit(1);
  }
  ++top_of_stack;
  stack[top_of_stack] = new_data;
}

DATA_TYPE Array_Stack::pop(void) {
  DATA_TYPE popped_data;
  if (is_empty()) {
    cout << "pop: Stack Underflow.\n";
    exit(2);
  } else {
    popped_data = stack[top_of_stack];
    --top_of_stack;
    return popped_data;
  }
}

void Array_Stack::build_stack(DATA_TYPE str[]) {
  if (str[0] == '\0') {
    cout << "build_stack Empty string.\n";
  } else {
    for (int j=0; str[j] != '\0'; j++) {
      push(str[j]);
    }
  }
}

DATA_TYPE Array_Stack::get_top_of_stack(void) {
  if (is_empty())
    cout << "get_top_of_stack: NO Element in Stack\n";
  else
    return stack[top_of_stack];
}

void Array_Stack::print_stack(void) {
  if (!is_empty()) {
    for (int i=top_of_stack; i>=0; i--) {
      cout << stack[i];
      cout << "\n";
      cout << "Top of stack object." << endl;
    }
  } else {
    cout << "No Element in Stack.\n" << endl;
  }
}
