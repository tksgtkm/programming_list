
#include "token.h"
#include "prot.h"

int main(int argc, char *argv[]) {
  if (argc == 1) {
    cout << "usage: filename\n";
    exit(1);
  }
  convert_to_internalCode(argv[1]);
  syntaxChk();
  execute();
  return 0;
}
