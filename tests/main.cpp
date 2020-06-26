#include <cstdio>
#include "../ui/SdlUi.h"


int main(int argc, const char** argv) {
    if(!SdlUi::Init()) {
        printf("Failed initializing SdlUi!\n");
        return 1;
    }

    SdlUi::Window window("Test Window");

    if(window.isValid())
        printf("Successfully created window of size %ix%i!\n", window.getDim().x, window.getDim().y);
    else
        printf("Failed to create window!\n");

    SDL_Delay(2000);
    SdlUi::Quit();
    return 0;
}
