#ifndef DATATIME_H
#define DATATIME_H

#include <iostream>

class Datetime {
  int year, month, day, hour, minute, second;  // Все нужные переменные
  bool isValidDate(int y, int m, int d) const; // Проверка данных
  bool isLeapYear(int y) const;                // Проверка на високосный код
  int daysInMonth(int y, int m) const;      // Проверка количества дней в месяце
  int dayOfWeek(int y, int m, int d) const; // Кол дня недели

public:
  Datetime(int y, int m, int d, int h = 0, int min = 0,
           int s = 0);                          // конструктор
  Datetime();                                   // еще один
  Datetime(const char *arr);                    // Нужен еще один для сктроки
  long long gregorianToJulianDayNumber() const; // Перевод в Юлианский калиндарь
  void fromJulianDayNumber(long long jdn, int &y, int &m,
                           int &d) const; // Перевод в григорянский календарь
  Datetime operator+(const int d) const;  // пока не работает, дома реализую
  Datetime operator-(const int days) const;
  Datetime &operator+=(int days);
  Datetime &operator-=(int days);
  friend std::istream &operator>>(std::istream &is, Datetime &dt);
  friend std::ostream &operator<<(std::ostream &os, const Datetime &dt);
};

#endif
