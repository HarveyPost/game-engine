#include "core/engine.h"
#include <iostream>

int main() {
  core::Engine engine;
  if (!engine.initialise()) {
    std::cerr << "Engine failed to initialise." << std::endl;
    return 1;
  }
  engine.run();
  engine.shutdown();

  return 0;
}
