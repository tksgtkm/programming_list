
#include <iostream>

using namespace std;

void fill_zero(int* p, int n) {
  while (n-- > 0) {
    *p = 0;
    p++;
  }
}

int main() {
  int x[5] = {1, 2, 3, 4, 5};
  int x_size = sizeof(x)/sizeof(x[0]);

  fill_zero(x, x_size);

  cout << "全要素に0を代入しました。\n";
  for (int i = 0; i < x_size; i++)
    cout << "x[" << i << "] = " << x[i] << '\n';
}
