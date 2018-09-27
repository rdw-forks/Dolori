#include "UI/UIMakeCharWnd.h"

#include "Common/Globals.h"
#include "Common/MsgStrMgr.h"
#include "Common/const_strings.h"
#include "UI/UIBmp.h"

CUIMakeCharWnd::CUIMakeCharWnd()
    : m_charInfo(), m_charInfo2(), m_viewChar(), m_viewChar2(), m_text() {
  m_charInfo.head_style = 1;
  m_charInfo.job = 4;
  m_charInfo.base_level = 1;
  m_charInfo.status_points = 1;
  m_charInfo.max_hp = 100;
  m_charInfo.hp = 100;
  m_charInfo.max_sp = 100;
  m_charInfo.sp = 100;
  m_charInfo.str = 5;
  m_charInfo.agi = 5;
  m_charInfo.vit = 5;
  m_charInfo.int_ = 5;
  m_charInfo.dex = 5;
  m_charInfo.luk = 5;
}

void CUIMakeCharWnd::OnCreate(int x, int y) {
  g_ModeMgr->GetCurMode()->SendMsg(LMM_GET_MAKING_CHAR_NAME, 0, 0, 0);

  const std::string bitmap_name =
      const_strings::kResourceSubfolder + "login_interface/name-edit.bmp";

  for (int i = 0; i < 6; i++) {
    m_text[i] = new CUIStaticText();
    m_text[i]->Create(90, 15);
    m_text[i]->Move(144 * (i / 6) + 490, 16 * (i % 6) + 40);
    AddChild(m_text[i]);
  }
  InitTextControls();

  m_nameEditCtrl = new CUIBitmapEditCtrl();
  m_nameEditCtrl->SetBitmap(bitmap_name);
  m_nameEditCtrl->Create(m_nameEditCtrl->GetWidth(),
                         m_nameEditCtrl->GetHeight());
  m_nameEditCtrl->Move(62, 244);
  m_nameEditCtrl->SetTextLimit(24);
  m_nameEditCtrl->SetId(118);
  AddChild(m_nameEditCtrl);
  MakeButton();
  g_WindowMgr->SetFocusEdit(m_nameEditCtrl);
  m_defPushId = 118;
}

void CUIMakeCharWnd::OnDraw() {
  const std::string filename =
      const_strings::kResourceSubfolder + "login_interface/win_make.bmp";

  auto bitmap =
      static_cast<CBitmapRes *>(g_ResMgr->Get(UIBmp(filename), false));
  DrawBitmap(0, 0, bitmap, 0);
}

void CUIMakeCharWnd::InitTextControls() {
  m_text[0]->SetText(std::to_string(m_charInfo.str), false);
  m_text[1]->SetText(std::to_string(m_charInfo.agi), false);
  m_text[2]->SetText(std::to_string(m_charInfo.vit), false);
  m_text[3]->SetText(std::to_string(m_charInfo.int_), false);
  m_text[4]->SetText(std::to_string(m_charInfo.dex), false);
  m_text[5]->SetText(std::to_string(m_charInfo.luk), false);
  Invalidate();
}

void CUIMakeCharWnd::MakeButton() {
  const std::string button_name[8][3] = {
      {"btn_ok", "btn_ok_a", "btn_ok_b"},
      {"btn_cancel", "btn_cancel_b", "btn_cancel_b"},
      {"login_interface/arw-str0", "login_interface/arw-str1",
       "login_interface/arw-str0"},
      {"login_interface/arw-agi0", "login_interface/arw-agi1",
       "login_interface/arw-agi0"},
      {"login_interface/arw-vit0", "login_interface/arw-vit1",
       "login_interface/arw-vit0"},
      {"login_interface/arw-int0", "login_interface/arw-int1",
       "login_interface/arw-int0"},
      {"login_interface/arw-dex0", "login_interface/arw-dex1",
       "login_interface/arw-dex0"},
      {"login_interface/arw-luk0", "login_interface/arw-luk1",
       "login_interface/arw-luk0"}};
  const size_t ids[8] = {118, 119, 139, 140, 141, 142, 143, 144};
  const int pos[8][2] = {{0x1e3, 0x13e}, {0x212, 0x13e}, {0x10e, 0x32},
                         {0xbe, 0x68},   {0x15d, 0x68},  {0x10e, 0xf4},
                         {0xbe, 0xbe},   {0x15d, 0xbe}};

  for (size_t i = 0; i < 8; i++) {
    auto bitmap_btn = new CUIBitmapButton();

    bitmap_btn->SetBitmapName(
        const_strings::kResourceSubfolder + button_name[i][0] + ".bmp", 0);
    bitmap_btn->SetBitmapName(
        const_strings::kResourceSubfolder + button_name[i][1] + ".bmp", 1);
    bitmap_btn->SetBitmapName(
        const_strings::kResourceSubfolder + button_name[i][2] + ".bmp", 2);

    bitmap_btn->Create(bitmap_btn->GetBitmapWidth(),
                       bitmap_btn->GetBitmapHeight());
    bitmap_btn->Move(pos[i][0], pos[i][1]);
    bitmap_btn->SetId(ids[i]);
    AddChild(bitmap_btn);
  }
}

void *CUIMakeCharWnd::SendMsg(CUIWindow *sender, int message, void *val1,
                              void *val2, void *val3, void *val4) {
  switch (message) {
    case 0: {
      const auto &name = m_nameEditCtrl->GetText();
      name.copy(m_charInfo.name, sizeof(m_charInfo.name), 0);
      m_charInfo.name[name.length()] = '\0';
    } break;

    case WM_BUTTON_PRESSED: {
      const size_t btn_id = reinterpret_cast<size_t>(val1);

      switch (btn_id) {
        case 118:  // ok_btn
          if (m_nameEditCtrl->GetTextSize() < 4) {
            const auto error_msg =
                g_MsgStrMgr->GetMsgStr(MSI_ENTER_NAME_MORE_THAN_4_CHAR);
            g_WindowMgr->ErrorMsg(error_msg, 0, 1, 0, 0);
            return nullptr;
          }

          g_Session->SetCharName(m_nameEditCtrl->GetText());
          g_ModeMgr->GetCurMode()->SendMsg(LMM_SENDCHARINFO);
          g_WindowMgr->PostQuit(this);
          g_WindowMgr->SetCurScreen(1);
          break;
        case 119:  // cancel_btn
          g_WindowMgr->PostQuit(this);
          g_WindowMgr->SetCurScreen(110);
          break;
        case 139:  // str_arw
          if (m_charInfo.int_ < 2) {
            return nullptr;
          }

          m_charInfo.int_--;
          m_charInfo.str++;

          if (m_charInfo.int_ + m_charInfo.str != 10) {
            m_charInfo.int_ = 5;
            m_charInfo.str = 5;
          }
          InitTextControls();
          break;
        case 140:  // agi_arw
          if (m_charInfo.luk < 2) {
            return nullptr;
          }

          m_charInfo.luk--;
          m_charInfo.agi++;

          if (m_charInfo.luk + m_charInfo.agi != 10) {
            m_charInfo.luk = 5;
            m_charInfo.agi = 5;
          }
          InitTextControls();
          break;
        case 141:  // vit_arw
          if (m_charInfo.dex < 2) {
            return nullptr;
          }

          m_charInfo.dex--;
          m_charInfo.vit++;

          if (m_charInfo.dex + m_charInfo.vit != 10) {
            m_charInfo.dex = 5;
            m_charInfo.vit = 5;
          }
          InitTextControls();
          break;
        case 142:  // int_arw
          if (m_charInfo.str < 2) {
            return nullptr;
          }

          m_charInfo.str--;
          m_charInfo.int_++;

          if (m_charInfo.str + m_charInfo.int_ != 10) {
            m_charInfo.str = 5;
            m_charInfo.int_ = 5;
          }
          InitTextControls();
          break;
        case 143:  // dex_arw
          if (m_charInfo.vit < 2) {
            return nullptr;
          }

          m_charInfo.vit--;
          m_charInfo.dex++;

          if (m_charInfo.vit + m_charInfo.dex != 10) {
            m_charInfo.vit = 5;
            m_charInfo.dex = 5;
          }
          InitTextControls();
          break;
        case 144:  // luk_arw
          if (m_charInfo.agi < 2) {
            return nullptr;
          }

          m_charInfo.agi--;
          m_charInfo.luk++;

          if (m_charInfo.agi + m_charInfo.luk != 10) {
            m_charInfo.agi = 5;
            m_charInfo.luk = 5;
          }
          InitTextControls();
          break;
      }
    } break;
  }

  return nullptr;
}
