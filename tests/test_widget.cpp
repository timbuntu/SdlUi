#include "testing.h"

using namespace SdlUi;

int main(int argc, const char** argv) {
    
    TEST_ADD("Constructor1", {
        Widget widget(nullptr);
        
        assert(widget.getDim()         == Vector(0,0));
        assert(widget.getPos()         == Vector(0,0));
        assert(widget.getParent()      == nullptr    );
        assert(widget.freesChildren()  == false      );
        assert(widget.isValid()        == true       );
        assert(widget.getBorderWidth() == 0          );
    });

    TEST_ADD("Constructor2", {
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

    TEST_ADD("Constructor3", {
        Widget widgetDefault(nullptr, Vector(200, 200), Vector(400, 400));
        
        assert(widgetDefault.getPos()         == Vector(200,200));
        assert(widgetDefault.getDim()         == Vector(400,400)  );
        assert(widgetDefault.getParent()      == nullptr      );
        assert(widgetDefault.freesChildren()  == false        );
        assert(widgetDefault.isValid()        == true         );
        assert(widgetDefault.getBorderWidth() == 0            );

        Widget widgetCustom(nullptr, Vector(200, 200), Vector(640, 480), 4, true);
        
        assert(widgetCustom.getPos()         == Vector(200,200));
        assert(widgetCustom.getDim()         == Vector(640,480));
        assert(widgetCustom.getParent()      == nullptr        );
        assert(widgetCustom.freesChildren()  == true           );
        assert(widgetCustom.isValid()        == true           );
        assert(widgetCustom.getBorderWidth() == 4              );
    });

    runTests();
}
