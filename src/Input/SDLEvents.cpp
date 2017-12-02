#include "SDLEvents.h"
#include <SDL.h>
#include "../Common/Globals.h"

void ProcessSDLEvents() {
  SDL_Event ev;

  while (SDL_PollEvent(&ev)) {
    switch (ev.type) {
      case SDL_QUIT:
        g_sys_quit = true;
        return;
      case SDL_MOUSEBUTTONDOWN:
        g_Mouse->SetXPos(ev.button.x);
        g_Mouse->SetYPos(ev.button.y);
        if (ev.button.button == SDL_BUTTON_LEFT)
          g_Mouse->SetLBtn(BTN_DOWN);
        else if (ev.button.button == SDL_BUTTON_RIGHT)
          g_Mouse->SetRBtn(BTN_DOWN);
        else if (ev.button.button == SDL_BUTTON_MIDDLE)
          g_Mouse->SetWBtn(BTN_DOWN);
        break;
      case SDL_MOUSEBUTTONUP:
        g_Mouse->SetXPos(ev.button.x);
        g_Mouse->SetYPos(ev.button.y);
        if (ev.button.button == SDL_BUTTON_LEFT)
          g_Mouse->SetLBtn(BTN_UP);
        else if (ev.button.button == SDL_BUTTON_RIGHT)
          g_Mouse->SetRBtn(BTN_UP);
        else if (ev.button.button == SDL_BUTTON_MIDDLE)
          g_Mouse->SetWBtn(BTN_UP);
        break;
      case SDL_MOUSEMOTION:
        g_Mouse->SetXPos(ev.motion.x);
        g_Mouse->SetYPos(ev.motion.y);
        break;
      case SDL_TEXTINPUT:
        g_Language->AddInput(ev.text.text);
        break;
    };
  }
}