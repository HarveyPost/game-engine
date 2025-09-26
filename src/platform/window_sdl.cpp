#include "platform/window.h"
#include <SDL2/SDL.h>
#include <iostream>

namespace platform {

SDL_Window* CreateWindow(const char* title, int width, int height) {
    SDL_Window* w = SDL_CreateWindow(title,
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          width, height,
                                          SDL_WINDOW_SHOWN);
    if (!w) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
    }
    return w;
}

SDL_Renderer* CreateRenderer(SDL_Window* window) {
    if (!window) return nullptr;
    SDL_Renderer* r = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!r) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
    }
    return r;
}

void setWindowTitle(SDL_Window* window, const std::string& title) {
    if (window) {
        SDL_SetWindowTitle(window, title.c_str());
    }
}

}
