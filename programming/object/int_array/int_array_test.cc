#include <iostream>
#include "int_array.h"

using namespace std;

int main() {
  int n;
  cout << "please input number of element: ";
  cin >> n;

  IntArray x(n);

  for(int i=0; i<x.size(); i++)
    x[i] = i;

  for(int i=0; i<x.size(); i++)
    cout << "x[" << i << "] = " << x[i] << '\n';
}
