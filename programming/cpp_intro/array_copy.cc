
#include <iostream>

using namespace std;

int main() {
  const int n = 5; // 配列aとbの要素数
  int a[n]; // コピー元配列
  int b[n] = {0}; // コピー先配列(全要素を0で初期化)

  // 配列aの要素に値を読み込む
  for (int i = 0; i < n; i++) {
    cout << "a[" << i << "] : ";
    cin >> a[i];
  }

  // 配列aの全要素を配列bにコピー
  for (int i = 0; i < n; i++) {
    b[i] = a[i];
  }

  // 配列bの全要素の値を表示
  for (int i = 0; i < n; i++) {
    cout << "b[" << i << "] = " << b[i] << '\n';
  }
}
