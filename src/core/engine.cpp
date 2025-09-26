#include "core/engine.h"
#include "platform/platform.h"
#include "platform/window.h"
#include "render/renderer.h"
#include "input/input.h"

#include <SDL2/SDL.h>
#include <iostream>

namespace core {

bool Engine:: initialise() {
    if (!platform::Init()) return false;

    m_Window = platform::CreateWindow("Engine Window", 1280, 960);
    if (!m_Window) return false;

    m_SDLRenderer = platform::CreateRenderer(m_Window);
    if (!m_SDLRenderer) return false;

    m_Renderer = new render::Renderer();
    if (!m_Renderer->Init(m_SDLRenderer)) {
        std::cerr << "Failed to initialise renderer." << std::endl;
        return false;
    }

    if (m_Entities.empty()) {
        m_Entities.push_back({Vec2(640.f, 480.f), Vec2(120.f, 0.f)});
    }

    m_LastFpsSampleTicks = SDL_GetTicks();
    m_LastTicks = SDL_GetPerformanceCounter();
    m_TicksToSeconds = 1.0 / static_cast<double>(SDL_GetPerformanceFrequency());
    m_Accumulator = 0.0;
    std::cout << "Engine initialised successfully.\n";
    return true;
}

void Engine::run()
{
    bool isRunning = true;
    SDL_Event event;

    while (isRunning)
    {
        input::BeginFrame();
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) {
                isRunning  = false;
            } else if (event.type == SDL_WINDOWEVENT &&
                        event.window.event == SDL_WINDOWEVENT_CLOSE) {
                isRunning = false;
            }
            input::ProcessEvent(event);
        }

        // Escapce press to quit
        if (input::WasPressed(SDL_SCANCODE_ESCAPE)) {
            isRunning = false;
        }

        // Time step accumulation
        uint64_t now = SDL_GetPerformanceCounter();
        double frameDt = (now - m_LastTicks) * m_TicksToSeconds;
        m_LastTicks = now;

        if (frameDt > 0.25) frameDt = 0.25;
        m_Accumulator += frameDt;

        // Fixed updates
        while (m_Accumulator >= m_FixedDt) {
            update(m_FixedDt);
            m_Accumulator -= m_FixedDt;
            ++m_UpdatesCounter;
        }

        // Interpolation ratio
        double alpha = m_Accumulator / m_FixedDt;
        (void)alpha; // Currently unused, but can be used for rendering interpolation

        updateFps();

        Uint32 frameStart = SDL_GetTicks();

        m_Renderer->Clear(0, 0, 0, 255); // Clear with black
        
        Vec2 center = m_Entities[0].pos;
        Vec2 a{center.x, center.y - 380.f};
        Vec2 b{center.x - 540.f, center.y + 380.f};
        Vec2 c{center.x + 540.f, center.y + 380.f};
        m_Renderer->DrawTriangleOutline(static_cast<int>(a.x), static_cast<int>(a.y),
                                        static_cast<int>(b.x), static_cast<int>(b.y),
                                        static_cast<int>(c.x), static_cast<int>(c.y));

        m_Renderer->DrawFpsText(static_cast<int>(m_CurrentFps));
        m_Renderer->Present();
        
        if (m_Accumulator < (m_FixedDt * 0.25))
            SDL_Delay(1);
    }
}

void Engine::update(double dt) {
    for (auto& e : m_Entities) {
        e.pos += e.vel * static_cast<float>(dt);

        // Horizontal bounce (keep within window bounds)
        if (e.pos.x < 200.f) { e.pos.x = 200.f; e.vel.x *= -1.f; }
        if (e.pos.x > 1080.f) { e.pos.x = 1080.f; e.vel.x *= -1.f; }
    }
}

void Engine::updateFps() {
    ++m_FrameCounter;
    unsigned nowMs = SDL_GetTicks();
    if (nowMs - m_LastFpsSampleTicks >= 500) {
        m_CurrentFps = static_cast<unsigned>(m_FrameCounter * 1000.0 / (nowMs - m_LastFpsSampleTicks));
        m_CurrentUps = static_cast<unsigned>(m_UpdatesCounter * 1000.0 / (nowMs - m_LastFpsSampleTicks));
        m_FrameCounter = 0;
        m_UpdatesCounter = 0;
        m_LastFpsSampleTicks = nowMs;
    }
}

void Engine::shutdown() {
    if (m_Renderer) { delete m_Renderer; m_Renderer = nullptr; }
    if (m_SDLRenderer) { SDL_DestroyRenderer(m_SDLRenderer); m_SDLRenderer = nullptr; }
    if (m_Window) { SDL_DestroyWindow(m_Window); m_Window = nullptr; }
    platform::Shutdown();
    std::cout << "Engine shutdown completed.\n";
}

void Engine::setWindowTitle(const std::string& title) {
    platform::setWindowTitle(m_Window, title);
}

}
