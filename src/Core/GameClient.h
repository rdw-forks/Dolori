#ifndef DOLORI_CORE_GAMECLIENT_H_
#define DOLORI_CORE_GAMECLIENT_H_

#include "Session.h"

class GameClient {
 public:
  ~GameClient();

  bool Initialize();
  void Run();

 private:
  bool LoadConfiguration(const std::string& file_name);

 private:
  bool full_screen_;
  int window_width_;
  int window_height_;
};

#endif /* DOLORI_CORE_GAMECLIENT_H_ */
