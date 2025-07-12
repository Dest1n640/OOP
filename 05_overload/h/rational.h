#ifndef RATIONAL_H
#define RATIONAL_H

#include <cmath>
#include <iostream>
using namespace std;

class Rational {
  int simplify(int &number, int &denom);
  int number;
  int denom;

public:
  Rational();
  Rational(int number);
  Rational(int number, int denom);
  Rational &operator+=(const Rational &r);     // Сложение с присваиванием
  Rational operator+(const Rational &r) const; // Сложение
  Rational operator-(const Rational &r) const; // Вычитание
  Rational operator-() const;
  Rational &operator-=(const Rational &r);     // Вычитание с присваиванием
  Rational operator*(const Rational &r) const; // Умножение
  Rational &operator*=(const Rational &r);     // Умножение с присваиванием
  Rational operator/(const Rational &r) const; // Дление
  Rational &operator/=(const Rational &r);     // Деление с присваниванием
  Rational &operator++();                      // Префиксный инкремент
  Rational operator++(int);                    // Постфиксный инкеремент
  Rational &operator--();
  Rational operator--(int);
  bool operator>=(const Rational &r) const;
  bool operator<=(const Rational &r) const;
  bool operator>(const Rational &r) const;
  bool operator<(const Rational &r) const;
  bool operator==(const Rational &r) const; // Опертор сравнения
  bool operator!=(const Rational &r) const; // Оператор неравентсва
  operator int() const;                     // Приведение к int
  operator double() const;                  // Приведение к double
  friend istream &operator>>(istream &in, Rational &r);
  friend ostream &operator<<(ostream &out, const Rational &r);
};
double my_sqrt(int x);
#endif
