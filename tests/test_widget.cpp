#include "testing.h"

using namespace SdlUi;

void addConstructorTests(void);
void addChildTests      (void);
void addResizeTests     (void);

int main(int argc, const char** argv) {
    addConstructorTests();   
    addChildTests();
    addResizeTests();
    runTests();
}

void addConstructorTests(void) {
    TEST_ADD("Constructor1", [](void) {
        Widget widget(nullptr);
        
        assert(widget.getDim()         == Vector(0,0));
        assert(widget.getPos()         == Vector(0,0));
        assert(widget.getParent()      == nullptr    );
        assert(widget.freesChildren()  == false      );
        assert(widget.isValid()        == true       );
        assert(widget.getBorderWidth() == 0          );
    });

    TEST_ADD("Constructor2", [](void) {
        Widget widgetDefault(nullptr, Vector(0, 200));
        
        assert(widgetDefault.getPos()         == Vector(0,200));
        assert(widgetDefault.getDim()         == Vector(0,0)  );
        assert(widgetDefault.getParent()      == nullptr      );
        assert(widgetDefault.freesChildren()  == false        );
        assert(widgetDefault.isValid()        == true         );
        assert(widgetDefault.getBorderWidth() == 0            );

        Widget widgetCustom(nullptr, Vector(0, 200), 4, true);
        
        assert(widgetCustom.getPos()         == Vector(0,200));
        assert(widgetCustom.getDim()         == Vector(0,0)  );
        assert(widgetCustom.getParent()      == nullptr      );
        assert(widgetCustom.freesChildren()  == true         );
        assert(widgetCustom.isValid()        == true         );
        assert(widgetCustom.getBorderWidth() == 4            );
    });

    TEST_ADD("Constructor3", [](void) {
        Widget widgetDefault(nullptr, Vector(200, 200), Vector(400, 400));
        
        assert(widgetDefault.getPos()         == Vector(200,200));
        assert(widgetDefault.getDim()         == Vector(400,400));
        assert(widgetDefault.getParent()      == nullptr        );
        assert(widgetDefault.freesChildren()  == false          );
        assert(widgetDefault.isValid()        == true           );
        assert(widgetDefault.getBorderWidth() == 0              );

        Widget widgetCustom(nullptr, Vector(200, 200), Vector(640, 480), 4, true);
        
        assert(widgetCustom.getPos()         == Vector(200,200));
        assert(widgetCustom.getDim()         == Vector(640,480));
        assert(widgetCustom.getParent()      == nullptr        );
        assert(widgetCustom.freesChildren()  == true           );
        assert(widgetCustom.isValid()        == true           );
        assert(widgetCustom.getBorderWidth() == 4              );
    });
}

static void testParentChild(Widget* parent, Widget* child) {
    assert(child->getParent() == parent);
    assert(parent->hasChild(child));
    assert(child->getPos() >= parent->getPos());
    assert(child->getPos() + child->getDim() <= parent->getDim());

    parent->delChild(child);
    assert(parent->hasChild(child) == false);
    assert(child->getParent() == nullptr);
}

void addChildTests(void) {
    TEST_ADD("Childs via parent pointer", [](void) {
        Widget parent(nullptr, Vector(0,0), Vector(640,480));
        Widget child(&parent, Vector(0,0), Vector(1000,1000));
        
        testParentChild(&parent, &child);
    });

    TEST_ADD("Childs via addChild", [](void) {
        Widget parent(nullptr, Vector(0,0), Vector(640,480));
        Widget child(nullptr, Vector(100,100), Vector(1000,1000));
        parent.addChild(&child);
        
        testParentChild(&parent, &child);
    });
}

void addResizeTests(void) {
    TEST_ADD("Resize", [](void) {
        Widget parent (nullptr, Vector(0,0), Vector(640,480));
        const Vector childSize(parent.getDim().x/2, parent.getDim().y/2);

        Widget child1 (&parent,  Vector(0,           0),           childSize);
        Widget child2 (&parent,  Vector(childSize.x, 0),           childSize);
        Widget child3 (&parent,  Vector(0,           childSize.y), childSize);
        Widget child4 (&parent,  Vector(childSize.x, childSize.y), childSize);
        
        float factor = 1.5f;
        parent.resize(childSize*2 * factor);
        assert(child1.getPos() == Vector(0,                  0                 ));
        assert(child2.getPos() == Vector(childSize.x*factor, 0                 ));
        assert(child3.getPos() == Vector(0,                  childSize.y*factor));
        assert(child4.getPos() == Vector(childSize.x*factor, childSize.y*factor));

        assert(child1.getDim() == childSize*factor);
        assert(child2.getDim() == childSize*factor);
        assert(child3.getDim() == childSize*factor);
        assert(child4.getDim() == childSize*factor);

        parent.resize(childSize*2);
        assert(child1.getPos() == Vector(0,           0          ));
        assert(child2.getPos() == Vector(childSize.x, 0          ));
        assert(child3.getPos() == Vector(0,           childSize.y));
        assert(child4.getPos() == Vector(childSize.x, childSize.y));

        assert(child1.getDim() == childSize);
        assert(child2.getDim() == childSize);
        assert(child3.getDim() == childSize);
        assert(child4.getDim() == childSize);
    });

}

