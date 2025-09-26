#include "input/input.h"
#include <cstring>

namespace {
    bool g_Current[SDL_NUM_SCANCODES]{};
    bool g_Previous[SDL_NUM_SCANCODES]{};
}

namespace input {

void BeginFrame() {
    std::memcpy(g_Previous, g_Current, sizeof(g_Current));
}

void ProcessEvent(const SDL_Event& e) {
    switch (e.type) {
    case SDL_KEYDOWN:
        if (!e.key.repeat)
            g_Current[e.key.keysym.scancode] = true;
        break;
    case SDL_KEYUP:
        g_Current[e.key.keysym.scancode] = false;
        break;
    default:
        break;
    }
}

bool IsDown(SDL_Scancode code) {
    return g_Current[code];
}
bool WasPressed(SDL_Scancode code) {
    return g_Current[code] && !g_Previous[code];
}
bool WasReleased(SDL_Scancode code) {
    return !g_Current[code] && g_Previous[code];
}

}
