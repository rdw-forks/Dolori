#ifndef DOLORI_CORE_GAME_H_
#define DOLORI_CORE_GAME_H_

#include "Session.h"

class Game {
 public:
  ~Game();

  bool Initialize();
  void Run();

 private:
};

#endif /* DOLORI_CORE_GAME_H_ */