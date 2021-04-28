#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include "pearson.h"

using namespace std;

int main() {
  char filename[20];
  Pearson p;
  cout << "Enter the file name: " << flush;
  cin.getline(filename, 19);
  ofstream stream(filename, ios::out);
  if (stream.fail()) {
    cout << "File open failed!" << endl;
    return 0;
  }
  while(true) {
    cin >> p;
    if (strlen(p.last_name) == 0)
      break;
    stream << p;
  }
}
