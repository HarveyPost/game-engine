#pragma once
#include <string>

struct SDL_Window;
struct SDL_Renderer;

namespace platform {
SDL_Window* CreateWindow(const char* title, int width, int height);
SDL_Renderer* CreateRenderer(SDL_Window* window);
void setWindowTitle(SDL_Window* window, const std::string& title);
}
