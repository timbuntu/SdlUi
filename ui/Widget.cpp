#include "Widget.h"

using namespace SdlUi;

unsigned long Widget::idCounter = 0;

Widget::Widget(Widget* parent, bool freeChildren)
: Widget(parent, Vector(0, 0), 0, freeChildren)
{

}

Widget::Widget(Widget* parent, const Vector& pos, unsigned short borderWidth, bool freeChildren)
: parent(parent), pos(pos), borderWidth(borderWidth), id(idCounter++), freeChildren(freeChildren)
{
    if(parent)
        this->dim = parent->dim;
    else
        dim = Vector(0, 0);
}

Widget::Widget(Widget* parent, const Vector& position, const Vector& dimension, unsigned short borderWidth, bool freeChildren)
: parent(parent), dim(dimension), pos(position), borderWidth(borderWidth), id(idCounter++), freeChildren(freeChildren)
{
    if(parent)
        parent->addChild(this);
}

void Widget::addChild(Widget* widget) {
    if(hasChild(widget))
        return;

    if(widget->parent != this) {

        if(widget->parent != NULL)
            widget->parent->delChild(widget, false);

        widget->parent = this;
    }
    children.insert(std::pair<unsigned long, Widget*>(widget->id, widget));
    printf("Widget %li: Added widget %li\n", id, widget->id);
}

void Widget::delChild(Widget* widget, bool free) {
    unsigned long id = widget->id;
    if(free)
        delete[] widget;

    if(widget->parent == this)
        widget->parent = NULL;
    children.erase(id);
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
    if(parent == NULL)
        SDL_RenderPresent(renderer);
}

/**
 * Draws inner border around widget.
 **/
void Widget::drawBorder() const {
    if(borderWidth > 0) {
        SDL_Renderer* renderer = getRenderer();
        SDL_Rect rect = {pos.x, pos.y, dim.x, dim.y};
        //printf("Widget %li: Drawing border from %i,%i to %i,%i\n", id, rect.x, rect.y, rect.x+rect.w, rect.y+rect.h);
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF );
        SDL_RenderDrawRect(renderer, &rect);
        rect.x += borderWidth;
        rect.y += borderWidth;
        rect.w -= 2 * borderWidth;
        rect.h -= 2 * borderWidth;
        //printf("Widget %li: And from %i,%i to %i,%i\n", id, rect.x, rect.y, rect.x+rect.w, rect.y+rect.h);
        SDL_RenderDrawRect(renderer, &rect);
    }
}

Widget::~Widget() {
    if(freeChildren)
        for(auto iter : children)
            delete[] iter.second;

    children.clear(); 
}
