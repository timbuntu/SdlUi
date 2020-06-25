#include "Vector.h"

using namespace SdlUi;

Vector& Vector::operator+=(const Vector& other){
    x += other.x;
    y += other.y;
    return *this;
}

Vector& Vector::operator-=(const Vector& other){
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector Vector::operator+(const Vector& other) const {
    return Vector(x+other.x, y+other.y);
}

Vector Vector::operator-(const Vector& other) const {
    return Vector(x-other.x, y-other.y);
}

Vector Vector::operator*(const int& scalar) const {
    return Vector(scalar*x, scalar*y);
}

int Vector::operator*(const Vector& other) const {
    return x*other.x + y*other.y;
}
