#include "class.h"
#include <cmath>

#define LIST_INITIALIZATION 0

#if LIST_INITIALIZATION
Point::Point(double x, double y) : _x(x), _y(y) {}
Circle::Circle(double x, double y, double radius) : _center(x, y), _radius(radius) {}
#else

Point::Point(double x, double y) {
  _x = x;
  _y = y;
}

Point::Point() {
  _x = 0;
  _y = 0;
}

double Point::getHorizontal() const { return _x; }

double Point::getVertical() const { return _y; }

void Point::setHorizontal(double x) { _x = x; }

void Point::setVertical(double y) { _y = y; }

double Point::distTo(const Point& another) const {
  return sqrt((_x - another.getHorizontal()) * (_x - another.getHorizontal()) +
              (_y - another.getVertical() * _y - another.getVertical()));
}

Circle::Circle(double x, double y, double radius) {
  _center = Point(x, y);
  _radius = radius;
}

Circle::Circle() {
  _center = Point();
  _radius = 1;
}

Point Circle::getCenter() const { return _center; }

double Circle::getRadius() const { return _radius; }

void Circle::setCenter(double x, double y) {
  _center.setHorizontal(x);
  _center.setVertical(y);
}

void Circle::setRadius(double radius) { _radius = radius; }

bool Circle::isOverlap(const Circle& another) const {
  return _center.distTo(another.getCenter()) <= _radius + another.getRadius();
}

#endif
