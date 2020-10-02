#include "Widget.h"

using namespace SdlUi;

unsigned long Widget::idCounter = 0;

/**
 * Create Widget with given parent, or none if passed a null pointer.
 * Optionally can be passed a bool to determine whether the Widget should free its children. Default behaviour is to not free them.
 *
 * @param parent Parent of the new Widget, null pointer if there is none
 */
Widget::Widget(Widget* parent)
: Widget(parent, Vector(0, 0), 0)
{

}

/**
 * Create Widget at the given position with given parent, or none if passed a null pointer.
 * Optionally can be passed a borderwidth, and a bool to determine whether the Widget should free its children. Default behaviour is to not free them.
 *
 * @param parent Parent of the new Widget, null pointer if there is none
 * @param pos The position of the Widget
 * @param borderWidth The width of the border to draw around the widget
 */
Widget::Widget(Widget* parent, const Vector& pos, unsigned short borderWidth)
: parent(parent), pos(pos), borderWidth(borderWidth), minimalDim(2*borderWidth, 2*borderWidth), id(idCounter++), bFreeChildren(false)
{
    if(parent)
        this->dim = parent->dim;
    else
        dim = Vector(0, 0);
}

/**
 * Create Widget at the given position with the given dimension, and the given parent, or none if passed a null pointer.
 * If the dimension is too big to fit into the parent, it is shrinked to the maximal fitting size.
 * Optionally can be passed a borderwidth, and a bool to determine whether the Widget should free its children. Default behaviour is to not free them.
 *
 * @param parent Parent of the new Widget, null pointer if there is none
 * @param position The position of the Widget
 * @param dimension The dimension of the Widget
 * @param borderWidth The width of the border to draw around the widget
 */
Widget::Widget(Widget* parent, const Vector& position, const Vector& dimension, unsigned short borderWidth)
: parent(parent), dim(dimension), borderWidth(borderWidth), minimalDim(2*borderWidth, 2*borderWidth), id(idCounter++), bFreeChildren(false)
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

/**
 * Scales the Widget, including all its children, by factorX and factorY
 *
 * @param factorX The factor with whitch to scale on x axis
 * @param factorY The factor with whitch to scale on y axis
 */
void Widget::scale(const float factorX, const float factorY) {
    for(auto child : children)
        child.second->scale(factorX, factorY);

    if(factorX != 1 && factorX != INFINITY) {
        this->dim.x = this->dim.x * factorX;
        this->pos.x = this->pos.x * factorX;
    }
    if(factorY != 1 && factorY != INFINITY) {
        this->dim.y = this->dim.y * factorY;
        this->pos.y = this->pos.y * factorY;
    }
}

/**
 * Adds the given Widget as child.
 * Sets the parent property of the child, and reduces size to parent size if neccessary.
 *
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
}

/**
 * Returns the position of this Widget.
 *
 * @return The position of this Widget
 */
Vector Widget::getPos() const {
    return this->pos;
}

/**
 * Returns the dimension of this Widget.
 *
 * @return The dimension of this Widget
 */
Vector Widget::getDim() const {
    return this->dim;
}

/**
 * Sets the position of the Widget to the given position.
 *
 * @param pos The position the move the Widget to
 */
void Widget::setPos(const Vector& pos) {
    this->setPos(pos.x, pos.y);
}

/**
 * Sets the position of the Widget to the given coordinates.
 *
 * @param x The x coordinate
 * @param y the y coordinate
 */
void Widget::setPos(const float x, const float y) {
    this->pos.x = x == CENTER ? (parent->dim.x/2 - this->dim.x/2) : x;
    this->pos.y = y == CENTER ? (parent->dim.y/2 - this->dim.y/2) : y;
}

/**
 * Resizes the widget to the given size, scaling all its content.
 *
 * @param x The x dimension to set
 * @param y The y dimension to set
 */
 void Widget::resize(const float x, const float y) {
     this->resize(Vector(x,y));
 }

/**
 * Resizes the widget to the given size, scaling all its content.
 *
 * @param dim The dimension to resize to
 */
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

/**
 * Removes the given Widget as child if it is one. If the bFreeChildren option was set in Constructor, also frees the child.
 *
 * @param widget The widget to remove as child
 */
void Widget::delChild(Widget* widget) {
    this->delChild(widget, this->bFreeChildren);
}

/**
 * Removes the given Widget as it child if it is one. If the free parameter is set to true, also frees the child.
 *
 * @param widget The widget to remove as child
 * @param free Whether to free the child after removal
 */
void Widget::delChild(Widget* widget, bool free) {
    if(!widget)
        return;

    unsigned long id = widget->id;
    if(free)
        delete[] widget;

    if(widget->parent == this)
        widget->parent = NULL;
    children.erase(id);
}

/**
 * Checks whether the given Widget is a child of this Widget.
 *
 * @param widget
 * @return Whether the given Widget is a child of this Widget
 */
bool Widget::hasChild(const Widget* widget) const {
    return children.find(widget->id) != children.end();
}

/**
 * Adds the listener for the given SDL_Event type
 *
 * @param type The SDL_Event type to add the listener for
 * @param listener The EventListener to add
 */
void Widget::addListener(const uint32_t type, const EventListener listener) {
    listeners.insert(std::make_pair(type, listener));
}

/**
 * Calls the corresponding EventListener for the SDL_Event, if there is any
 *
 * @param event The SDL_Event that occured
 */
void Widget::handleEvent(const SDL_Event* event) {
    //Special case for mouse events
    //They are only considered if inside the widgets bounds
    bool ignoreEvent = false;

    switch(event->type) {
        case SDL_MOUSEMOTION:
            ignoreEvent = !this->containsPoint(event->motion.x, event->motion.y);
            break;
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEBUTTONDOWN:
            ignoreEvent = !this->containsPoint(event->button.x, event->button.y);
            break;
        case SDL_MOUSEWHEEL:
            int x, y;
            SDL_GetMouseState(&x, &y);
            ignoreEvent = !this->containsPoint(x, y);
            break;
    }
    if(ignoreEvent)
        return;
        
    auto listener = listeners.find(event->type);
    if(listener != listeners.end())
        listener->second(this, event);

    for(auto child : children)
        child.second->handleEvent(event);
}

/**
 * Checks whether this Widget was initialized correctly, and is fully functional.
 *
 * @return Whether this Widget was initialized correctly
 */
bool Widget::isValid() const {
    return valid;
}

/**
 * Set whether this Widget should free its children on removal, or not.
 *
 * @param free Whether to free children
 */
void Widget::freeChildren(bool free) {
    this->bFreeChildren = free;
}

/**
 * Check whether this Widget frees its children on removal, or its destruction.
 *
 * @return Whether this Widget frees its children.
 */
bool Widget::freesChildren() const {
    return bFreeChildren;
}

/**
 * Set the width of the inner border for this Widget.
 *
 * @param width The width to set the borderwidth to
 */
void Widget::setBorder(const unsigned short width) {
    this->borderWidth = width;
}

/**
 * Get the width of the inner border for this Widget.
 *
 * @return The borderwidth of this Widget
 */
unsigned short Widget::getBorderWidth() const {
    return borderWidth;
}

/**
 * Check whether this Widget has its borderwidth set to any value greater zero.
 *
 * @return Whether this Widget draws a border
 */
bool Widget::hasBorder() const {
    return borderWidth > 0;
}

/**
 * Draws the Widget, and all its children. The widget itself is drawn first, its children after that.
 */
void Widget::draw() const {
    SDL_Renderer* renderer = getRenderer();
    if(parent == NULL) {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear(renderer);
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_Rect rect = createRect(pos, dim);
    SDL_RenderFillRect(renderer, &rect);
    drawBorder();

    for(auto iter : children)
        iter.second->draw();

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

/**
 * Get the parent of this Widget.
 *
 * @return The parent of this Widget
 */
Widget* Widget::getParent() {
    return parent;
}

/**
 * Get the underlying SDL_Renderer. Used by this and its child Widgets to draw their content to.
 *
 * @return The underlying SDL_Renderer
 */
SDL_Renderer* Widget::getRenderer() const {
    return parent->getRenderer();
}

/**
 * Checks whether this Widget fits into the given other Widget, if not, resizes itself to fit.
 *
 * @param other The Widget to fit this into
 */
void Widget::fit(const Widget* other) {
    
    Vector spaceReq(this->pos + this->dim);
    if(spaceReq.x > other->dim.x || spaceReq.y > other->dim.y) {
        this->resize(
                (this->pos.x + this->dim.x) <= other->dim.x ? this->dim.x : (other->dim.x - this->pos.x),
                (this->pos.y + this->dim.y) <= other->dim.y ? this->dim.y : (other->dim.y - this->pos.y)
        );
    }
}
            
/**
 * Checks whether a given point is inside the Widgets bounds
 *
 * @param p The point to check
 */
bool Widget::containsPoint(Vector p) const {
    return containsPoint(p.x, p.y);
}

/**
 * Checks whether a given point is inside the Widgets bounds
 *
 * @param x The x coordinate of the point
 * @param y The y coordinate of the point
 */
bool Widget::containsPoint(float x, float y) const {
    return (this->pos.x <= x && this->pos.x + this->dim.x >= x) && (this->pos.y <= y && this->pos.y + this->dim.y >= y);
}
/**
 * Creates a SDL_Rect from the given posistion and dimension Vectors.
 *
 * @param pos The position to create the rect at
 * @param dim The dimension of the rect to create
 * @return The SDL_Rect for the given values
 */
SDL_Rect SdlUi::createRect(const Vector& pos, const Vector& dim) {
    return {(int)round(pos.x), (int)round(pos.y), (int)round(dim.x), (int)round(dim.y)};
}

/**
 * On destruction removes all children, and depending on the bFreeChildren parameter given in the constructor, also frees them.
 */
Widget::~Widget() {
    for(auto iter = children.begin(); iter != children.end(); ) {
        Widget* child = iter->second;
        ++iter;
        this->delChild(child);
    }
}
