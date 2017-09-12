#include "UINoticeConfirmWnd.h"
#include <string>
#include "../Common/Globals.h"
#include "../Render/BitmapRes.h"
#include "UIBitmapButton.h"
#include "UIBmp.h"

CUINoticeConfirmWnd::CUINoticeConfirmWnd() { m_target = 30; }

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
    btn->SetBitmapName((path_name + button_name[i][0] + ".bmp").c_str(), 0);
    btn->SetBitmapName((path_name + button_name[i][1] + ".bmp").c_str(), 1);
    btn->SetBitmapName((path_name + button_name[i][2] + ".bmp").c_str(), 2);

    btn->Create(btn->GetBitmapWidth(), btn->GetBitmapHeight());
    btn->Move(pos[i][0], pos[i][1]);
    btn->SetId(ids[i]);
    AddChild(btn);
  }

  CUITextViewer *text_viewer = new CUITextViewer();
  text_viewer->Create2(10, 22, cx - 20, cy - 55, false);
  AddChild(text_viewer);
  // TODO: replace with the correct SendMsg call
  text_viewer->AddItem(g_MsgStrMgr->GetMsgStr(MSI_DO_YOU_AGREE));
}

void CUINoticeConfirmWnd::OnDraw() {
  const char *filename;
  CBitmapRes *bitmap;

  filename = UIBmp("유저인터페이스/win_msgbox.bmp");
  bitmap = (CBitmapRes *)g_ResMgr->Get(filename, false);
  DrawBitmap(0, 0, bitmap, 0);
}

int CUINoticeConfirmWnd::SendMsg(CUIWindow *sender, int message, void *val1,
                                 void *val2, void *val3, void *val4) {
  int result = 0;

  switch (message) {
    case 6: {
      int btn_id = (int)val1;

      // Ok button has been pressed
      if (btn_id == 118)
        result = g_ModeMgr->GetCurMode()->SendMsg(m_target, 0, 0, 0);
      // Cancel button has been pressed so we quit the current mode
      else if (btn_id == 119)
        g_ModeMgr->GetCurMode()->SendMsg(MM_QUIT, 0, 0, 0);
    } break;
    case 80:
      m_target = (int)val1;
      break;
    default:
      result = CUIFrameWnd::SendMsg(sender, message, val1, val2, val3, val4);
  };

  return result;
}
