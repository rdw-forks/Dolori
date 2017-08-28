#include "UINoticeConfirmWnd.h"
#include <string>
#include "../Common/Globals.h"
#include "../Render/BitmapRes.h"
#include "UIBitmapButton.h"
#include "UIBmp.h"

CUINoticeConfirmWnd::CUINoticeConfirmWnd() {}

CUINoticeConfirmWnd::~CUINoticeConfirmWnd() {}

void CUINoticeConfirmWnd::OnCreate(int cx, int cy) {
  std::string path_name = "유저인터페이스/";
  char *button_name[2][3];
  int ids[2];
  int pos[2][2];

  button_name[0][0] = "btn_ok";
  button_name[0][1] = "btn_ok_a";
  button_name[0][2] = "btn_ok_b";
  button_name[1][0] = "btn_cancel";
  button_name[1][1] = "btn_cancel_a";
  button_name[1][2] = "btn_cancel_b";
  ids[0] = 118;
  ids[1] = 119;
  pos[0][0] = 0xBD;
  pos[0][1] = 0x60;
  pos[1][0] = 0xEA;
  pos[1][1] = 0x60;

  for (int i = 0; i < 2; i++) {
    CUIBitmapButton *btn = new CUIBitmapButton();
    btn->SetBitmapName((path_name + button_name[i][0] + ".bmp").c_str(),
                       BTN_NONE);
    btn->SetBitmapName((path_name + button_name[i][1] + ".bmp").c_str(),
                       BTN_DOWN);
    btn->SetBitmapName((path_name + button_name[i][2] + ".bmp").c_str(),
                       BTN_PRESSED);

    btn->Create(btn->GetBitmapWidth(), btn->GetBitmapHeight());
    btn->Move(pos[i][0], pos[i][1]);
    btn->SetId(ids[i]);
    AddChild(btn);
  }
}

void CUINoticeConfirmWnd::OnDraw() {
  const char *filename;
  CBitmapRes *bitmap;

  filename = UIBmp("유저인터페이스/win_msgbox.bmp");
  bitmap = (CBitmapRes *)g_ResMgr->Get(filename, false);
  DrawBitmap(0, 0, bitmap, 0);
}

int CUINoticeConfirmWnd::SendMsg(CUIWindow *sender, int message, int val1,
                                 int val2, int val3, int val4) {
  int result;

  if (message == 6) {
    if (val1 == 118) {
      // g_ModeMgr->GetCurMode()->SendMsg(g_ModeMgr->GetCurMode(), m_target, 0,
      // 0,
      //                                 0);
    } else if (val1 == 119) {
      // g_ModeMgr->GetCurMode()->SendMsg(2, 0, 0, 0);
      return 0;
    }
    result = 0;
  } else if (message == 80) {
    result = 0;
    m_target = val1;
  } else {
    CUIFrameWnd *frame_wnd = this;
    // result = frame_wnd->SendMsg(sender, message, val1, val2, val3, val4);
  }
  return result;
}
