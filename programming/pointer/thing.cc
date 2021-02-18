#include <iostream>

using namespace std;

int main() {
  int thing_var;  // 変数を定義する
  int *thing_ptr; // ポインタを定義する

  thing_var = 2; // thingに値を代入する
  cout << "Thing " << thing_var << '\n';

  thing_ptr = &thing_var; // ポインタにthingをポイントさせる
  *thing_ptr = 3;         // thing_ptrはthing_varをポイントさせるため、
                          // thing_ptrも3に変わる

  cout << "Thing " << thing_var << '\n';
  cout << "Thing " << thing_ptr << '\n'; // thing_ptr自体はthing_varのアドレスの所在地(&thing_var)が格納される
  cout << "Thing " << *thing_ptr << '\n';

  return 0;
}
