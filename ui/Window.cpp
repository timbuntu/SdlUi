#include "Window.h"

using namespace SdlUi;


Window::Window(const char* title, const Vector& dim, const Vector& pos)
: Widget(NULL, dim, pos) 
{ 
    this->title = strdup(title);
    this->window = SDL_CreateWindow(title, pos.x, pos.y, dim.x, dim.y, SDL_WINDOW_SHOWN);
    if(window) {
        this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(renderer == NULL)
            printf("SdlUi::Window: Couldn't create renderer. SDL_Error: %s\n", SDL_GetError());

    } else {
        printf("SdlUi::Window: Couldn't create window. SDL_Error: %s\n", SDL_GetError());
        this->renderer = NULL;
    }

}

Window::~Window() {
    SDL_DestroyWindow(window);
    delete[] title;
}
