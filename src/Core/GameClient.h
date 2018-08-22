#ifndef DOLORI_CORE_GAMECLIENT_H_
#define DOLORI_CORE_GAMECLIENT_H_

#include "Session.h"

class GameClient {
 public:
  ~GameClient();

  bool Initialize();
  void Run();

 private:
};

#endif /* DOLORI_CORE_GAMECLIENT_H_ */
