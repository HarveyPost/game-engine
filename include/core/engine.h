#pragma once
#include <string>
#include <cstdint>
#include <vector>
#include "math/vec2.h"

// Forward declarations
struct SDL_Window;
struct SDL_Renderer;

namespace render { class Renderer; }

namespace core {

class Engine {
public:
    Engine() = default;
    bool initialise();
    void run();
    void shutdown();
    void setWindowTitle(const std::string& title);

private:
    struct Entity {
        Vec2 pos;
        Vec2 vel;
    };
    std::vector<Entity> m_Entities;

    void updateFps();
    void update(double dt);

    // Timestep values
    double m_Accumulator = 0.0;
    double m_FixedDt = 1.0 / 60.0;
    uint64_t m_LastTicks = 0;
    double m_TicksToSeconds = 0.0;

    // UPS tracking
    unsigned m_UpdatesCounter = 0;
    unsigned m_CurrentUps = 0;

    SDL_Window *m_Window = nullptr;
    SDL_Renderer *m_SDLRenderer = nullptr;
    render::Renderer* m_Renderer = nullptr;

    // FPS tracking
    unsigned m_FrameCounter = 0;
    unsigned m_CurrentFps = 0.0f;
    unsigned m_LastFpsSampleTicks = 0;
    bool m_Running = false;
};

}
