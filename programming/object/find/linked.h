#include <string>

class linked_list_element {
public:
  std::string data;
private:
  class linked_list_element *next_ptr;
  friend class linked_list;
};

class linked_list {
private:
  linked_list_element *first_ptr;
public:
  linked_list() {first_ptr = NULL;};
  ~linked_list();
private:
  linked_list(const linked_list&);
public:
  bool find(const std::string& name);
};
