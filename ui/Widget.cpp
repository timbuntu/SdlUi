#include "Widget.h"

using namespace SdlUi;

unsigned long Widget::idCounter = 0;

Widget::Widget(const Vector& dimension, const Vector& position, bool absPos)
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
    for(auto iter : children)
        iter.second->draw();
}

Widget::~Widget() {
    for(auto iter : children)
        delete[] iter.second;

    children.clear(); 
}
