#ifndef __PEARSON_H
#define __PEARSON_H

class Pearson {
public:
  char last_name[11];
  char first_name[11];
  char address[16];
  char city[16];
  char state[3];
  char zipcode[10];
  Pearson();
};

std::ostream& operator<<(std::ostream& stream, Pearson& p);
std::istream& operator>>(std::istream& stream, Pearson& p);

#endif
