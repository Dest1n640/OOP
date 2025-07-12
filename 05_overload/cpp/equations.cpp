#include "../h/equations.h"
#include "../h/rational.h"
#include <cmath>
#include <iostream>

Rational my_sqrt(int x,
                 double Epsilon = std::numeric_limits<double>::epsilon()) {
  if (x < 0)
    return 0;

  int guess = x;
  while (abs(guess * guess - x) > Epsilon)
    guess = (guess + x / guess) / 2;
  return guess;
}
Rational linear_eq(Rational k, Rational b) { return (-b) / k; }

QuadraticRoots quadr_eq(Rational a, Rational b, Rational c) {
  Rational D_rational;
  D_rational = b * b - Rational(4) * a * c;
  double D = static_cast<double>(D_rational);

  QuadraticRoots roots;
  roots.hasRealRoots = true;

  if (D < 0) {
    std::cout << "D < 0" << std::endl;
    roots.hasRealRoots = false;
    roots.x1 = NAN;
    roots.x2 = NAN;
  } else if (D == 0) {
    roots.x1 = static_cast<double>(((-b) / Rational(2)) * a);
    roots.x2 = roots.x1;
  } else {
    double double_b = static_cast<double>(b);
    double double_a = static_cast<double>(a);

    roots.x1 = ((-double_b) + std::sqrt(D)) / (2.0 * double_a);
    roots.x2 = ((-double_b) - std::sqrt(D)) / (2.0 * double_a);
  }

  return roots;
}
