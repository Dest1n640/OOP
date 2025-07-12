#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

template <typename T> struct Points {
  T x, y;
  Points(T x = 0, T y = 0) : x(x), y(y) {}
  Points<T> operator+(const Points<T> &other) const {
    return Points<T>(this->x + other.x, this->y + other.y);
  }
  Points<T> operator/(const Points<T> &other) const {
    return Points<T>(this->x / other.x, this->y / other.y);
  }
  Points<T> operator-(const Points<T> &other) const {
    return Points<T>(this->x - other.x, this->y - other.y);
  }
  Points<T> operator*(const Points<T> &other) const {
    return Points<T>(this->x * other.x, this->y * other.y);
  }
};

template <typename T> class Figure {
public:
  virtual T calc_area() = 0;
  virtual T calc_perimeter() = 0;
  virtual void name() = 0;
  virtual ~Figure() = default;
};

template <typename T> class Circle : public Figure<T> {
  Points<T> center;
  T radius;

public:
  Circle(Points<T> center, T radius) : center(center), radius(radius) {}

  T calc_area() { return static_cast<T>(M_PI) * radius * radius; }

  T calc_perimeter() { return static_cast<T>(2 * M_PI) * radius; }

  void name() { std::cout << "Circle" << std::endl; }
};

template <typename T> class Elips : public Figure<T> {
  Points<T> center;
  T radius_a;
  T radius_b;

public:
  Elips(Points<T> center, T a, T b)
      : center(center), radius_a(a), radius_b(b) {}

  T calc_area() { return static_cast<T>(M_PI) * radius_a * radius_b; }

  T calc_perimeter() {
    T h = ((radius_a - radius_b) * (radius_a - radius_b)) /
          ((radius_a + radius_b) * (radius_a + radius_b));
    return static_cast<T>(M_PI) * (radius_a + radius_b) *
           (1 + (3 * h) / (10 + sqrt(4 - 3 * h)));
  }

  void name() { std::cout << "Elips" << std::endl; }
};

template <typename T> class Triangle : public Figure<T> {
  Points<T> a, b, c;

public:
  Triangle(Points<T> a, Points<T> b, Points<T> c) : a(a), b(b), c(c) {}

  T calc_area() {
    T ab = sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
    T bc = sqrt((c.x - b.x) * (c.x - b.x) + (c.y - b.y) * (c.y - b.y));
    T ca = sqrt((a.x - c.x) * (a.x - c.x) + (a.y - c.y) * (a.y - c.y));
    T p = (ab + bc + ca) / 2;

    return sqrt(p * (p - ab) * (p - bc) * (p - ca));
  }

  T calc_perimeter() {
    T ab = sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
    T bc = sqrt((c.x - b.x) * (c.x - b.x) + (c.y - b.y) * (c.y - b.y));
    T ca = sqrt((a.x - c.x) * (a.x - c.x) + (a.y - c.y) * (a.y - c.y));
    return ab + bc + ca;
  }

  void name() { std::cout << "Triangle" << std::endl; }
};

template <typename T> class Rectangle : public Figure<T> {
  Points<T> top_left, bottom_right;

public:
  Rectangle(Points<T> top_left, Points<T> bottom_right)
      : top_left(top_left), bottom_right(bottom_right) {}

  T calc_area() {
    T width = abs(bottom_right.x - top_left.x);
    T height = abs(bottom_right.y - top_left.y);
    return width * height;
  }

  T calc_perimeter() {
    T width = abs(bottom_right.x - top_left.x);
    T height = abs(bottom_right.y - top_left.y);
    return 2 * (width + height);
  }

  void name() { std::cout << "Rectangle" << std::endl; }
};

class PolygonException {};

template <typename T> class Polygon : public Figure<T> {
  std::vector<Points<T>> vertices;

public:
  Polygon(const std::vector<Points<T>> &vertices) : vertices(vertices) {
    if (vertices.size() < 3)
      throw PolygonException();
  }

  T calc_area() {
    T area = 0.0;
    const size_t n = vertices.size();

    for (size_t i = 0; i < n; ++i) {
      size_t j = (i + 1) % n;
      area += vertices[i].x * vertices[j].y;
      area -= vertices[j].x * vertices[i].y;
    }

    return abs(area / 2.0);
  }

  T calc_perimeter() {
    T perimeter = 0.0;

    for (size_t i = 0; i < vertices.size(); ++i) {
      size_t j = (i + 1) % vertices.size();
      T dx = vertices[j].x - vertices[i].x;
      T dy = vertices[j].y - vertices[i].y;
      perimeter += sqrt(dx * dx + dy * dy);
    }

    return perimeter;
  }

  void name() { std::cout << "Polygon" << std::endl; }
};

#endif
