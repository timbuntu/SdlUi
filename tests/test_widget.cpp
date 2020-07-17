#include "testing.h"

using namespace SdlUi;

void addConstructorTests(void);
void addChildTests(void);

int main(int argc, const char** argv) {
    addConstructorTests();   
    addChildTests();
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
