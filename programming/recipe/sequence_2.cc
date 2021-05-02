#include <iostream>
#include <vector>
#include <exception>

using namespace std;

int main() {
  // char carr[] = {'a', 'b', 'c', 'd', 'e'};
  // cout << carr[100000] << '\n';

  vector<char> v;
  v.push_back('a');
  v.push_back('b');
  v.push_back('c');
  v.push_back('d');
  v.push_back('e');

  try {
    cout << v.at(10000) << '\n';
  } catch(out_of_range& e) {
    cerr << e.what() << '\n';
  }
}
