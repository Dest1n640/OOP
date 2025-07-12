#include "../h/rational.h"
#include <cmath>
#include <cstdlib>

using namespace std;

int Rational::simplify(int &number, int &denom) {
  if (denom == 0) {
    denom = 1;
    return 0;
  }
  if (number == 0) {
    denom = 1;
    return 0;
  }

  int a = abs(number);
  int b = abs(denom);
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }

  number /= a;
  denom /= a;

  return a;
}

int number;
int denom;

Rational::Rational() {
  number = 0;
  denom = 1;
}

Rational::Rational(int n, int d) : number(n), denom(d) {
  simplify(number, denom);
  if (denom < 0) {
    number = -number;
    denom = -denom;
  }
}
Rational::Rational(int num) {
  number = num;
  denom = 1;
}
Rational &Rational::operator+=(const Rational &r) {
  number = (number * r.denom + denom * r.number);
  denom *= r.denom;
  simplify(number, denom);
  return *this;
}

Rational Rational::operator+(const Rational &r) const {
  Rational res(*this);
  return res += r;
}

Rational Rational::operator-(const Rational &r) const { return (*this + (-r)); }

Rational Rational::operator-() const {
  Rational r(-number, denom);
  return r;
}

Rational &Rational::operator-=(const Rational &r) { return (*this += (-r)); }

Rational Rational ::operator*(const Rational &r) const {
  Rational res(*this);
  return res *= r;
}
Rational &Rational::operator*=(const Rational &r) {
  number *= r.number;
  denom *= r.denom;
  simplify(number, denom);
  return *this;
}

Rational Rational::operator/(const Rational &r) const {
  return *this * Rational(r.denom, r.number);
}

Rational &Rational ::operator/=(const Rational &r) {
  number *= r.denom;
  denom *= r.number;
  simplify(number, denom);
  return *this;
}

Rational &Rational::operator++() { // Префиксный инкремент
  number += denom;
  return *this;
}

Rational Rational::operator++(int) { // Постфиксный инкремент
  Rational r(*this);
  number += denom;
  return r;
}
Rational &Rational ::operator--() {
  number -= denom;
  return *this;
}

Rational Rational ::operator--(int) {
  Rational r(*this);
  number -= denom;
  return r;
}
bool Rational::operator>=(const Rational &r) const {
  return number * r.denom >= r.number * denom;
}
bool Rational ::operator<=(const Rational &r) const {
  return number * r.denom <= r.number * denom;
}

bool Rational::operator>(const Rational &r) const {
  return number * r.denom > r.number * denom;
}
bool Rational ::operator<(const Rational &r) const { return !(*this > r); }

bool Rational::operator==(const Rational &r) const {
  return (number == r.number) && (denom == r.denom);
}
bool Rational::operator!=(const Rational &r) const { return !(*this == r); }

Rational::operator int() const { return number / denom; }

Rational::operator double() const {
  return static_cast<double>(number) / denom;
}

istream &operator>>(istream &in, Rational &r) {
  in >> r.number >> r.denom;
  r.simplify(r.number, r.denom);
  return in;
}

ostream &operator<<(ostream &out, const Rational &r) {
  out << r.number << "/" << r.denom;
  return out;
}

double my_sqrt(int x) {
  double eplison = 1e-6;
  if (x < 0) {
    cout << "The number < 0" << endl;
    return -1;
  }

  int guess = x;
  while (abs(guess * guess - x) > eplison)
    guess = (guess + x / guess) / 2;
  return guess;
}
