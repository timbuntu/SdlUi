#include "Window.h"

using namespace SdlUi;


/**
 * Creates a new Window with the given title, dimensions, and position, which optionally frees its childrens
 * Memory on removal.
 *
 * @param title The window title to set
 * @param dim The dimensions of the window
 * @param pos The position of the window
 * @freeChildren Whether children should be deallocated on removal
 */
Window::Window(const char* title, const Vector& dim, const Vector& pos, bool freeChildren)
: Widget(NULL, pos, dim, 0, freeChildren) 
{ 
    this->title = strdup(title);
    this->window = SDL_CreateWindow(title, pos.x, pos.y, dim.x, dim.y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(window) {
        this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(renderer == NULL)
            printf("SdlUi::Window: Couldn't create renderer. SDL_Error: %s\n", SDL_GetError());

    } else {
        printf("SdlUi::Window: Couldn't create window. SDL_Error: %s\n", SDL_GetError());
        this->renderer = NULL;
    }

}

/**
 * Handles specific Window events like SDL_WINDOWEVENT, and passes other events down to its Widgets
 *
 * @param event The SDL_Event to handle
 */
void Window::handleEvent(const SDL_Event* event) {
    if(event->type == SDL_WINDOWEVENT) {
        switch(event->window.event) {
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                this->resize(event->window.data1, event->window.data2);
                break;
        }
    } else
        Widget::handleEvent(event);
}

Window::~Window() {
    SDL_DestroyWindow(window);
    delete[] title;
}
