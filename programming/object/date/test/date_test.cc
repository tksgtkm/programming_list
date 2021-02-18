#include <iostream>
#include "../date.h"

using namespace std;

void display(const Date& day) {
  string dw[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  cout << "date: " << day << ".\n";
  cout << " day is" << dw[day.day_of_week()] << "day";
  cout << " Days elapsed within the year" << day.day_of_year() << "days";
  cout << " This year is " << (day.leap_year() ? "leap" : "not leap") << "\n";
}

void change(Date& day) {
  while(true) {
    cout << "[1]change year [2]change month [3]change day [4]change date "
         << "[5]advance n days [6]back n days [0]back: ";
    int selected;
    cin >> selected;

    if (selected == 0) return;

    int y, m, d, n;
    if (selected == 1 || selected == 4) {cout << "year: "; cin >> y;}
    if (selected == 2 || selected == 4) {cout << "month: "; cin >> m;}
    if (selected == 3 || selected == 4) {cout << "day: "; cin >> d;}
    if (selected == 5 || selected == 6) {cout << "days: "; cin >> n;}

    switch(selected) {
      case 1: day.set_year(y);  break;
      case 2: day.set_month(m); break;
      case 3: day.set_day(d);   break;
      case 4: day.set(y, m, d); break;
      case 5: day += n;         break;
      case 6: day -= n;         break;
    }
    cout << day << "update.\n";
  }
}

void inc_dec(Date& day) {
  while(true) {
    cout << "[1]++day [2]day++ [3]--day [4]day-- [0]back: ";
    int selected;
    cin >> selected;

    if (selected == 0) return;

    switch(selected) {
      case 1: cout << "++day = " << ++day << '\n'; break;
      case 2: cout << "day++ = " << day++ << '\n'; break;
      case 3: cout << "--day = " << --day << '\n'; break;
      case 4: cout << "day-- = " << day-- << '\n'; break;
    }
    cout << "day  = " << day << '\n';
  }
}

void before_after(Date& day) {
  while(true) {
    cout << "[1]next day [2]before day [3]n days later(day+n) [4]n days later(n+day) ";
    cout << "[5]n days before [0]back: ";
    int selected;
    cin >> selected;

    int n;
    if (selected >= 3 && selected <= 5) {
      cout << "days: "; cin >> n;
    }

    cout << "it's";
    switch(selected) {
      case 1: cout << day.following_day(); break;
      case 2: cout << day.preceding_day(); break;
      case 3: cout << day + n;             break;
      case 4: cout << n + day;             break;
      case 5: cout << day - n;             break;
    }
    cout << ".\n";
  }
}

void compare(const Date& day) {
  int y, m, d;
  cout << "input date day2 for compare.\n";
  cout << "year: "; cin >> y;
  cout << "month: "; cin >> m;
  cout << "day: "; cin >> d;

  Date day2(y, m, d);

  cout << boolalpha;
  cout << "day  = " << day << '\n';
  cout << "day2 = " << day2 << '\n';
  cout << "day  -  day2  = " << (day - day2)  << '\n';
  cout << "day2 -  day   = " << (day2 - day)  << '\n';
  cout << "day  == day2  = " << (day == day2) << '\n';
  cout << "day  != day2  = " << (day != day2) << '\n';
  cout << "day  >  day2  = " << (day > day2)  << '\n';
  cout << "day  >= day2  = " << (day >= day2) << '\n';
  cout << "day  <  day2  = " << (day < day2)  << '\n';
  cout << "day  <= day2  = " << (day <= day2) << '\n';
}

int main() {
  int y, m, d;
  cout << "input date day.\n";
  cout << "year: ";  cin >> y;
  cout << "month: "; cin >> m;
  cout << "day: ";   cin >> d;

  Date day(y, m, d);

  while(true) {
    cout << "[1]info [2]change date [3]inc/dec operator [4]bef/aft date "
         << "[5]compare [0]finish: ";

    int selected;
    cin >> selected;

    if (selected == 0) break;

    switch(selected) {
      case 1: display(day); break;
      case 2: change(day); break;
      case 3: inc_dec(day); break;
      case 4: before_after(day); break;
      case 5: compare(day); break;
    }
  }
}
