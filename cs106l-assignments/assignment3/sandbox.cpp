/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */
#include <iostream>
#include "class.h"

void sandbox() {
  // STUDENT TODO: Construct an instance of your class!
  Point3D p1(1.0, 2.0, 3.0);
  Point3D p2(4.0, 5.0, 6.0);
  std::cout << "Point 1: " << p1 << "\n";
  std::cout << "Point 2: " << p2 << "\n";
  std::cout << "Distance between Point 1 and Point 2: " << p1.distanceTo(p2) << "\n";
  p1.moveBy(1.0, 1.0, 1.0);
  std::cout << "Point 1 after moving by (1, 1, 1): " << p1 << "\n";
  p1.add(p2);
  std::cout << "Point 1 after adding Point 2: " << p1 << "\n";
}