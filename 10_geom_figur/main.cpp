#include "./h/geom_fig.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <vector>

void read_points_and_calculate(const std::string &filename,
                               std::vector<Figure *> &figures);

Figure::~Figure() = default;

int main() {
  int circle_count = 0, ellipse_count = 0, triangle_count = 0;
  int rectangle_count = 0, polygon_count = 0;

  double circle_area_sum = 0, ellipse_area_sum = 0, triangle_area_sum = 0;
  double rectangle_area_sum = 0, polygon_area_sum = 0;

  double circle_perimeter_sum = 0, ellipse_perimeter_sum = 0,
         triangle_perimeter_sum = 0;
  double rectangle_perimeter_sum = 0, polygon_perimeter_sum = 0;

  std::vector<Figure *> figures;

  figures.push_back(new Circle(Points(0, 0), 10));
  figures.push_back(new Circle(Points(5, 5), 7));
  figures.push_back(new Circle(Points(-3, 4), 12));

  figures.push_back(new Elips(Points(1, 1), 15, 5));
  figures.push_back(new Elips(Points(2, -2), 8, 3));
  figures.push_back(new Elips(Points(0, 5), 10, 4));

  figures.push_back(new Triangle({Points(0, 0), Points(0, 3), Points(4, 0)}));
  figures.push_back(new Triangle({Points(1, 1), Points(4, 5), Points(7, 2)}));
  figures.push_back(new Triangle({Points(-2, -2), Points(0, 3), Points(5, 0)}));

  figures.push_back(new Rectangle(Points(0, 0), Points(5, 0)));
  figures.push_back(new Rectangle(Points(6, 7), Points(6, 2)));
  figures.push_back(new Rectangle(Points(-5, -5), Points(0, -5)));

  read_points_and_calculate("granitsy-uchastka2.txt", figures);

  for (size_t i = 0; i < figures.size(); ++i) {
    figures[i]->name();
    double area = figures[i]->calc_area();
    double perimeter = figures[i]->calc_perimeter();

    std::cout << "Площадь: " << area << ", Периметр: " << perimeter << "\n";

    if (dynamic_cast<Circle *>(figures[i])) {
      circle_count++;
      circle_area_sum += area;
      circle_perimeter_sum += perimeter;
    } else if (dynamic_cast<Elips *>(figures[i])) {
      ellipse_count++;
      ellipse_area_sum += area;
      ellipse_perimeter_sum += perimeter;
    } else if (dynamic_cast<Triangle *>(figures[i])) {
      triangle_count++;
      triangle_area_sum += area;
      triangle_perimeter_sum += perimeter;
    } else if (dynamic_cast<Rectangle *>(figures[i])) {
      rectangle_count++;
      rectangle_area_sum += area;
      rectangle_perimeter_sum += perimeter;
    } else if (dynamic_cast<Polygon *>(figures[i])) {
      polygon_count++;
      polygon_area_sum += area;
      polygon_perimeter_sum += perimeter;
    }
  }

  for (Figure *fig : figures) {
    delete fig;
  }

  return 0;
}

void read_points_and_calculate(const std::string &filename,
                               std::vector<Figure *> &figures) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Ошибка открытия файла: " << filename << std::endl;
    return;
  }

  std::vector<Points> points;
  int x, y;
  std::string line;

  while (std::getline(file, line)) {
    std::istringstream iss(line);
    if (iss >> x >> y) {
      points.emplace_back(x, y);
    }
  }

  if (points.size() < 3) {
    std::cerr << "Недостаточно точек для построения многоугольника."
              << std::endl;
    return;
  }

  try {
    Polygon *polygon = new Polygon(points);
    figures.push_back(polygon);
    std::cout << "Многоугольник успешно добавлен из файла!" << std::endl;
  } catch (const Figure_Exception &e) {
    std::cerr << "Ошибка создания многоугольника." << std::endl;
  }
}
