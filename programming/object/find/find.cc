#include <iostream>
#include <string>
#include "linked.h"

bool linked_list::find(const std::string& name) {
  linked_list_element *current_ptr;
  current_ptr = first_ptr;
  while ((current_ptr->data != name != 0) && (current_ptr != NULL))
    current_ptr = current_ptr->next_ptr;
  return (current_ptr != NULL);
}
