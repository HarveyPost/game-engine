#include "render/renderer.h"
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <iostream>

namespace render {

Renderer::~Renderer() {
    if (m_Font) {
        TTF_CloseFont(m_Font);
        m_Font = nullptr;
    }
}

bool Renderer::Init(SDL_Renderer* sdlRenderer,
                    const char* fontPath,
                    int fontSize) {
    m_Renderer = sdlRenderer;
    if (!m_Renderer) return false;
    m_Font = TTF_OpenFont(fontPath, fontSize);
    return m_Font != nullptr;
}

void Renderer::Clear(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
    SDL_RenderClear(m_Renderer);
}

void Renderer::DrawTriangleOutline(int x1, int y1, int x2, int y2, int x3, int y3) {
    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(m_Renderer, x1, y1, x2, y2);
    SDL_RenderDrawLine(m_Renderer, x2, y2, x3, y3);
    SDL_RenderDrawLine(m_Renderer, x3, y3, x1, y1);
}

void Renderer::DrawFpsText(int fps) {
    if (!m_Font) return;
    std::string text = "FPS: " + std::to_string(fps);
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* surf = TTF_RenderText_Solid(m_Font, text.c_str(), white);
    if (!surf) return;
    SDL_Texture* tex = SDL_CreateTextureFromSurface(m_Renderer, surf);
    if (tex) {
        SDL_Rect dst{10, 10, surf->w, surf->h};
        SDL_RenderCopy(m_Renderer, tex, nullptr, &dst);
        SDL_DestroyTexture(tex);
    }
    SDL_FreeSurface(surf);
}

void Renderer::Present() {
    SDL_RenderPresent(m_Renderer);
}

}
