#ifndef SDLUI_WINDOW
#define SDLUI_WINDOW

#include "Widget.h"
#include <cstring>

#define SDLUI_WIN_DEFAULT_WIDTH  640
#define SDLUI_WIN_DEFAULT_HEIGHT 480

namespace SdlUi {
    
    class Window : public Widget {
        public:
            Window(
                const char* title,
                const Vector& dim = Vector(SDLUI_WIN_DEFAULT_WIDTH, SDLUI_WIN_DEFAULT_HEIGHT),
                const Vector& pos = Vector(0,0)
            );

            virtual bool isValid() const { return window && surface; }
            virtual ~Window();

        protected:
            virtual SDL_Renderer* getRenderer() const { return renderer; }

        private:
            const char*   title;
            SDL_Window*   window;
            SDL_Surface*  surface;
            SDL_Renderer* renderer;
    };
}

#endif
