#pragma once
#include <string>

struct SDL_Renderer;
struct TTF_Font;

namespace render {

class Renderer {
public:
    Renderer() = default;
    ~Renderer();

    bool Init(SDL_Renderer* sdlRenderer,
              const char* fontPath = "/System/Library/Fonts/Supplemental/Arial.ttf",
              int fontSize = 24);

    void Clear(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    void DrawTriangleOutline(int x1, int y1, int x2, int y2, int x3, int y3);
    void DrawFpsText(int fps);
    void Present();

private:
    SDL_Renderer* m_Renderer = nullptr;
    TTF_Font* m_Font = nullptr;
};

}
