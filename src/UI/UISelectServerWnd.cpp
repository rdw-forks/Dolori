#include "UISelectServerWnd.h"
#include "Common/Globals.h"
#include "Common/const_strings.h"
#include "UIBmp.h"
#include "UIServerListBox.h"

CUISelectServerWnd::CUISelectServerWnd(CUIWindowMgr *p_window_mgr)
    : CUIFrameWnd(p_window_mgr) {}

void CUISelectServerWnd::OnCreate(int cx, int cy) {
  const std::string path_name = const_strings::kResourceSubfolder;
  const char *button_name[3][3];
  int pos[3][2];
  int ids[3];

  CUIServerListBox *server_list = new CUIServerListBox(p_window_mgr_);
  m_serverList = server_list;
  m_serverList->Create2(12, 22, cx - 24, cy - 55, false);
  m_serverList->SetColor(240, 240, 240);
  m_serverList->SetId(118);
  AddChild(m_serverList);

  button_name[0][0] = "btn_ok";
  button_name[0][1] = "btn_ok_a";
  button_name[0][2] = "btn_ok_b";
  button_name[1][0] = "btn_cancel";
  button_name[1][1] = "btn_cancel_a";
  button_name[1][2] = "btn_cancel_b";
  button_name[2][0] = "login_interface/btn_exit";
  button_name[2][1] = "login_interface/btn_exit_a";
  button_name[2][2] = "login_interface/btn_exit_b";
  ids[0] = 118;
  ids[1] = 119;
  ids[2] = 155;
  pos[0][0] = 189;
  pos[0][1] = cy - 24;
  pos[1][0] = 234;
  pos[1][1] = cy - 24;
  pos[2][0] = 434;
  pos[2][1] = cy - 24;

  for (int i = 0; i < 3; i++) {
    CUIBitmapButton *btn = new CUIBitmapButton(p_window_mgr_);
    btn->SetBitmapName((path_name + button_name[i][0] + ".bmp").c_str(), 0);
    btn->SetBitmapName((path_name + button_name[i][1] + ".bmp").c_str(), 1);
    btn->SetBitmapName((path_name + button_name[i][2] + ".bmp").c_str(), 2);

    btn->Create(btn->GetBitmapWidth(), btn->GetBitmapHeight());
    btn->Move(pos[i][0], pos[i][1]);
    btn->SetId(ids[i]);
    AddChild(btn);

    if (ids[i] == 155) m_exitButton = btn;
  }
}

void CUISelectServerWnd::OnDraw() {
  const std::string filename =
      const_strings::kResourceSubfolder + "login_interface/win_service.bmp";
  CBitmapRes *bitmap;

  bitmap = (CBitmapRes *)g_ResMgr->Get(UIBmp(filename), false);
  DrawBitmap(0, 0, bitmap, 0);

  // Below is the original code used to make the window taller (280x200)
  // filename = UIBmp("유저인터페이스/basic_interface/btnbar_left2.bmp");
  // bitmap = (CBitmapRes *)g_ResMgr->Get(filename, false);
  // DrawBitmap(0, m_h - bitmap->GetHeight(), bitmap, 0);

  // filename = UIBmp("유저인터페이스/basic_interface/btnbar_right2.bmp");
  // bitmap = (CBitmapRes *)g_ResMgr->Get(filename, false);
  // DrawBitmap(m_w - bitmap->GetWidth(), m_h - bitmap->GetHeight(), bitmap, 0);

  // filename = UIBmp("유저인터페이스/basic_interface/btnbar_mid2.bmp");
  // bitmap = (CBitmapRes *)g_ResMgr->Get(filename, false);
  // int nb_of_elements =
  //    (m_w - 42) / 21 + ((m_w - 42) % 21 != 0);
  // int pos_x = 21;
  // for (int i = 0; i < nb_of_elements; i++) {
  //  DrawBitmap(pos_x, m_h - bitmap->GetHeight(), bitmap, 0);
  //  pos_x += 21;
  // }
}

void CUISelectServerWnd::AddServer(const char *server) {
  m_serverList->AddItem(server);
}

void *CUISelectServerWnd::SendMsg(CUIWindow *sender, int message, void *val1,
                                  void *val2, void *val3, void *val4) {
  void *result = NULL;

  switch (message) {
    case WM_SET_ACTION_BUTTON_OK:
      m_target = (size_t)val1;
      // TODO: Save selected item num
      break;
    case WM_BUTTON_PRESSED: {
      size_t btn_id = (size_t)val1;

      if (btn_id == 118) {
        if (m_serverList->GetSelected() == -1) break;
        p_window_mgr_->PostQuit(this);
        g_ModeMgr->GetCurMode()->SendMsg(
            m_target, (void *)m_serverList->GetSelected(), 0, 0);
      } else if (btn_id == 119) {
        p_window_mgr_->PostQuit(this);
        g_ModeMgr->GetCurMode()->SendMsg(LMM_CANCEL, 0, 0, 0);
      }
      // else
      //{
      //  if (btn_id != 155)
      //    return 0;
      //  v14 = MsgStr(MSI_DO_YOU_REALLY_WANT_TO_QUIT);
      //  if (UIWindowMgr::ErrorMsg(&g_windowMgr, v14, 2, 1, 0, 0) != 121)
      //    return 0;
      //  ((void(__stdcall *)(signed int, _DWORD, _DWORD,
      //  _DWORD))g_modeMgr.m_curMode->vfptr->SendMsg)(2, 0, 0, 0);
      //  UIWindowMgr::PostQuit(&g_windowMgr, (UIWindow *)&v7->vfptr);
      //}
    } break;
  };

  return result;
}
