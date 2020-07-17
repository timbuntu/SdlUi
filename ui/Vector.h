#ifndef SDLUI_VECTOR
#define SDLUI_VECTOR

#include <cmath>

namespace SdlUi {

    /**
     * Class representing a 2d Vector with floating point precision.
     */
    class Vector {
        public:

            Vector() : x(0), y(0) {}
            Vector(float x, float y) : x(x), y(y) {}
            Vector(const Vector& v) : x(v.x), y(v.y) {}

            bool    operator==(const Vector&) const;
            bool    operator>(const Vector&) const;
            bool    operator>=(const Vector&) const;
            bool    operator<(const Vector&) const;
            bool    operator<=(const Vector&) const;

            Vector& operator+=(const Vector&);
            Vector  operator+ (const Vector&) const;
            Vector& operator-=(const Vector&);
            Vector  operator- (const Vector&) const;
            Vector  operator* (const int)    const;
            Vector  operator* (const float)    const;
            float     operator* (const Vector&) const;

            static float abs(const Vector& v);

            float x, y;
    };


}

#endif
