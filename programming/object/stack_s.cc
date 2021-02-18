#include <assert.h>
#include <cstdlib>
#include <iostream>

const int STACK_SIZE = 100;

class Stack {
private:
  int count;
  int data[STACK_SIZE];
public:
  void init();
  void push(const int item);
  int pop();
};

inline void Stack::init() {
  count = 0;
}

inline void Stack::push(const int item) {
  assert((count >= 0) && (count < static_cast<int>(sizeof(data)/sizeof(data[0]))));
  data[count] = item;
  ++count;
}

inline int Stack::pop() {
  --count;
  assert((count >= 0) && (count <static_cast<int>(sizeof(data)/sizeof(data[0]))));
  return (data[count]);
}

int main() {
  Stack a_stack;
  a_stack.init();

  a_stack.push(1);
  a_stack.push(2);
  a_stack.push(3);

  std::cout << "Except a 3 ->" << a_stack.pop() << '\n';
  std::cout << "Except a 2 ->" << a_stack.pop() << '\n';
  std::cout << "Except a 1 ->" << a_stack.pop() << '\n';
  return 0;
}
