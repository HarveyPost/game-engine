cmake_minimum_required(VERSION 3.31.6 FATAL_ERROR)

project(engine)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# RPATHs (SDL2 + SDL2_ttf)
set(CMAKE_INSTALL_RPATH "/opt/homebrew/opt/sdl2/lib")
set(CMAKE_BUILD_RPATH  "/opt/homebrew/opt/sdl2/lib")
list(APPEND CMAKE_INSTALL_RPATH "/opt/homebrew/opt/sdl2_ttf/lib")
list(APPEND CMAKE_BUILD_RPATH  "/opt/homebrew/opt/sdl2_ttf/lib")

# Your public headers
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

# Engine sources
set(ENGINE_SOURCE
  ${CMAKE_CURRENT_LIST_DIR}/src/core/engine.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/platform/platform_sdl.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/platform/window_sdl.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/render/renderer.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/input/input.cpp
)
add_library(engine STATIC ${ENGINE_SOURCE})

# Test executable
set(TESTING_SOURCE ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp)
add_executable(program ${TESTING_SOURCE})

# Find SDL2 + SDL2_ttf
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Add both include dirs (so <SDL.h> and <SDL_ttf.h> work)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
include_directories(/opt/homebrew/include/SDL2)

# Link SDL2 + SDL2_ttf into the engine (since you use TTF_* in the library)
target_link_libraries(engine
  /opt/homebrew/opt/sdl2/lib/libSDL2.dylib
  /opt/homebrew/opt/sdl2_ttf/lib/libSDL2_ttf.dylib
)

# Link the engine to your program
target_link_libraries(program engine)
