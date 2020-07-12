#include <cstdio>
#include "../ui/SdlUi.h"


int main(int argc, const char** argv) {
    SdlUi::Vector vecs[4] = { SdlUi::Vector(0,0), SdlUi::Vector(1,0), SdlUi::Vector(0,2), SdlUi::Vector(2,2) };
    for(SdlUi::Vector vec : vecs)
        printf("|(%f, %f)| = %f\n", vec.x, vec.y, abs(vec));

    if(!SdlUi::Init()) {
        printf("Failed initializing SdlUi!\n");
        return 1;
    }

    SdlUi::Window window("Test Window");
    int widgetWidth = window.getDim().x / 2;
    int widgetHeight = window.getDim().y;
    SdlUi::Widget left(&window, SdlUi::Vector(0, 0), SdlUi::Vector(widgetWidth, widgetHeight), 3);
    SdlUi::Widget right(&window, SdlUi::Vector(widgetWidth, 0), SdlUi::Vector(widgetWidth, widgetHeight), 3);

    if(window.isValid())
        printf("Successfully created window of size %fx%f!\n", window.getDim().x, window.getDim().y);
    else
        printf("Failed to create window!\n");
    
    SdlUi::Loop(&window);
    SdlUi::Quit();
    return 0;
}
