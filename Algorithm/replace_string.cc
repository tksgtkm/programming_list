#include <string>
#include <iostream>

using namespace std;

template <class CharT, class Traits, class Allocator>
basic_string<CharT, Traits, Allocator>& replace_substr(
  basic_string<CharT, Traits, Allocator>& s1,
  const basic_string<CharT, Traits, Allocator>& s2,
  const basic_string<CharT, Traits, Allocator>& s3
) {
  
}

int main() {
  string sentence, sentence1, sentence2;
  getline(cin, sentence);
  getline(cin, sentence1);
  getline(cin, sentence2);
  cout << "target_sentence is: " << sentence << "\n";
}
