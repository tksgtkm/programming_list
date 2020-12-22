
#include <iostream>

using namespace std;

int main() {
  int yamane, takada, kawakami, saegusa, tozuka;
  int sum = 0;
  cout << "5人の点数の合計点と平均点を求めます。\n";
  cout << "1番目の点数: "; cin >> yamane; sum += yamane;
  cout << "2番目の点数: "; cin >> takada; sum += takada;
  cout << "3番目の点数: "; cin >> kawakami; sum += kawakami;
  cout << "4番目の点数: "; cin >> saegusa; sum += saegusa;
  cout << "5番目の点数: "; cin >> tozuka; sum += tozuka;

  cout << "合計は" << sum << "点です。\n";
  cout << "平均は" << static_cast<double>(sum) / 5 << "点です。\n";
}
