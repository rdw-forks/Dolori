#include "ErrorMsg.h"
#include <SDL.h>

void ErrorMsg(const char* msg) {
  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", msg, NULL);
}