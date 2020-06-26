#ifndef UI_WIDGET
#define UI_WIDGET

#include "Vector.h"
#include <map>

namespace SdlUi {

    class Widget {
        public:
            Widget(const Vector& dimension = Vector(0, 0), const Vector& position = Vector(0, 0), bool absPos = 0);

            Vector getPos() const { return pos; }
            Vector getDim() const { return dim; }

            void setPos(const Vector& pos) { this->pos = pos; }
            void setDim(const Vector& dim) { this->dim = dim; }

            void setAbsolute(bool absPos) { this->absPos = absPos; }
            bool isAbsolute() const { return absPos; }

            void addChild(Widget* widget);
            void delChild(const Widget* widget);
            bool hasChild(const Widget* widget) const;

            virtual void draw() const;

            virtual ~Widget() = 0;

        private:
            static unsigned long idCounter;
            const unsigned long id;
            Vector pos, dim;
            bool absPos;
            std::map<unsigned long, Widget*> children;
    };

}

#endif
