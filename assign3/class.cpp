#include "class.h"

#define LIST_INITIALIZATION 0

#if LIST_INITIALIZATION
Point(double x, double y) : _x(x), _y(y) {}
Circle(double x, double y, double radius) : _center(x, y), _radius(radius) {}
#else

Point::Point(double x, double y) {
  _x = x; _y = y;
}

Point::Point() {
  _x = 0; _y = 0;
}

double getHorizontal() {
  return _x;
}

double getVertical() {
  return _y;
}

void setHorizontal(double x) {
  _x = x;
}

void setVertical(double y) {
  _y = y;
}

double distTo(const Point& another) const {
  return sqrt((_x - another.getHorizontal()) * (_x - another.getHorizontal()) +
	      (_y - another.getVertical()    * _y - another.getVertical()));
}

Circle(double x, double y, double radius) {
  Point _center(x, y);
  _radius = radius;
}

Circle() {
  Point _center();
  _radius = 1;
}

Point getCenter() {
  return _center;
}

double getRadius() {
  return _radius;
}

void setCenter(double x, double y) {
  _center.setHorizontal(x);
  _center.setVertical(y);
}

void setRadius(double radius) {
  _radius = radius;
}

bool isOverlap(const Circle& another) const {
  return _center.distTo(another.getCenter()) <= _radius + another.getRadius();
}

#endif
