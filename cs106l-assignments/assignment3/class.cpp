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