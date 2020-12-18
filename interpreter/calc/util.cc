
#include "util.h"

// 大文字小文字を区別しないで文字を比較する関数
bool comp_char_ign_case(char c1, char c2) {
  return (tolower(c1) == tolower(c2));
}

// 大文字小文字を区別しないで文字列を比較する
// 同じであればtrue、違うならfalseを返す
bool compare_ign_case(string s1, string s2) {
  if (s1.length() > s2.length())
    return false;
  return equal(s1.begin(), s1.end(), s2.begin(), comp_char_ign_case);
}
