#include "class.h"
#include <cmath>
#include <stdexcept>

#define LIST_INITIALIZATION 0

#if LIST_INITIALIZATION
Point::Point(double x, double y) : _x(x), _y(y) {}
Circle::Circle(double x, double y, double radius) : _center(x, y), _radius(radius) {}
#else

Point::Point(double x, double y) {
  if (!isValidCoordinate(x, y)) {
    throw std::invalid_argument("Invalid coordinates");
  }
  _x = x;
  _y = y;
}

Point::Point() {
  _x = 0;
  _y = 0;
}

bool Point::isValidCoordinate(double x, double y) const {
  // Assuming reasonable bounds for coordinates, e.g., within [-1e6, 1e6]
  return (x >= -1e6 && x <= 1e6) && (y >= -1e6 && y <= 1e6);
}

double Point::getX() const { return _x; }
double Point::getY() const { return _y; }
void Point::setX(double x) { _x = x; }
void Point::setY(double y) { _y = y; }

double Point::distTo(const Point& another) const {
  return sqrt((_x - another.getX()) * (_x - another.getX()) +
              (_y - another.getY()) * (_y - another.getY()));
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
  _center.setX(x);
  _center.setY(y);
}

void Circle::setRadius(double radius) { _radius = radius; }

bool Circle::isOverlap(const Circle& another) const {
  return _center.distTo(another.getCenter()) <= _radius + another.getRadius();
}

#endif
