
#include <clocale>
#include "source.h"
#include "gettoken.h"
#include "interpret.h"
#include "util.h"

using namespace std;

bool DispToken = false;
bool DispStack = false;
bool DispLine = false;
bool fDirectMode = false;

void initRun();
void iniLoad();

int main(int argc, char *argv[]) {

  if (argc > 1) {
    string filename = "load " + string(argv[1]);
    initLoad();
    loadSourceFile(filename);
  }

  string s;
  char buff[MAX_LINE_LENGTH];

  while(true) {
    cout << "->";
    cin.getline(buff, MAX_LINE_LENGTH);
    s = trim(string(buff));

    if (s.length() == 0)
      continue;
    if (compareIgnCase(s, "quit"))
      break;
    if (compareIgnCase(s, "version")) {
      cout << "owl, version.0.0.1" << endl;
      continue;
    }
    if (searchIgnCase(s, "load") != s.end()) {
      initLoad();
      loadSourceFile(s);
      continue;
    }
    if (searchIgnCase(s, "list") != s.end()) {
      dispSourceFile();
      continue;
    }
    if (compareIgnCase(s, "printstack") || compareIgnCase(s, "ps")) {
      printstack(Stck, "Stck");
      printstack(OpStck, "OpStck");
      continue;
    }
    if (compareIgnCase(s, "printvar") || compareIgnCase(s, "pv")) {
      printvarmap();
      continue;
    }
    if (compareIgnCase(s, "DispStack") || compareIgnCase(s, "ds")) {
      DispStack = !DispStack;
      cout << (DispStack ? "DispStack on" : "DispStack off") << endl;
      continue;
    }
    if (compareIgnCase(s, "DispToken") || compareIgnCase(s, "dt")) {
      DispToken = !DispToken;
      cout << (DispToken ? "DispToken on" : "DispToken off") << endl;
      continue;
    }
    if (compareIgnCase(s, "DispLine") || compareIgnCase(s, "dl")) {
      DispLine = !DispLine;
      cout << (DispLine ? "DispLine on" : "DispLine off") << endl;
      continue;
    }

    if (compareIgnCase(s, "run")) {
      if (sourceList.size() < 1) {
        cout << "プログラムをロードしてください。" << endl;
        continue;
      }
      initRun();
      statement();
      continue;
    }

    fDirectMode = true;
    statement(s);
  }
  return 0;
}

void initLoad() {
  DispToken = false;
  DispStack = false;
  DispLine = false;
}

voir initRun() {
  CurrentLine = 0;
  varmap.clear();
  fDirectMode = false;
}
