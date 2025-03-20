/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */

#include "class.h"
#include <iostream> 

void sandbox() {
  // STUDENT TODO: Construct an instance of your class!
  double x, y, radius;

  std::cout << "Please input the center coordinates for circle 1: ";
  std::cin >> x >> y >> radius;
  Circle c1(x, y, radius);
  std::cout << "Please input the center coordinates for circle 2: ";
  std::cin >> x >> y >> radius;
  Circle c2(x, y, radius);
  std::cout << "These distance between the two points is " << c1.getCenter().distTo(c2.getCenter()) << std::endl;
  std::cout << "These two circles are " << (c1.isOverlap(c2) ? "" : "not ") << "overlapped." << std::endl;
}