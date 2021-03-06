
#ifndef UTIL_H
#define UTIL_H
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <iomanip>

using namespace std;

#define MAX_LINE_LENGTH 256

enum errorid { UnknownError, NoFileName, FileNotOpen, Dummy };
typedef errorid ErrorID;

// �v���g�^�C�v�錾
bool isParen(char c);

bool compCharIgnCase(char c1, char c2);
bool compareIgnCase(string s1, string s2);
string::iterator searchIgnCase(string &str, const string &substr) ;
string trim(string s);
string trimStart(string s);
string StripStr(string s);      // �������̑O����"������
int isNumberString(string ss);
int syntaxError( string msg = "" );
bool isOparator(char c);
bool isParen(char c);
void removeLastCRLF(char *);

int dispError(ErrorID id=UnknownError, string s="");

#endif
