#include <cstdio>
#include "../ui/SdlUi.h"


int main(int argc, const char** argv) {
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
        printf("Successfully created window of size %ix%i!\n", window.getDim().x, window.getDim().y);
    else
        printf("Failed to create window!\n");
    
    SdlUi::Loop(&window);
    SdlUi::Quit();
    return 0;
}
