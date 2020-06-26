#include "Window.h"

using namespace SdlUi;


Window::Window(const char* title, const Vector& dim, const Vector& pos)
: Widget(dim, pos) 
{ 
    this->title = strdup(title);
    this->window = SDL_CreateWindow(title, pos.x, pos.y, dim.x, dim.y, SDL_WINDOW_SHOWN);
    if(window) {
        this->surface = SDL_GetWindowSurface(window);
        SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
        SDL_UpdateWindowSurface(window);
    } else {
        printf("SdlUi::Window: Couldn't create window. SDL_Error: %s\n", SDL_GetError());
        this->surface = NULL;
    }

}

Window::~Window() {
    SDL_DestroyWindow(window);
    delete[] title;
}
