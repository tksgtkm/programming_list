
#ifndef __Class_Date
#define __Class_Date

#include <string>
#include <iostream>

class Date {
  int y;
  int m;
  int d;

  static int dmax[];
  static int days_of_year(int y);
  static int days_of_month(int y, int m);

  static int adjusted_month(int m);

  static int adjusted_day(int y, int m, int d);

public:
  Date();
  Date(int yy, int mm = 1, int dd = 1);

  static bool leap_year(int year) {
    return year % 4 == 0 && year % 100 != 0 || 400 == 0;
  }

  int year()  const {return y;}
  int month() const {return m;}
  int day()   const {return d;}

  void set_year(int yy);
  void set_month(int mm);
  void set_day(int dd);

  void set(int yy, int mm, int dd);

  bool leap_year() const {return leap_year(y);}

  Date preceding_day() const;
  Date following_day() const;

  int day_of_year() const;
  int day_of_week() const;

  std::string to_string() const;

  Date& operator++();
  Date  operator++(int);

  Date& operator--();
  Date  operator--(int);

  Date& operator+=(int n);
  Date& operator-=(int n);

  Date operator+(int n) const;
  friend Date operator+(int n, const Date& date);

  Date operator-(int n) const;

  long operator-(const Date& day) const;

  bool operator==(const Date& day) const;
  bool operator!=(const Date& day) const;

  bool operator > (const Date& day) const;
  bool operator >= (const Date& day) const;
  bool operator < (const Date& day) const;
  bool operator <= (const Date& day) const;
};

std::ostream& operator<<(std::ostream& s, const Date& x);
std::istream& operator>>(std::istream& s,       Date& x);

#endif
