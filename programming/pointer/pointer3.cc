
#include <iostream>

using namespace std;

void sum_mul(int x, int y, int* sum, int* mul) {
  // sumとmulのアドレスに含まれる値をここで計算する
  *sum = x + y;
  *mul = x * y;
}

int main() {
  int a, b;
  int wa = 0, seki = 0;

  cout << "整数a:"; cin >> a;
  cout << "整数b:"; cin >> b;

  sum_mul(a, b, &wa, &seki);
  cout << "sum is" << wa << "\n";
  cout << "mul is" << seki << "\n";
}
