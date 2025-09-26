#pragma once
#include <SDL.h>

namespace input {

// Call once per frame before polling events
void BeginFrame();

// Feed every SDL_Event polled
void ProcessEvent(const SDL_Event& e);

// Query functions
bool IsDown(SDL_Scancode code);
bool WasPressed(SDL_Scancode code);
bool WasReleased(SDL_Scancode code);

}
