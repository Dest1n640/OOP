#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>

// Структура для представления точки
struct Point {
  double x;
  double y;
};

// Функция для вычисления расстояния между двумя точками
double calcDistance(const Point &p1, const Point &p2);

// Функция для вычисления площади треугольника по координатам точек
double calcAreaByPoints(const Point &p1, const Point &p2, const Point &p3);

// Функция для вычисления периметра треугольника по координатам точек
double calcPerimeterByPoints(const Point &p1, const Point &p2, const Point &p3);

#endif
