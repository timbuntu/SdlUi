#include <cstdio>
#include "../ui/SdlUi.h"


int main(int argc, const char** argv) {
    if(!SdlUi::Init()) {
        printf("Failed initializing SdlUi!\n");
        return 1;
    }

    SdlUi::Window window("Test Window");
    window.setBorder(10);

    if(window.isValid())
        printf("Successfully created window of size %ix%i!\n", window.getDim().x, window.getDim().y);
    else
        printf("Failed to create window!\n");
    
    SdlUi::Loop(&window);
    SdlUi::Quit();
    return 0;
}
