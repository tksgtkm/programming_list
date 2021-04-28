#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "bc_stack.h"
#include "lnk_stack.h"

using namespace std;

void Lnk_Stack::clear_stack(void) {
  while(!is_empty())
    pop();
}

Lnk_Stack::Lnk_Stack() {
  init_stack();
}

Lnk_Stack::~Lnk_Stack() {
  clear_stack();
}

void Lnk_Stack::push(DATA_TYPE new_data) {
  STACK_PTR new_ptr = new STACK_ELEMENT;
  new_ptr->data = new_data;
  new_ptr->next = top_of_stack;
  top_of_stack = new_ptr;
}

DATA_TYPE Lnk_Stack::pop(void) {
  STACK_PTR tmp_ptr = top_of_stack;
  if (is_empty()) {
    cout << "pop: Stack Underflow\n";
    exit(1);
  } else {
    DATA_TYPE popped_data = top_of_stack->data;
    top_of_stack = top_of_stack->next;
    delete tmp_ptr;
    return popped_data;
  }
}

void Lnk_Stack::build_stack(DATA_TYPE str[]) {
  if (str[0] == '\0') {
    cout << "build_stack: Empty string.\n";
  } else {
    for(int j=0; str[j] != '\0'; ++j)
      cout << str[j] << endl;
  }
}

DATA_TYPE Lnk_Stack::get_top_of_stack(void) {
  if (!is_empty())
    return top_of_stack->data;
  else
    cout << "get_top_of_stack: No Element in Stack\n";
}

void Lnk_Stack::print_stack(void) {
  if (!is_empty()) {
    for (STACK_PTR tmp_ptr=top_of_stack; tmp_ptr!=NULL; tmp_ptr=tmp_ptr->next) {
      cout << tmp_ptr->data << "\n" << endl;
      cout << "top of this stackobject\n";
    }
  } else {
    cout << "No Element in Stack.\n";
  }
}
