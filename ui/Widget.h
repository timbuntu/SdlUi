#ifndef UI_WIDGET
#define UI_WIDGET

#include "Vector.h"
#include <SDL2/SDL.h>
#include <map>

namespace SdlUi {

    class Widget {
        public:
            Widget(Widget* parent, bool freeChildren = false);
            Widget(Widget* parent, const Vector& pos = Vector(0, 0), unsigned short borderWidth = 0, bool freeChildren = false);
            Widget(Widget* parent, const Vector& pos, const Vector& dimension, unsigned short borderWidth = 0, bool freeChildren = false);

            Vector getPos() const { return pos; }
            Vector getDim() const { return dim; }

            void setPos(const Vector& dim) { this->dim = dim; }
            void resize(const Vector& pos);
            void setPos(const int x, const int y) { pos.x = x; pos.y = y; }
            void resize(const int x, const int y) { this->resize(Vector(x, y)); }
            void scale(const float factorX, const float factorY);

            void setAbsolute(bool absPos) { this->absPos = absPos; }
            bool isAbsolute() const { return absPos; }

            void setBorder(const unsigned short width) { this->borderWidth = width; }
            unsigned short getBorderWidth() const { return borderWidth; }
            bool hasBorder() const { return borderWidth > 0; }

            void addChild(Widget* widget);
            void delChild(Widget* widget) { delChild(widget, freeChildren); }
            bool hasChild(const Widget* widget) const;
            Widget* getParent() { return parent; }

            virtual bool isValid() const { return valid; }
            virtual void draw() const;

            virtual ~Widget();
        protected:
            virtual SDL_Renderer* getRenderer() const { return parent->getRenderer(); }
            
            void fit(const Widget* other);
            void delChild(Widget* widget, bool free);

            virtual void drawBorder() const;

        private:
            static unsigned long idCounter;
            const unsigned long id;
            Widget* parent;
            Vector pos, dim, minimalDim;
            unsigned short borderWidth;
            bool absPos;
            bool valid;
            bool freeChildren;
            std::map<unsigned long, Widget*> children;
    };

}

#endif
