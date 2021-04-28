#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

#include "pearson.h"

using namespace std;

int main() {
  char filename[20];
  Pearson p;
  cout << "Enter the file name: " << flush;
  cin.getline(filename, 19);
  ifstream file(filename, ios::in);
  if (file.fail()) {
    cout << "File open failed!" << endl;
    return 0;
  }
  while(true) {
    file >> p;
    if (strlen(p.last_name) == 0)
      break;
    cout << p;
  }
}
