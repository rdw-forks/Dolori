#include <stdlib.h>
#include "Core/Game.h"

int main(int argc, char* argv[]) {
  Game game;

  if (!game.Initialize()) {
    return EXIT_FAILURE;
  }

  game.Run();
  return EXIT_SUCCESS;
}
