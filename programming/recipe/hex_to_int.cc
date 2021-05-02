#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

long hex2int(const string& hexstr) {
  char *offset;
  if (hexstr.length() > 2) {
    if (hexstr[0] == '0' && hexstr[1] == 'x') {
      return strtol(hexstr.c_str(), &offset, 0);
    }
  }
  return strtol(hexstr.c_str(), &offset, 16);
}

int main() {
  string str1 = "0x12AB";
  cout << hex2int(str1) << endl;
  string str2 = "12AB";
  cout << hex2int(str2) << endl;
  string str3 = "QAFG";
  cout << hex2int(str3) << endl;
}
