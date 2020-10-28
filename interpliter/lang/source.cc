
#include "source.h"
#include "interpret.h"
#include "util.h"

using namespace std;

vector < string > SourceList;

int CurrentLine;

int loadSourceFile(string, cmdline) {
  char buff[MAX_LINE_LENGTH];
  strcpy(buff, cmdline.c_str());
  char seps[12] = " ,\t\n";
  char *token = strtok(buff, seps);

  if (token == NULL)
    return dispError();

  token = strtok(NULL, seps);

  if (token == NULL)
    return dispError(NoFileName);

  char filename[MAX_LINE_LENGTH];
  strcpy(filename, token);
  if (strstr(filename, ".owl") == NULL)
    strcat(filename, ".owl");

  ifstream fin(filename, ios::in);
  if (!fin)
    return dispError(FileNotOpen, filename);
  SourceList.clear();
  int lines = 0;
  while (!fin.eof()) {
    fin.getline(buff, MAX_LINE_LENGTH);
    removeLastCRLF(buff);
    string s = string(buff);
    if (s.length() > 0) {
      sourceList.push_back(s);
      lines += 1;
    }
  }
  fin.close();

  cout << filename << "を読み込みました。(" << lines << "行)" << endl;
  return 0;
}

void dispSourceFile() {
  vector<string>::iterator itr;
  int linenumber = 0;
  for (itr=SourceList.begin(); itr != SourceList.end(); ++itr) {
    cout << setw(3) << ++linenumber << ":";
    cout << *itr << " " << endl;
  }
}
