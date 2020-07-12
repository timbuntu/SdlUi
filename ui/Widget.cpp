#include "Widget.h"

using namespace SdlUi;

unsigned long Widget::idCounter = 0;

Widget::Widget(Widget* parent, bool freeChildren)
: Widget(parent, Vector(0, 0), 0, freeChildren)
{

}

Widget::Widget(Widget* parent, const Vector& pos, unsigned short borderWidth, bool freeChildren)
: parent(parent), pos(pos), borderWidth(borderWidth), minimalDim(2*borderWidth, 2*borderWidth), id(idCounter++), freeChildren(freeChildren)
{
    if(parent)
        this->dim = parent->dim;
    else
        dim = Vector(0, 0);
}

Widget::Widget(Widget* parent, const Vector& position, const Vector& dimension, unsigned short borderWidth, bool freeChildren)
: parent(parent), dim(dimension), borderWidth(borderWidth), minimalDim(2*borderWidth, 2*borderWidth), id(idCounter++), freeChildren(freeChildren)
{
    if(parent) {
        this->setPos(position);
        parent->addChild(this);
    } else if(position.x != CENTER && position.y != CENTER)
        this->setPos(position);
    else if(position.x == CENTER && position.y == CENTER)
        this->setPos(0, 0);
    else if(position.x == CENTER)
        this->setPos(0, position.y);
    else //if(position.y == CENTER)
        this->setPos(position.x, 0);
}

void Widget::scale(const float factorX, const float factorY) {
    printf("Widget %li: Scaling by factors %f, %f\n", this->id, factorX, factorY);
    for(auto child : children)
        child.second->scale(factorX, factorY);

    if(factorX != 1 && factorX != INFINITY) {
        printf("Widget %li: Scaling x\n", this->id);
        this->dim.x = this->dim.x * factorX;
        this->pos.x = this->pos.x * factorX;
    }
    if(factorY != 1 && factorY != INFINITY) {
        printf("Widget %li: Scaling y\n", this->id);
        this->dim.y = this->dim.y * factorY;
        this->pos.y = this->pos.y * factorY;
    }
    printf("Widget %li: Resized to %f, %f\n", this->id, this->dim.x, this->dim.y);
}

/**
 * Adds the given Widget as child.
 * Sets the parent property of the child, and reduces size to parent size if neccessary.
 * @param widget The Widget to add
 */
void Widget::addChild(Widget* widget) {
    if(hasChild(widget))
        return;

    if(widget->parent != this) {

        if(widget->parent != NULL)
            widget->parent->delChild(widget, false);

        widget->parent = this;
    }
    widget->fit(this);

    children.insert(std::pair<unsigned long, Widget*>(widget->id, widget));
    //TODO More elaborate calculation of minimalDim for multiple children
    if(widget->minimalDim < this->minimalDim)
        this->minimalDim = widget->minimalDim;

    printf("Widget %li: Added widget %li\n", id, widget->id);
}

void Widget::setPos(const float x, const float y) {
    this->pos.x = x == CENTER ? (parent->dim.x/2 - this->dim.x/2) : x;
    this->pos.y = y == CENTER ? (parent->dim.y/2 - this->dim.y/2) : y;
}

void Widget::resize(const Vector& dim) {
    if(parent) {
        if((this->pos + dim) > parent->dim) {
            this->resize(parent->dim - this->pos);
            return;
        }
    }

    const float scaleX = ((float)dim.x) / this->dim.x;
    const float scaleY = ((float)dim.y) / this->dim.y;
    this->scale(scaleX, scaleY);
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

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_Rect rect = createRect(pos, dim);
    SDL_RenderFillRect(renderer, &rect);

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
        SDL_Rect rect = createRect(pos, dim);
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF );
        SDL_RenderDrawRect(renderer, &rect);
        rect.x += borderWidth;
        rect.y += borderWidth;
        rect.w -= 2 * borderWidth;
        rect.h -= 2 * borderWidth;
        SDL_RenderDrawRect(renderer, &rect);
    }
}

void Widget::fit(const Widget* other) {
    
    printf("Widget %li: Fitting to parent...\n", id);
    Vector spaceReq(this->pos + this->dim);
    if(spaceReq.x > other->dim.x || spaceReq.y > other->dim.y) {
        this->resize(
                (this->pos.x + this->dim.x) <= other->dim.x ? this->dim.x : (other->dim.x - this->pos.x),
                (this->pos.y + this->dim.y) <= other->dim.y ? this->dim.y : (other->dim.y - this->pos.y)
        );
    } else
        printf("Widget %li: Don't need to resize\n", id);

}

SDL_Rect SdlUi::createRect(const Vector& pos, const Vector& dim) {
    return {(int)round(pos.x), (int)round(pos.y), (int)round(dim.x), (int)round(dim.y)};
}

Widget::~Widget() {
    if(freeChildren)
        for(auto iter : children)
            delete[] iter.second;

    children.clear(); 
}
