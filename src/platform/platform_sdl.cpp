#include "platform/platform.h"
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <iostream>

namespace platform {

bool Init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialise SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() < 0) {
        std::cerr << "Failed to initialise SDL_ttf: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    return true;
}

void Shutdown() {
    TTF_Quit();
    SDL_Quit();
}

}
