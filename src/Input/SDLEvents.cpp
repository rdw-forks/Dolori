#include "Input/SDLEvents.h"

#include <SDL.h>

#include "Common/Globals.h"

void ProcessSDLEvents(CUIWindowMgr* p_window_mgr) {
  SDL_Event ev;

  g_Mouse->SetWheel(0);

  while (SDL_PollEvent(&ev) != 0) {
    switch (ev.type) {
      case SDL_QUIT:
        g_sys_quit = true;
        return;
      case SDL_MOUSEBUTTONDOWN:
        g_Mouse->SetXPos(ev.button.x);
        g_Mouse->SetYPos(ev.button.y);

        if (ev.button.button == SDL_BUTTON_LEFT) {
          g_Mouse->SetLBtn(CMouse::ButtonState::kDown);
        } else if (ev.button.button == SDL_BUTTON_RIGHT) {
          g_Mouse->SetRBtn(CMouse::ButtonState::kDown);
        } else if (ev.button.button == SDL_BUTTON_MIDDLE) {
          g_Mouse->SetWBtn(CMouse::ButtonState::kDown);
        }
        break;
      case SDL_MOUSEBUTTONUP:
        g_Mouse->SetXPos(ev.button.x);
        g_Mouse->SetYPos(ev.button.y);

        if (ev.button.button == SDL_BUTTON_LEFT) {
          g_Mouse->SetLBtn(CMouse::ButtonState::kUp);
        } else if (ev.button.button == SDL_BUTTON_RIGHT) {
          g_Mouse->SetRBtn(CMouse::ButtonState::kUp);
        } else if (ev.button.button == SDL_BUTTON_MIDDLE) {
          g_Mouse->SetWBtn(CMouse::ButtonState::kUp);
        }
        break;
      case SDL_MOUSEMOTION:
        g_Mouse->SetXPos(ev.motion.x);
        g_Mouse->SetYPos(ev.motion.y);
        break;
      case SDL_MOUSEWHEEL:
        g_Mouse->SetWheel(ev.wheel.y);
        break;
      case SDL_KEYDOWN:
        if (p_window_mgr->ProcessPushButton(ev.key.keysym.sym, 1,
                                            ev.key.keysym.scancode)) {
          return;
        }

        if (p_window_mgr->IsFocusChatWnd()) {
          p_window_mgr->ExecuteMsgInBattleMode(ev.key.keysym.sym, 1);
        }
        break;
      case SDL_TEXTINPUT:
        g_Language->AddInput(ev.text.text);
        break;
    };
  }
}
