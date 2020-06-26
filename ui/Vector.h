#ifndef SDLUI_VECTOR
#define SDLUI_VECTOR

namespace SdlUi {

    class Vector {
        public:

            Vector() : x(0), y(0) {}
            Vector(int x, int y) : x(x), y(y) {}
            Vector(const Vector& v) : x(v.x), y(v.y) {}

            Vector& operator+=(const Vector&);
            Vector operator+(const Vector&) const;
            Vector& operator-=(const Vector&);
            Vector operator-(const Vector&) const;
            Vector operator*(const int&)    const;
            int    operator*(const Vector&) const;

            int x, y;
    };

}

#endif
