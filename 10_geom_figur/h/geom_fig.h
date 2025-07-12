#ifndef GEOM_FIG_H
#define GEOM_FIG_H

#include <csignal>
#include <string>
#include <vector>

class Figure_Exception {};

struct Points {
  int x, y;
  Points(int x = 0, int y = 0);
  Points operator+(const Points &other) const;
  Points operator/(const Points &other) const;
  Points operator-(const Points &other) const;
  Points operator*(const Points &other) const;
};

class Figure {
public:
  virtual double calc_area() = 0;
  virtual double calc_perimeter() = 0;
  virtual void name() = 0;
  virtual ~Figure() = 0;
};

class Circle : public Figure {
  Points center;
  int radius;

public:
  Circle(Points center, int radius);
  double calc_area();
  double calc_perimeter();
  void name();
};

class Elips : public Figure {
  Points center; // Центр
  int radius_a;  // Большая полуось
  int radius_b;  // Маленькая полуось

public:
  Elips(Points center, int a, int b);
  double calc_area();
  double calc_perimeter();
  void name();
};

class Triangle : public Figure {
  Points a, b, c;

public:
  Triangle(Points a, Points b, Points c);
  double calc_area();
  double calc_perimeter();
  void name();
};

class Rectangle : public Figure {
  Points top_left;
  Points bottom_right;

public:
  Rectangle(Points top_left, Points bottom_right);
  Rectangle(const Points &p1, const Points &p2, const Points &p3,
            const Points &p4);
  double calc_area();
  double calc_perimeter();
  void name();
};

class Polygon : public Figure {
  std::vector<Points> vertices;

public:
  Polygon(std::vector<Points> &vertices);
  double calc_area();
  double calc_perimeter();
  void name();
};

#endif
