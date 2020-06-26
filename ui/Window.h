#ifndef UI_WINDOW
#define UI_WINDOW

#include "Widget.h"
#include <cstring>

#define UI_WIN_DEFAULT_WIDTH  640
#define UI_WIN_DEFAULT_HEIGHT 480

namespace SdlUi {
    
    class Window : public Widget {
        public:
            Window(
                const char* title,
                const Vector& dim = Vector(UI_WIN_DEFAULT_WIDTH, UI_WIN_DEFAULT_HEIGHT),
                const Vector& pos = Vector(0,0)
            );

            virtual bool isValid() const { return window && surface; }
            virtual ~Window();

        private:
            const char* title;
            SDL_Window* window;
            SDL_Surface* surface;
    };
}

#endif
