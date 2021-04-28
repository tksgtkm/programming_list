#include <iostream>
#include <cstring>
#include "pearson.h"

using namespace std;

Pearson::Pearson() {
  last_name[0] = 0;
  first_name[0] = 0;
  address[0] = 0;
  city[0] = 0;
  state[0] = 0;
  zipcode[0] = 0;
}

ostream& operator<<(ostream& stream, Pearson& p) {
  stream << "last name '" << p.last_name << "'\n"
         << "first name '" << p.first_name << "'\n"
         << "address '" << p.address << "'\n"
         << "city '" << p.city << "'\n"
         << "state '" << p.state << "'\n"
         << "zip code '" << p.zipcode << "'\n"
         << flush;
  return stream;
}

istream& operator>>(istream& stream, Pearson& p) {
  cout << "Enter last name, or <cr> to end: " << flush;
  stream.getline(p.last_name, 30);
  if (strlen(p.last_name) == 0)
    return stream;
  cout << "Enter first name: " << flush;
  stream.getline(p.first_name, 30);
  cout << "Enter address: " << flush;
  stream.getline(p.address, 30);
  cout << "Enter city: " << flush;
  stream.getline(p.city, 30);
  cout << "Enter state: " << flush;
  stream.getline(p.state, 15);
  cout << "Enter zip code: " << flush;
  stream.getline(p.zipcode, 10);
  return stream;
}
