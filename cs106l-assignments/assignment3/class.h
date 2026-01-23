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