#ifndef SDLUI
#define SDLUI

#include "Window.h"

namespace SdlUi {

    bool Init() {
        bool success = true;

        if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
            success = false;
            printf( "SdlUi::Init(): SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        }

        return success;
    }

    void Quit() {
        SDL_Quit();
    }

}
#endif
