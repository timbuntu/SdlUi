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

        void Loop(Widget* mainWidget) {
            bool quit = false;
            SDL_Event event;

            while(!quit) {

                while(SDL_PollEvent(&event) != 0) {
                    if(event.type == SDL_QUIT)
                        quit = true;
                }

                mainWidget->draw();
                //SDL_Delay(50);
            }
        }

        void Quit() {
            SDL_Quit();
        }


}
#endif
