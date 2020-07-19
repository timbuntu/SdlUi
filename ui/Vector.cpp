#include "Vector.h"

using namespace SdlUi;

/**
 * Two Vectors are euqal, if their x and y values both are equal.
 *
 * @param other The Vector to compare to.
 * @return Whether this Vector is equal to the given one
 */
bool Vector::operator==(const Vector& other) const {
    return x == other.x && y == other.y;
}

/**
 * One Vector is smaller than another if their absolute, or length, is smaller.
 *
 * @param other The Vector to compare to.
 * @return Whether this Vector is smaller than the given one
 */
bool Vector::operator<(const Vector& other) const {
    return abs(*this) < abs(other);
}

/**
 * Two Vectors are euqal, if their x and y values both are equal.
 * One Vector is smaller than another if their absolute, or length, is smaller.
 *
 * @param other The Vector to compare to.
 * @return Whether this Vector is smaller than, or equal to, the given one
 */
bool Vector::operator<=(const Vector& other) const {
    return abs(*this) <= abs(other);
}

/**
 * One Vector is bigger than another if their absolute, or length, is bigger.
 *
 * @param other The Vector to compare to.
 * @return Whether this Vector is bigger than the given one
 */
bool Vector::operator>(const Vector& other) const {
    return abs(*this) > abs(other);
}

/**
 * Two Vectors are euqal, if their x and y values both are equal.
 * One Vector is bigger than another if their absolute, or length, is bigger.
 *
 * @param other The Vector to compare to.
 * @return Whether this Vector is bigger than, or equal to, the given one
 */
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

/**
 * Adding two Vectors adds their individual components.
 *
 * @param other The Vector to add to this one
 * @return The sum of this and the given Vector
 */
Vector Vector::operator+(const Vector& other) const {
    return Vector(x+other.x, y+other.y);
}

/**
 * Subtracting two Vectors subtracts their individual elements.
 *
 * @param other The Vector to subtract from this one
 * @return The difference of this and the given Vector
 */
Vector Vector::operator-(const Vector& other) const {
    return Vector(x-other.x, y-other.y);
}

/**
 * Multiplying a Vector with a scalar multiplies its individual components with the scalar.
 *
 * @param other The scalar to multiply with
 * @return The the Vector multiplied by the given scalar
 */
Vector Vector::operator*(const int scalar) const {
    return Vector(scalar*x, scalar*y);
}

Vector Vector::operator* (const float scalar) const {
    return Vector(round(scalar*x), round(scalar*y));
}

/**
 * Multiplying two Vectors of the same dimension returns a scalar which can be interpreted to decern their orientation to each other.
 *
 * @param other The Vector to multiply with
 * @return The scalar product of the two Vectors
 */
float Vector::operator*(const Vector& other) const {
    return x*other.x + y*other.y;
}

/**
 * Returns the absolute, or the length, of the given Vector.
 *
 * @param v The Vector to get the absolute of
 */
float Vector::abs(const Vector& v) {
    return sqrt(((float)v.x)*v.x + ((float)v.y)*v.y);
}
