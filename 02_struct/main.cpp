#include "Head/geometry.h"
#include <iostream>

int main() {
  Point p1, p2, p3;

  std::cout << "Введите координаты первой точки (x y): ";
  std::cin >> p1.x >> p1.y;

  std::cout << "Введите координаты второй точки (x y): ";
  std::cin >> p2.x >> p2.y;

  std::cout << "Введите координаты третьей точки (x y): ";
  std::cin >> p3.x >> p3.y;

  double area = calcAreaByPoints(p1, p2, p3);
  double perimeter = calcPerimeterByPoints(p1, p2, p3);

  if (area > 0) {
    std::cout << "Площадь треугольника: " << area << std::endl;
    std::cout << "Периметр треугольника: " << perimeter << std::endl;
  } else {
    std::cout
        << "Невозможно вычислить площадь и периметр (некорректный треугольник)"
        << std::endl;
  }

  return 0;
}
