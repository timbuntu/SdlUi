#ifndef UI_WIDGET
#define UI_WIDGET

#include "Vector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <map>

namespace SdlUi {
    /**
     * Used for centering on individual axis
     */
    const float CENTER = INFINITY;
    /**
     * Used for filling individual dimension
     */
    const float FILL   = INFINITY;

    /**
     * Used for centering in parent
     */
    const Vector POS_CENTER = Vector(CENTER, CENTER);
    const Vector POS_CENTER_H = Vector(CENTER, 0);
    const Vector POS_CENTER_V = Vector(0, CENTER);
    const Vector DIM_FILL   = Vector(FILL, FILL);

    SDL_Rect createRect(const Vector& pos, const Vector& dim);

    /**
     * Callback Funtion for events
     */
    typedef void (*EventListener)(const SDL_Event*);

    /**
     * The base Widget class contains common functions for all Widgets,
     * and can by itself be used as pane or container for adding other Widgets.
     */
    class Widget {
        public:
            Widget(Widget* parent, bool freeChildren = false);
            Widget(Widget* parent, const Vector& pos, unsigned short borderWidth = 0, bool freeChildren = false);
            Widget(Widget* parent, const Vector& pos, const Vector& dimension, unsigned short borderWidth = 0, bool freeChildren = false);

            Vector getPos() const;
            Vector getDim() const;

            void setPos(const Vector& pos);
            void setPos(const float x, const float y);
            void resize(const Vector& dim);
            void resize(const float x, const float y);
            void scale(const float factorX, const float factorY);

            void setBorder(const unsigned short width);
            unsigned short getBorderWidth() const;
            bool hasBorder() const;

            void addChild(Widget* widget);
            void delChild(Widget* widget);
            bool hasChild(const Widget* widget) const;
            Widget* getParent();

            void addListener(const uint32_t, const EventListener);
            void handleEvent(const SDL_Event*);

            virtual bool isValid() const;
            bool freesChildren() const;
            virtual void draw() const;

            virtual ~Widget();
        protected:
            virtual SDL_Renderer* getRenderer() const;
            
            void fit(const Widget* other);
            bool containsPoint(float x, float y) const;
            bool containsPoint(Vector p) const;
            void delChild(Widget* widget, bool free);

            virtual void drawBorder() const;


        private:
            static unsigned long idCounter;
            const unsigned long id;
            Widget* parent;
            Vector pos, dim, minimalDim;
            unsigned short borderWidth;
            bool valid = true;
            bool freeChildren;
            std::map<unsigned long, Widget*> children;
            /**
             * Maps EventListeners to SDL_Event types
             */
            std::map<uint32_t, EventListener> listeners;
    };

}

#endif
