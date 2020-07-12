#include "SdlUi.h"

using namespace SdlUi;

bool SdlUi::Init() {
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        success = false;
        printf( "SdlUi::Init(): SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
            
    return success;
}

namespace SdlUi {
static void handleWindowEvent(SDL_WindowEvent* event, Widget* mainWidget) {
    switch(event->event) {
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            mainWidget->resize(event->data1, event->data2);
            puts("Got window size changed event");
            break;
    }
}
}

void SdlUi::Loop(Widget* mainWidget) {
    bool quit = false;
    SDL_Event event;

    while(!quit) {

        while(SDL_PollEvent(&event) != 0) {
            switch(event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_WINDOWEVENT:
                    handleWindowEvent(&event.window, mainWidget);
                    break;
            }
        }

        mainWidget->draw();
        //SDL_Delay(50);
    }
}

void SdlUi::Quit() {
    SDL_Quit();
}
