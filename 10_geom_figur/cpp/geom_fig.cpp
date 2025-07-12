#include "../h/geom_fig.h"
#include <cmath>
#include <csignal>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

Points::Points(int x, int y) : x(x), y(y) {}

Points Points::operator+(const Points &other) const {
  return Points(this->x + other.x, this->y + other.y);
}
Points Points::operator/(const Points &other) const {
  return Points(this->x / other.x, this->y / other.y);
}
Points Points::operator-(const Points &other) const {
  return Points(this->x - other.x, this->y - other.y);
}
Points Points::operator*(const Points &other) const {
  return Points(this->x * other.x, this->y * other.y);
}

Circle::Circle(Points center, int radius) : radius(radius), center(center) {}

double Circle::calc_area() { return M_PI * (radius * radius); }

double Circle::calc_perimeter() { return 2 * M_PI * radius; }

void Circle::name() { std::cout << "Circle" << std::endl; }

Elips::Elips(Points center, int a, int b)
    : center(center), radius_a(a), radius_b(b) {}

double Elips::calc_area() { return M_PI * radius_a * radius_b; }

double Elips::calc_perimeter() {
  double h = ((radius_a - radius_b) * (radius_a - radius_b)) /
             ((radius_a + radius_b) * (radius_a + radius_b));
  return M_PI * (radius_a + radius_b) * (1 + (3 * h) / (10 + sqrt(4 - 3 * h)));
}
void Elips::name() { std::cout << "Elips" << std::endl; }

Triangle::Triangle(Points a, Points b, Points c) : a(a), b(b), c(c) {}

double Triangle::calc_area() {
  double ab = sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
  double bc = sqrt((c.x - b.x) * (c.x - b.x) + (c.y - b.y) * (c.y - b.y));
  double ca = sqrt((a.x - c.x) * (a.x - c.x) + (a.y - c.y) * (a.y - c.y));

  double p = (ab + bc + ca) / 2;

  return sqrt(p * (p - ab) * (p - bc) * (p - ca));
}

double Triangle::calc_perimeter() {
  double ab = sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
  double bc = sqrt((c.x - b.x) * (c.x - b.x) + (c.y - b.y) * (c.y - b.y));
  double ca = sqrt((a.x - c.x) * (a.x - c.x) + (a.y - c.y) * (a.y - c.y));
  return ab + bc + ca;
}

void Triangle::name() { std::cout << "Triangle" << std::endl; }

Rectangle::Rectangle(Points top_left, Points bottom_right)
    : top_left(top_left), bottom_right(bottom_right) {}

double Rectangle::calc_area() {
  int width = std::abs(bottom_right.x - top_left.x);
  int height = std::abs(bottom_right.y - top_left.y);
  return width * height;
}

double Rectangle::calc_perimeter() {
  int width = std::abs(bottom_right.x - top_left.x);
  int height = std::abs(bottom_right.y - top_left.y);
  return 2 * (width + height);
}

void Rectangle::name() { std::cout << "Rectangle" << std::endl; }

Polygon::Polygon(std::vector<Points> &vertices) : vertices(vertices) {
  if (vertices.size() < 3)
    throw Figure_Exception();
}

double Polygon::calc_area() {
  double area = 0.0;
  const int n = vertices.size();

  for (int i = 0; i < n; ++i) {
    int j = (i + 1) % n;
    area += vertices[i].x * vertices[j].y;
    area -= vertices[j].x * vertices[i].y;
  }

  return std::abs(area) / 2.0;
}

double Polygon::calc_perimeter() {
  double perimeter = 0.0;
  for (size_t i = 0; i < vertices.size(); ++i) {
    size_t j = (i + 1) % vertices.size();
    double dx = vertices[j].x - vertices[i].x;
    double dy = vertices[j].y - vertices[i].y;
    perimeter += sqrt(dx * dx + dy * dy);
  }
  return perimeter;
}
void Polygon::name() { std::cout << "Polygon" << std::endl; }
