#include "UI/UINoticeConfirmWnd.h"

#include <string>

#include "Common/Globals.h"
#include "Common/const_strings.h"
#include "Files/BitmapRes.h"
#include "UI/UIBitmapButton.h"
#include "UI/UIBmp.h"

CUINoticeConfirmWnd::CUINoticeConfirmWnd(CUIWindowMgr *p_window_mgr)
    : CUIFrameWnd(p_window_mgr), m_textViewer(), m_target(30) {}

void CUINoticeConfirmWnd::OnCreate(int cx, int cy) {
  const std::string resource_path = const_strings::kResourceSubfolder;
  std::string button_name[2][3];
  int ids[2];
  int pos[2][2];

  button_name[0][0] = "btn_ok.bmp";
  button_name[0][1] = "btn_ok_a.bmp";
  button_name[0][2] = "btn_ok_b.bmp";
  button_name[1][0] = "btn_cancel.bmp";
  button_name[1][1] = "btn_cancel_a.bmp";
  button_name[1][2] = "btn_cancel_b.bmp";
  ids[0] = 118;
  ids[1] = 119;
  pos[0][0] = 0xBD;
  pos[0][1] = 0x60;
  pos[1][0] = 0xEA;
  pos[1][1] = 0x60;

  for (int i = 0; i < 2; i++) {
    CUIBitmapButton *btn = new CUIBitmapButton(p_window_mgr_);
    btn->SetBitmapName(resource_path + button_name[i][0], 0);
    btn->SetBitmapName(resource_path + button_name[i][1], 1);
    btn->SetBitmapName(resource_path + button_name[i][2], 2);

    btn->Create(btn->GetBitmapWidth(), btn->GetBitmapHeight());
    btn->Move(pos[i][0], pos[i][1]);
    btn->SetId(ids[i]);
    AddChild(btn);
  }

  CUITextViewer *text_viewer = new CUITextViewer(p_window_mgr_);
  text_viewer->Create2(10, 22, cx - 20, cy - 55, false);
  AddChild(text_viewer);
  // TODO: replace with the correct SendMsg call
  const std::string notice_msg = g_MsgStrMgr->GetMsgStr(MSI_DO_YOU_AGREE);
  text_viewer->AddItem(notice_msg);
}

void CUINoticeConfirmWnd::OnDraw() {
  const std::string filename =
      const_strings::kResourceSubfolder + "win_msgbox.bmp";
  CBitmapRes *bitmap =
      reinterpret_cast<CBitmapRes *>(g_ResMgr->Get(filename, false));

  DrawBitmap(0, 0, bitmap, 0);
}

void *CUINoticeConfirmWnd::SendMsg(CUIWindow *sender, int message,
                                   const void *val1, const void *val2,
                                   const void *val3, const void *val4) {
  void *result = nullptr;

  switch (message) {
    case WM_BUTTON_PRESSED: {
      const size_t btn_id = reinterpret_cast<size_t>(val1);

      // Ok button has been pressed
      if (btn_id == 118) {
        result = g_ModeMgr->GetCurMode()->SendMsg(m_target);
      }
      // Cancel button has been pressed so we quit the current mode
      else if (btn_id == 119) {
        g_ModeMgr->GetCurMode()->SendMsg(MM_QUIT);
      }
    } break;
    case WM_SET_ACTION_BUTTON_OK:
      m_target = reinterpret_cast<size_t>(val1);
      break;
    default:
      result = CUIFrameWnd::SendMsg(sender, message, val1, val2, val3, val4);
  };

  return result;
}
