#include "../Head/geometry.h"

double calcDistance(const Point &p1, const Point &p2) {
  return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

double calcAreaByPoints(const Point &p1, const Point &p2, const Point &p3) {
  double a = calcDistance(p1, p2);
  double b = calcDistance(p2, p3);
  double c = calcDistance(p3, p1);
  double p = (a + b + c) / 2.0;

  if (p <= a || p <= b || p <= c) {
    return 0.0; // Некорректный треугольник
  }

  return sqrt(p * (p - a) * (p - b) * (p - c));
}

double calcPerimeterByPoints(const Point &p1, const Point &p2,
                             const Point &p3) {
  double a = calcDistance(p1, p2);
  double b = calcDistance(p2, p3);
  double c = calcDistance(p3, p1);

  return a + b + c;
}
