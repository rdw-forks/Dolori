#include "UI/UINoticeConfirmWnd.h"

#include <string>

#include "Common/Globals.h"
#include "Common/const_strings.h"
#include "Render/BitmapRes.h"
#include "UI/UIBitmapButton.h"
#include "UI/UIBmp.h"

CUINoticeConfirmWnd::CUINoticeConfirmWnd() : m_textViewer(), m_target(30) {}

CUINoticeConfirmWnd::~CUINoticeConfirmWnd() {}

void CUINoticeConfirmWnd::OnCreate(int cx, int cy) {
  const std::string resource_path = const_strings::kResourceSubfolder;
  const char *button_name[2][3];
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
    btn->SetBitmapName((resource_path + button_name[i][0] + ".bmp").c_str(), 0);
    btn->SetBitmapName((resource_path + button_name[i][1] + ".bmp").c_str(), 1);
    btn->SetBitmapName((resource_path + button_name[i][2] + ".bmp").c_str(), 2);

    btn->Create(btn->GetBitmapWidth(), btn->GetBitmapHeight());
    btn->Move(pos[i][0], pos[i][1]);
    btn->SetId(ids[i]);
    AddChild(btn);
  }

  CUITextViewer *text_viewer = new CUITextViewer();
  text_viewer->Create2(10, 22, cx - 20, cy - 55, false);
  AddChild(text_viewer);
  // TODO: replace with the correct SendMsg call
  std::string notice_msg = g_MsgStrMgr->GetMsgStr(MSI_DO_YOU_AGREE);
  text_viewer->AddItem(notice_msg);
}

void CUINoticeConfirmWnd::OnDraw() {
  const std::string filename =
      const_strings::kResourceSubfolder + "win_msgbox.bmp";
  CBitmapRes *bitmap =
      reinterpret_cast<CBitmapRes *>(g_ResMgr->Get(filename.c_str(), false));

  DrawBitmap(0, 0, bitmap, 0);
}

void *CUINoticeConfirmWnd::SendMsg(CUIWindow *sender, int message, void *val1,
                                   void *val2, void *val3, void *val4) {
  void *result = nullptr;

  switch (message) {
    case 6: {
      size_t btn_id = reinterpret_cast<size_t>(val1);

      // Ok button has been pressed
      if (btn_id == 118) {
        result = g_ModeMgr->GetCurMode()->SendMsg(m_target);
      }
      // Cancel button has been pressed so we quit the current mode
      else if (btn_id == 119) {
        g_ModeMgr->GetCurMode()->SendMsg(MM_QUIT);
      }
    } break;
    case 80: {
      size_t btn_id = reinterpret_cast<size_t>(val1);

      m_target = btn_id;
    } break;
    default:
      result = CUIFrameWnd::SendMsg(sender, message, val1, val2, val3, val4);
  };

  return result;
}
