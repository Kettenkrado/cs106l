/**
 * @file   class.h
 * @brief  The class definition of points and circles.
 * @author Ivy Blossom
 * @data   2025.3.10
 *
 */

#ifndef CLASS_H 
#define CLASS_H

class Point {
 private:
  double _x;
  double _y;
 public:
  Point(double x, double y);
  // default constructor, set the point coordinate to (0, 0)
  Point();

  // Getter functions
  double getHorizontal() const;
  double getVertical() const;

  // Setter functions
  void setHorizontal(double x);
  void setVertical(double y);

  /**
   * @brief    Calculate the distance between two points.
   * @param    Another point.
   * @returns  The distance to the other point.
   *
   */
  double distTo(const Point& another) const;
};

class Circle {
 private:
  Point _center;
  double _radius;
 public:
  Circle(double x, double y, double radius);
  // default constructor, set the circle to be a unit circle
  // with center at (0, 0) and radius being 1
  Circle();

  // Getter functions
  Point getCenter() const;
  double getRadius() const;

  // Setter functions
  void setCenter(double x, double y);
  void setRadius(double radius);

  /**
   * @brief    Determine if this circle overlaps another one.
   * @param    Another circle.
   * @returns  True if they overlap, false otherwise.
   * @note     If they are tangent, consider them as overlapped.
   *
   */
  bool isOverlap(const Circle& another) const;
};

#endif
