#include <stdlib.h>

#include "Common/debug.h"
#include "Core/Game.h"

int main(int argc, char* argv[]) {
#ifdef DOLORI_DEBUG
  spdlog::get(DOLORI_LOGGER_NAME)->set_level(spdlog::level::debug);
#endif

  Game game;

  if (!game.Initialize()) {
    return EXIT_FAILURE;
  }

  game.Run();

  return EXIT_SUCCESS;
}
