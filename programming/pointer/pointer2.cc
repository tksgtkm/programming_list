
#include <iostream>

using namespace std;

int main() {
  int x = 123;
  int y = 567;
  int sw;

  cout << "x = " << x << '\n';
  cout << "y = " << y << '\n';

  cout << "値を変更する変数[0...x / 1...y] : ";
  cin >> sw;

  int* ptr;
  if (sw == 0) {
    ptr  =&x;
  } else {
    ptr = &y;
  }

  *ptr = 999;

  cout << "x = " << x << '\n';
  cout << "y = " << y << '\n';
}
