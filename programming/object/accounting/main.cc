
#include <string>
#include <iostream>
#include "accounting.h"

using namespace std;

void print_Accounting(string title, Accounting* p) {
  cout << title << "\"" << p->name() << "\"" << p->asset() << "yen\n";
}

int main() {
  Accounting nakano("hayato nakano", 1000);
  Accounting yamada("hirohumi yamada", 200);

  nakano.spend(200);
  yamada.earn(100);
  print_Accounting("nakano: ", &nakano);
  print_Accounting("yamada: ", &yamada);
}
