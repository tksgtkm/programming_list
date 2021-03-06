#include <string>
#include <vector>
#include <functional>
#include <iostream>

using namespace std;

template<typename T>
void split(const basic_string<T>& s, T c, vector<basic_string<T> >& v) {
  typename basic_string<T>::size_type i = 0;
  typename basic_string<T>::size_type j = s.find(c);

  while(j != basic_string<T>::npos) {
    v.push_back(s.substr(i, j-i));
    i = ++j;
    j = s.find(c, j);

    if (j == basic_string<T>::npos) {
      v.push_back(s.substr(i, s.length()));
    }
  }
}

int main() {
  vector<string> v;
  string s = "Account Name|Address 1|Address 2|City";

  split(s, '|', v);

  for (int i = 0; i < v.size( ); ++i) {
     cout << v[i] << '\n';
  }
}
