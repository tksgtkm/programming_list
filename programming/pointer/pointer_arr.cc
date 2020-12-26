
#include <iostream>

using namespace std;

// 実はここのintは型ではなくポインタになる。
// int a[] -> int* a となっている。
void reverse(int a[], int n) {
  for (int i = 0; i < n/2; i++) {
    int t = a[i];
    a[i] = a[n -i - 1];
    a[n - i - 1] = t;
  }
}

int main() {
  const int n = 5;
  int c[n];
  for (int i = 0; i < n; i++) {
    cout << "c[" << i << "] : ";
    cin >> c[i];
  }
  reverse(c, n);
  cout << "要素の並びを反転しました。\n";
  for (int i = 0; i < n; i++) {
    cout << "c[" << i << "] = " << c[i] << '\n';
  }
}
