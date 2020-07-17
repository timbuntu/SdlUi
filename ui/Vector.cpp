#include "Vector.h"

using namespace SdlUi;

bool Vector::operator==(const Vector& other) const {
    return x == other.x && y == other.y;
}

bool Vector::operator<(const Vector& other) const {
    return abs(*this) < abs(other);
}

bool Vector::operator<=(const Vector& other) const {
    return abs(*this) <= abs(other);
}

bool Vector::operator>(const Vector& other) const {
    return abs(*this) > abs(other);
}

bool Vector::operator>=(const Vector& other) const {
    return abs(*this) >= abs(other);
}

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

Vector Vector::operator*(const int scalar) const {
    return Vector(scalar*x, scalar*y);
}

Vector Vector::operator* (const float scalar) const {
    return Vector(round(scalar*x), round(scalar*y));
}

float Vector::operator*(const Vector& other) const {
    return x*other.x + y*other.y;
}

float SdlUi::abs(const Vector& v) {
    return sqrt(((float)v.x)*v.x + ((float)v.y)*v.y);
}
