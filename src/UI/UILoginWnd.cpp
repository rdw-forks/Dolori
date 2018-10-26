#include "UI/UILoginWnd.h"

#include "Common/Globals.h"
#include "Common/const_strings.h"
#include "Common/service_type.h"
#include "Files/File.h"
#include "UI/UIBmp.h"

CUILoginWnd::CUILoginWnd(CUIWindowMgr *p_window_mgr)
    : CUIFrameWnd(p_window_mgr),
      m_login(),
      m_password(),
      m_cancel_button(),
      m_isCheckOn(),
      m_isGravity(1),
      m_isHangame(),
      m_classText() {
  m_defPushId = 117;
  m_defCancelPushId = 117;
}

void CUILoginWnd::OnCreate(int cx, int cy) {
  const std::string path_name = const_strings::kResourceSubfolder;
  const char *button_name[5][3];
  int button_count;
  int pos[5][2];
  int ids[5];

  button_name[0][0] = "login_interface/btn_connect";
  button_name[0][1] = "login_interface/btn_connect_a";
  button_name[0][2] = "login_interface/btn_connect_b";
  button_name[1][0] = "login_interface/btn_exit";
  button_name[1][1] = "login_interface/btn_exit_a";
  button_name[1][2] = "login_interface/btn_exit_b";
  button_name[2][0] = "btn_cancel";
  button_name[2][1] = "btn_cancel_a";
  button_name[2][2] = "btn_cancel_b";
  button_name[3][0] = "login_interface/btn_request";
  button_name[3][1] = "login_interface/btn_request_a";
  button_name[3][2] = "login_interface/btn_request_b";
  button_name[4][0] = "btn_intro";
  button_name[4][1] = "btn_intro_a";
  button_name[4][2] = "btn_intro_b";
  ids[0] = 120;
  ids[1] = 155;
  ids[2] = 119;
  ids[3] = 201;
  ids[4] = 219;
  pos[0][0] = 0xBD;
  pos[0][1] = 0x60;
  pos[1][0] = 0xEA;
  pos[1][1] = 0x60;
  pos[2][0] = 0x1B2;
  pos[2][1] = 0x60;
  pos[3][0] = 0x4;
  pos[3][1] = 0x60;
  pos[4][0] = 0x89;
  pos[4][1] = 0x60;

  if (CFile::IsFileExist("../openning.bik"))
    button_count = 5;
  else
    button_count = 4;

  for (int i = 0; i < button_count; i++) {
    if (i == 3 && g_serviceType != ServiceType::kKorea &&
        g_serviceType != ServiceType::kChina &&
        g_serviceType != ServiceType::kGermany &&
        g_serviceType != ServiceType::kIndia &&
        g_serviceType != ServiceType::kAustralia &&
        g_serviceType != ServiceType::kRussia) {
      break;
    }

    CUIBitmapButton *button = new CUIBitmapButton(p_window_mgr_);

    button->SetBitmapName((path_name + button_name[i][0] + ".bmp").c_str(), 0);
    button->SetBitmapName((path_name + button_name[i][1] + ".bmp").c_str(), 1);
    button->SetBitmapName((path_name + button_name[i][2] + ".bmp").c_str(), 2);

    button->Create(button->GetBitmapWidth(), button->GetBitmapHeight());
    button->Move(pos[i][0], pos[i][1]);
    button->SetId(ids[i]);
    AddChild(button);

    if (ids[i] == 119) {
      m_cancel_button = button;
    }
  }

  CUIEditCtrl *login = new CUIEditCtrl(p_window_mgr_);
  m_login = login;
  login->Create(125, 16);
  login->Move(92, 30);
  login->SetFrameColor(242, 242, 242);
  AddChild(login);

  CUIEditCtrl *password = new CUIEditCtrl(p_window_mgr_);
  m_password = password;
  password->Create(125, 16);
  password->Move(92, 62);
  password->SetFrameColor(242, 242, 242);
  password->HideChars(true);
  AddChild(password);
}

void CUILoginWnd::OnDraw() {
  const std::string res_path = []() {
    if (g_serviceType != ServiceType::kKorea) {
      return const_strings::kResourceSubfolder +
             "login_interface/win_login.bmp";
    } else if (g_isGravityID) {
      return const_strings::kResourceSubfolder +
             "login_interface/win_login_K2.bmp";
    } else {
      return const_strings::kResourceSubfolder +
             "login_interface/win_login_K1.bmp";
    }
  }();

  CBitmapRes *res =
      static_cast<CBitmapRes *>(g_ResMgr->Get(UIBmp(res_path), false));
  DrawBitmap(0, 0, res, 0);
}

void *CUILoginWnd::SendMsg(CUIWindow *sender, int message, void *val1,
                           void *val2, void *val3, void *val4) {
  void *result = nullptr;

  switch (message) {
    case 6: {
      size_t btn_id = reinterpret_cast<size_t>(val1);

      if (btn_id == 201) {
        if (g_isGravityID || g_serviceType != ServiceType::kKorea) {
          g_ModeMgr->Quit();
        } else {
          const auto error_msg = g_MsgStrMgr->GetMsgStr(MSI_3DAY_FREE);
          if (p_window_mgr_->ErrorMsg(error_msg, 2, 1, 0, 0) != 121) {
            return nullptr;
          }
          g_ModeMgr->Quit();
        }
      } else if (btn_id == 155) {
        // UILoginWnd::WriteToReg(this);
        const auto error_msg =
            g_MsgStrMgr->GetMsgStr(MSI_DO_YOU_REALLY_WANT_TO_QUIT);
        if (p_window_mgr_->ErrorMsg(error_msg, 2, 1, 0, 0) != 121) {
          return nullptr;
        }

        g_ModeMgr->GetCurMode()->SendMsg(MM_QUIT);
        p_window_mgr_->PostQuit(this);
      } else if (btn_id == 120) {
        // PlayWave(waveFileName, 0.0, 0.0, 0.0, 250, 40, 1.0);
        g_ModeMgr->GetCurMode()->SendMsg(
            LMM_PASSWORD,
            static_cast<const void *>(m_password->GetText().c_str()));
        g_ModeMgr->GetCurMode()->SendMsg(
            LMM_ID, static_cast<const void *>(m_login->GetText().c_str()));
        g_ModeMgr->GetCurMode()->SendMsg(LMM_CONNECT_TO_ACSVR);
        p_window_mgr_->PostQuit(this);
      }
    } break;
  };

  return result;
}
