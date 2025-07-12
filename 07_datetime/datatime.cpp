#include "datatime.h"
#include <iostream>

bool Datetime::isValidDate(int y, int m, int d) const {
  if (y < 1 || m < 1 || m > 12 || d < 1) {
    return false;
  }
  return d <= daysInMonth(y, m);
}
bool Datetime::isLeapYear(int y) const {
  return y % 4 == 0 && y % 100 != 0 || (y % 400 == 0);
}
int Datetime::daysInMonth(int y, int m) const {
  if (m == 2) {
    return isLeapYear(y) ? 29 : 28;
  } else if (m == 4 || m == 6 || m == 9 || m == 11) {
    return 30;
  } else {
    return 31;
  }
}
int Datetime::dayOfWeek(int y, int m, int d) const {
  if (m < 3) {
    m += 12;
    y--;
  }
  int c = y / 100;
  y %= 100;
  int w = (d + (13 * (m + 1)) / 5 + y + y / 4 + c / 4 - 2 * c) % 7;
  return (w + 7) % 7;
}
Datetime::Datetime(int y, int m, int d, int h, int min, int s)
    : year(y), month(m), day(d), hour(h), minute(min), second(s) {
  if (!isValidDate(y, m, d) || h < 0 || h > 23 || min < 0 || min > 59 ||
      s < 0 || s > 59) {
    std::cout << "Input data is incorrect" << std::endl;
    year = 2000;
    month = 1;
    day = 1;
    hour = 0;
    minute = 0;
    second = 0;
  }
}

long long Datetime::gregorianToJulianDayNumber() const {
  int a = (14 - month) / 12;
  int y = year + 4800 - a;
  int m = month + 12 * a - 3;
  return day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
}

void Datetime::fromJulianDayNumber(long long jdn, int &y, int &m,
                                   int &d) const { // С интернета
  long long l = jdn + 68569;
  long long n = (4 * l) / 146097;
  l = l - (146097 * n + 3) / 4;
  long long i = (4000 * (l + 1)) / 1461001;
  l = l - (1461 * i) / 4 + 31;
  long long j = (80 * l) / 2447;
  d = l - (2447 * j) / 80;
  l = j / 11;
  m = j + 2 - 12 * l;
  y = 100 * (n - 49) + i + l;
}

std::istream &operator>>(std::istream &is, Datetime &dt) {
  int y, m, d, h, min, s;

  std::cout << "Input the date (y m d): ";
  if (!(is >> y >> m >> d)) {
    std::cout << "Invalid date input. Setting to default date." << std::endl;
    dt.year = 2000;
    dt.month = 1;
    dt.day = 1;
    dt.hour = 0;
    dt.minute = 0;
    dt.second = 0;
    return is;
  }

  std::cout << "Input the time (h m s, default meaning 0): ";
  if (!(is >> h >> min >> s)) {
    std::cout << "Invalid time input.  Setting time to 00:00:00." << std::endl;
    h = 0;
    min = 0;
    s = 0;
  }

  if (!dt.isValidDate(y, m, d) || h < 0 || h > 23 || min < 0 || min > 59 ||
      s < 0 || s > 59) {
    std::cout
        << "Invalid date or time values. Setting to default date and time."
        << std::endl;
    dt.year = 2000;
    dt.month = 1;
    dt.day = 1;
    dt.hour = 0;
    dt.minute = 0;
    dt.second = 0;
  } else {
    dt.year = y;
    dt.month = m;
    dt.day = d;
    dt.hour = h;
    dt.minute = min;
    dt.second = s;
  }
  return is;
}

std::ostream &operator<<(std::ostream &os, const Datetime &dt) {
  os << (dt.day < 10 ? "0" : "") << dt.day << ".";
  os << (dt.month < 10 ? "0" : "") << dt.month << ".";
  os << dt.year;

  if (dt.hour != 0 || dt.minute != 0 || dt.second != 0) {
    os << " ";
    os << (dt.hour < 10 ? "0" : "") << dt.hour << ":";
    os << (dt.minute < 10 ? "0" : "") << dt.minute << ":";
    os << (dt.second < 10 ? "0" : "") << dt.second;
  }
  return os;
}

Datetime::Datetime(const char *arr) {
  if (std::sscanf(arr, "%d-%d-%d", &year, &month, &day) != 3) {
    std::cout << "Invalid date format. Expected YYYY-MM-DD." << std::endl;
    year = month = day = 0;
    return;
  }
  hour = minute = second = 0;
  if (!isValidDate(year, month, day)) {
    std::cout << "Invalid date." << std::endl;
    year = month = day = 0;
  }
}

// operators

Datetime Datetime::operator+(const int d) const {
  Datetime res = *this;
  res += d;
  return res;
}
Datetime Datetime::operator-(const int days) const {
  Datetime res = *this;
  res -= days;
  return res;
}

Datetime &Datetime::operator+=(int days) {
  long long current_jdn = gregorianToJulianDayNumber();
  long long new_jdn = current_jdn + days;
  fromJulianDayNumber(new_jdn, year, month, day);
  return *this;
}

Datetime &Datetime::operator-=(int days) {
  long long current_jdn = gregorianToJulianDayNumber();
  long long new_jdn = current_jdn - days;
  fromJulianDayNumber(new_jdn, year, month, day);
  return *this;
}
