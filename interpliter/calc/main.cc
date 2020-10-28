
#include <iostream>
#include <stack>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include "util.h"

using namespace std;

bool comp_char_ign_case(char c1, char c2);
bool compare_ign_case(string s1, string s2);
int get_top_2_elm(stack<double> &stck, double *a, double *b);
void printstack(stack<double>);
int is_number_string(string s);
void syntax_error();

int main(int argc, char *argv[]) {
  stack<double> stck;
  double a, b;
  string s;

  // ユーザーの入力を受け取って出力するループ
  while (true) {
    cout << "->"; // プロンプトを出力する
    cin >> s; // ユーザーのキー入力を受け取る

    if (s.length() == 0)
      continue;

    // 文字列がquitであればループを抜ける
    if (compare_ign_case(s, "quit"))
      break;

    // printstackであれば現在のスタックの内容を出力する
    if (compare_ign_case(s, "printstack")) {
      printstack(stck);
      continue;
    }

    char c = s[0]; // 文字列の先頭の文字を取り出す

    if (s.size() == 1 && !isdigit((int)c)) { // 演算子とみなす
      switch(c) {
        case '+': // 加算
          if (get_top_2_elm(stck, &a, &b))
            break;
          cout << a + b << endl;
          stck.push(a + b);
          break;
        case '-': // 減算
          if (get_top_2_elm(stck, &a, &b))
            break;
          cout << b - a << endl;
          stck.push(b - a);
          break;
        case '*': // 乗算
          if (get_top_2_elm(stck, &a, &b))
            break;
          cout << a * b << endl;
          stck.push(a * b);
          break;
        case '/': // 除算
          if (get_top_2_elm(stck, &a, &b))
            break;
          cout << b / a << endl;
          stck.push(b / a);
          break;
        default:
          // いずれの演算子でもなければエラーを返す
          syntax_error();
          break;
      }
      continue;
    }

    // 値が入力されたか調べる
    if (is_number_string(s)) {
      // 値をスタックにプッシュ
      stck.push(atof(s.c_str()));
    } else {
      syntax_error();
    }
  }

  return 0;
}

bool comp_char_ign_case(char c1, char c2) {
  return (tolower(c1) == tolower(c2));
}

bool compare_ign_case(string s1, string s2) {
  string ss1 = s1;
  string ss2 = s2;
  if (s1.length() > s2.length())
    swap(s1, s2);
  return equal(s1.begin(), s1.end(), s2.begin(), comp_char_ign_case);
}

// スタックから最上部の2個の要素を取り出す
int get_top_2_elm(stack<double> &stck, double *a, double *b) {
  if (stck.size() < 2) {
    cout << "オペランドが足りません" << endl;
    return -1;
  }
  *a = stck.top();
  stck.pop();
  *b = stck.top();
  stck.pop();
  return 0;
}

// スタックの内容を全て出力させる
void printstack(stack<double> stck) {
  stack<double> tmpstck; // スタックに出力されるデータを一時的に保存するための変数

  tmpstck = stck;
  cout << "--- stack top ---" <<  endl;
  int n = (int)tmpstck.size();
  for (int i=0; i<n; i++) {
    cout << tmpstck.top() << endl;
    tmpstck.pop();
  }
  cout << "--- stack bottom ---" << endl;
}

// 文字列の前後の空白を除く
string trim(string s) {
  string ss = "";
  int len = s.length();
  for (int i=0; i<len; i++) {
    int c = s[i];
    if (c == 0x20 || c == 0x8) {
      continue;
    } else {
      ss += c;
    }
  }
  return ss;
}

// 引数文字列ssが数値を表す文字列なら1を返し、
// そうでないならエラー0を返す
int is_number_string(string ss) {
  string s = trim(ss);
  // 最初の文字は-か.か数字
  char c = s[0]; // 文字列の先頭の文字を返す
  // 先頭が.でも-でも数字でもなければエラー
  if (c != '.' && c != '-' && !isdigit(c)) {
    return 0;
  }
  // 長さが1で数字文字でなければエラー
  if (s.length() == 1 && !isdigit(c)) {
    return 0;
  }
  // 長さが1以上で2文字以降に数字文字か.以外があればエラー
  int len = s.length();
  int n_period = 0;
  if (c == '.')
    n_period = 1;
  if (len > 1) {
    for (int i=1; i<len; i++) {
      char c = s[i];
      if (c != '.' && !isdigit(c))
        return 0;
      if (c == '.')
        if (++n_period > 1) // .が2個以上ならエラー
          return 0;
      }
      return 1;
  }
  return 1;
}

void syntax_error() {
  cerr << "syntax Error" << endl;
}
