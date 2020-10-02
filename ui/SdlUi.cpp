#include "SdlUi.h"

/*! \mainpage Index
 *
 * \section intro_sec Introduction
 *
 * This is the introduction.
 *
 * \section install_sec Installation
 *
 * \subsection install_req Requirements
 *
 * SdlUi needs SDL2, SDL2_image, and SDL2_ttf.
 *  
 * \subsection install_build Building
 * 
 * ```bash
 * mkdir build
 * cd build
 * cmake ..
 * make
 * ```
 */

using namespace SdlUi;

bool SdlUi::Init() {
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        success = false;
        printf( "SdlUi::Init(): SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
            
    return success;
}

void SdlUi::Loop(Widget* mainWidget) {
    bool quit = false;
    SDL_Event event;

    while(!quit) {

        while(SDL_PollEvent(&event) != 0) {
            switch(event.type) {
                case SDL_QUIT:
                    quit = true;
                default:
                    mainWidget->handleEvent(&event);
            }
        }

        mainWidget->draw();
        //SDL_Delay(50);
    }
}

void SdlUi::Quit() {
    SDL_Quit();
}
