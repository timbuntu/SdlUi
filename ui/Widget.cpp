#include "Widget.h"

using namespace SdlUi;

unsigned long Widget::idCounter = 0;

Widget::Widget(const Widget* parent, const Vector& dimension, const Vector& position, bool absPos)
: dim(dimension), pos(position), absPos(absPos), id(idCounter++)
{
}

void Widget::addChild(Widget* widget) {
    children.insert(std::pair<unsigned long, Widget*>(widget->id, widget));
}

void Widget::delChild(const Widget* widget) {
    children.erase(widget->id);
}

bool Widget::hasChild(const Widget* widget) const {
    return children.find(widget->id) != children.end();
}

void Widget::draw() const {
    SDL_Renderer* renderer = getRenderer();
    if(parent == NULL) {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear(renderer);
    }

    for(auto iter : children)
        iter.second->draw();

    drawBorder();
    SDL_RenderPresent(renderer);
}

/**
 * Draws inner border around widget.
 **/
void Widget::drawBorder() const {
    if(borderWidth > 0) {
        SDL_Renderer* renderer = getRenderer();
        SDL_Rect rect = {pos.x, pos.y, dim.x, dim.y};
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF );
        SDL_RenderDrawRect(renderer, &rect);
        rect.x += borderWidth;
        rect.y += borderWidth;
        rect.w -= 2 * borderWidth;
        rect.h -= 2 * borderWidth;
        SDL_RenderDrawRect(renderer, &rect);
    }
}

Widget::~Widget() {
    for(auto iter : children)
        delete[] iter.second;

    children.clear(); 
}
