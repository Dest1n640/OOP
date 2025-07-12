#include "./template/template.h"

int main() {
  try {
    Circle<double> circle({0.0, 0.0}, 5.0);
    circle.name();
    std::cout << "Area: " << circle.calc_area() << std::endl;
    std::cout << "Perimeter: " << circle.calc_perimeter() << std::endl;

    Elips<double> elips({0.0, 0.0}, 8.0, 4.0);
    elips.name();
    std::cout << "Area: " << elips.calc_area() << std::endl;
    std::cout << "Perimeter: " << elips.calc_perimeter() << std::endl;

    Triangle<double> triangle({0.0, 0.0}, {3.0, 0.0}, {0.0, 4.0});
    triangle.name();
    std::cout << "Area: " << triangle.calc_area() << std::endl;
    std::cout << "Perimeter: " << triangle.calc_perimeter() << std::endl;

    Rectangle<double> rect({1.0, 4.0}, {5.0, 1.0});
    rect.name();
    std::cout << "Area: " << rect.calc_area() << std::endl;
    std::cout << "Perimeter: " << rect.calc_perimeter() << std::endl;

    Polygon<double> polygon({{0.0, 0.0}, {3.0, 4.0}, {6.0, 1.5}});
    polygon.name();
    std::cout << "Area: " << polygon.calc_area() << std::endl;
    std::cout << "Perimeter: " << polygon.calc_perimeter() << std::endl;

    Polygon<double> invalid_polygon(std::vector<Points<double>>{{1.5, 2.5}});
  } catch (const PolygonException &) {
    std::cerr << "[Error] Polygon must have at least three vertices!"
              << std::endl;
  }

  return 0;
}
