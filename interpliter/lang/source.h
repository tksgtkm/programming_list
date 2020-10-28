
#ifndef SOURCE_H
#define SOURCE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <iomanip>

using namespace std;

extern vector < string > sourceList;
extern int CurrentLine;

int loadSourceFile(string, cmdline);
coid dispSourceFile();

#endif
