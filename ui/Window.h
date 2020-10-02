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
                const Vector& pos = Vector(0,0),
                bool freeChildren = false
            );

            virtual void handleEvent(const SDL_Event*) override;
            virtual bool isValid() const override { return window && renderer; }
            virtual ~Window();

        protected:
            virtual SDL_Renderer* getRenderer() const override { return renderer; }

        private:
            const char*   title;
            SDL_Window*   window;
            SDL_Renderer* renderer;
    };
}

#endif
