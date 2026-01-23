## 实现一个类

在这里我实现了一个三维点类：

- 头文件

```c++
#ifndef __3DPOINT__H_
#define __3DPOINT__H_
#include <iostream>

class Point3D {
public:
    Point3D();
    Point3D(double xCoord, double yCoord, double zCoord);

    double getX() const;
    double getY() const;
    double getZ() const;

    void setX(double xCoord);
    void setY(double yCoord);
    void setZ(double zCoord);

    double distanceTo(const Point3D& other) const;
    void moveBy(double deltaX, double deltaY, double deltaZ);
    void add(const Point3D& other);
    friend std::ostream& operator<<(std::ostream &os, const Point3D &point);

private:
    void print() const;
    double x;
    double y;
    double z;
};

#endif
```

- 源文件

```c++
#include <cmath>
#include "class.h"
#include <iostream>
#include <format>

Point3D::Point3D() : x(0), y(0), z(0) {}
Point3D::Point3D(double xCoord, double yCoord, double zCoord)
        : x(xCoord), y(yCoord), z(zCoord) {}

double Point3D::getX() const { return x; }
double Point3D::getY() const { return y; }
double Point3D::getZ() const { return z; }

void Point3D::setX(double xCoord) { x = xCoord; }
void Point3D::setY(double yCoord) { y = yCoord; }
void Point3D::setZ(double zCoord) { z = zCoord; }

double Point3D::distanceTo(const Point3D& other) const {
    double dx = x - other.x;
    double dy = y - other.y;
    double dz = z - other.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}   

void Point3D::moveBy(double deltaX, double deltaY, double deltaZ) {
    x += deltaX;
    y += deltaY;
    z += deltaZ;
}

void Point3D::add(const Point3D& other) {
    x += other.x;
    y += other.y;
    z += other.z;
}

std::ostream& operator<<(std::ostream &os, const Point3D &point) {
    os << std::format("Point({}, {}, {})", point.x, point.y, point.z);
    return os;
}

void Point3D::print() const { std::cout << "Point(" << x << ", " << y << ", " << z << ")"; }
```

## 测试结果

```shell
~/minghan/courses/CS106L/cs106l-assignments/assignment3 % ./main
Point 1: Point(1, 2, 3)
Point 2: Point(4, 5, 6)
Distance between Point 1 and Point 2: 5.19615
Point 1 after moving by (1, 1, 1): Point(2, 3, 4)
Point 1 after adding Point 2: Point(6, 8, 10)
⏳ Installing autograder packages (this may take a few minutes)...
✅ Autograder packages installed.

Running test: Autograder Setup... 🧪
Autograder found class Point3D inside class.h!

Running test: #1 / Public parameterized constructor... 🧪
⏩ Disregarding Point3D::Point3D() [constructor], has no arguments
🔍 Found Point3D::Point3D(double xCoord, double yCoord, double zCoord) [constructor]!
✅ #1 / Public parameterized constructor passed! 🚀

Running test: #2 / Public parameterless constructor... 🧪
🔍 Found Point3D::Point3D() [constructor]!
✅ #2 / Public parameterless constructor passed! 🚀

Running test: #3 / Private field... 🧪
🔍 Found Point3D::x [variable]!
✅ #3 / Private field passed! 🚀

Running test: #4 / Private member function... 🧪
⏩ Disregarding double Point3D::getX() const [member function], not private
⏩ Disregarding double Point3D::getY() const [member function], not private
⏩ Disregarding double Point3D::getZ() const [member function], not private
⏩ Disregarding void Point3D::setX(double xCoord) [member function], not private
⏩ Disregarding void Point3D::setY(double yCoord) [member function], not private
⏩ Disregarding void Point3D::setZ(double zCoord) [member function], not private
⏩ Disregarding double Point3D::distanceTo(Point3D const & other) const [member function], not private
⏩ Disregarding void Point3D::moveBy(double deltaX, double deltaY, double deltaZ) [member function], not private
⏩ Disregarding void Point3D::add(Point3D const & other) [member function], not private
🔍 Found void Point3D::print() const [member function]!
✅ #4 / Private member function passed! 🚀

Running test: #5 / Public getter function... 🧪
🔍 Found double Point3D::getX() const [member function]!
✅ #5 / Public getter function passed! 🚀

Running test: #6 / Public setter function... 🧪
🔍 Found void Point3D::setX(double xCoord) [member function]!
✅ #6 / Public setter function passed! 🚀

🚀🚀🚀 Congratulations, your code passed all the autograder tests! 🚀🚀🚀
```

