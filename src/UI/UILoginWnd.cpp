#include "UILoginWnd.h"
#include "../Common/Globals.h"
#include "../Common/service_type.h"
#include "../Files/File.h"
#include "UIBmp.h"

CUILoginWnd::CUILoginWnd() {
  m_defPushId = 117;
  m_defCancelPushId = 117;
  m_startGlobalX = 0;
  m_startGlobalY = 0;
  m_login = NULL;
  m_password = NULL;
  m_cancelButton = NULL;
  m_isCheckOn = 0;
  m_isHangame = 0;
  m_classText = NULL;
  m_isGravity = 1;
}

CUILoginWnd::~CUILoginWnd() {}

void CUILoginWnd::OnCreate(int cx, int cy) {
  std::string path_name = "유저인터페이스/";
  char *button_name[5][3];
  int button_count;
  int pos[5][2];
  int ids[5];

  button_name[0][0] = "btn_connect";
  button_name[0][1] = "btn_connect_a";
  button_name[0][2] = "btn_connect_b";
  button_name[1][0] = "btn_exit";
  button_name[1][1] = "btn_exit_a";
  button_name[1][2] = "btn_exit_b";
  button_name[2][0] = "btn_cancel";
  button_name[2][1] = "btn_cancel_a";
  button_name[2][2] = "btn_cancel_b";
  button_name[3][0] = "btn_request";
  button_name[3][1] = "btn_request_a";
  button_name[3][2] = "btn_request_b";
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
    if (i == 3 && g_serviceType != ServiceKorea &&
        g_serviceType != ServiceChina && g_serviceType != ServiceGermany &&
        g_serviceType != ServiceIndia && g_serviceType != ServiceAustralia &&
        g_serviceType != ServiceRussia)
      break;

    CUIBitmapButton *button = new CUIBitmapButton();

    button->SetBitmapName((path_name + button_name[i][0] + ".bmp").c_str(), 0);
    button->SetBitmapName((path_name + button_name[i][1] + ".bmp").c_str(), 1);
    button->SetBitmapName((path_name + button_name[i][2] + ".bmp").c_str(), 2);

    button->Create(button->GetBitmapWidth(), button->GetBitmapHeight());
    button->Move(pos[i][0], pos[i][1]);
    button->SetId(ids[i]);
    AddChild(button);

    if (ids[i] == 119) m_cancelButton = button;
  }

  CUIEditCtrl *login = new CUIEditCtrl();
  m_login = login;
  login->Create(125, 16);
  login->Move(92, 30);
  login->SetFrameColor(242, 242, 242);
  AddChild(login);

  CUIEditCtrl *password = new CUIEditCtrl();
  m_password = password;
  password->Create(125, 16);
  password->Move(92, 62);
  password->SetFrameColor(242, 242, 242);
  AddChild(password);
}

void CUILoginWnd::OnDraw() {
  const char *res_name;

  if (g_serviceType != ServiceKorea) {
    res_name = UIBmp("유저인터페이스/login_interface/win_login.bmp");
  } else {
    if (g_isGravityID)
      res_name = UIBmp("유저인터페이스/login_interface/win_login_K2.bmp");
    else
      res_name = UIBmp("유저인터페이스/login_interface/win_login_K1.bmp");
  }
  CBitmapRes *res = (CBitmapRes *)g_ResMgr->Get(res_name, false);
  DrawBitmap(0, 0, res, 0);
}

int CUILoginWnd::SendMsg(CUIWindow *sender, int message, void *val1, void *val2,
                         void *val3, void *val4) {
  int result = 0;

  switch (message) {
    case 6: {
      int btn_id = (int)val1;

      if (btn_id == 201) {
        if (g_isGravityID || g_serviceType != ServiceKorea) {
          g_ModeMgr->Quit();
        } else {
          // v12 = MsgStr(MSI_3DAY_FREE);
          // if (UIWindowMgr::ErrorMsg(&g_windowMgr, v12, 2, 1, 0, 0) != 121)
          //  return 0;
          g_ModeMgr->Quit();
        }
      } else if (btn_id == 155) {
        // UILoginWnd::WriteToReg(this);
        // v19 = MsgStr(MSI_DO_YOU_REALLY_WANT_TO_QUIT);
        // if (UIWindowMgr::ErrorMsg(&g_windowMgr, v19, 2, 1, 0, 0) != 121)
        //  return 0;
        g_ModeMgr->GetCurMode()->SendMsg(MM_QUIT, 0, 0, 0);
        g_WindowMgr->PostQuit(this);
      } else if (btn_id == 120) {
        // PlayWave(waveFileName, 0.0, 0.0, 0.0, 250, 40, 1.0);
        g_ModeMgr->GetCurMode()->SendMsg(LMM_PASSWORD,
                                         (void *)m_password->GetText(), 0, 0);
        g_ModeMgr->GetCurMode()->SendMsg(LMM_ID, (void *)m_login->GetText(), 0,
                                         0);
        g_ModeMgr->GetCurMode()->SendMsg(LMM_CONNECT_TO_ACSVR, 0, 0, 0);
        g_WindowMgr->PostQuit(this);
      }
    } break;
  };

  return result;
}
