#include <iostream>
#include <fstream>

using namespace std;

int main() {
  char ch;
  fstream file;
  char filename[20];
  cout << "Enter the name of the file." << flush;
  cin >> filename;
  file.open(filename, ios::in);
  file.unsetf(ios::skipws);
  while (true) {
    file >> ch;
    if (file.fail())
      break;
    cout << ch;
  }
  file.close();
  return 0;
}
