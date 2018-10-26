#include "UI/UIMakeCharWnd.h"

#include "Common/Globals.h"
#include "Common/MsgStrMgr.h"
#include "Common/const_strings.h"
#include "Common/debug.h"
#include "Files/ActRes.h"
#include "Files/ImfRes.h"
#include "Files/SprRes.h"
#include "UI/UIBmp.h"

CUIMakeCharWnd::CUIMakeCharWnd(CUIWindowMgr *p_window_mgr)
    : CUIFrameWnd(p_window_mgr),
      m_charInfo(),
      m_charInfo2(),
      m_viewChar(),
      m_viewChar2(),
      m_text() {
  m_charInfo.head_style = 1;
  m_charInfo.job = 0;
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

  m_viewChar.x = 95;
  m_viewChar.y = 213;
  m_viewChar.base_action = 0;
  m_viewChar.cur_action = 0;
  m_viewChar.cur_motion = 0;
  m_sex = g_Session->GetSex();
  m_viewChar.act_name[0] =
      std::move(g_Session->GetJobActName(m_charInfo.job, m_sex));
  m_viewChar.spr_name[0] =
      std::move(g_Session->GetJobSprName(m_charInfo.job, m_sex));
  m_viewChar.act_name[1] =
      std::move(g_Session->GetHeadActName(m_charInfo.head_style, m_sex));
  m_viewChar.spr_name[1] =
      std::move(g_Session->GetHeadSprName(m_charInfo.head_style, m_sex));
  m_viewChar.imf_name = std::move(g_Session->GetImfName(m_charInfo.job, m_sex));
}

void CUIMakeCharWnd::OnCreate(int x, int y) {
  g_ModeMgr->GetCurMode()->SendMsg(LMM_GET_MAKING_CHAR_NAME, 0, 0, 0);

  const std::string bitmap_name =
      const_strings::kResourceSubfolder + "login_interface/name-edit.bmp";

  for (int i = 0; i < 6; i++) {
    m_text[i] = new CUIStaticText(p_window_mgr_);
    m_text[i]->Create(90, 15);
    m_text[i]->Move(144 * (i / 6) + 490, 16 * (i % 6) + 40);
    AddChild(m_text[i]);
  }
  InitTextControls();

  m_nameEditCtrl = new CUIBitmapEditCtrl(p_window_mgr_);
  m_nameEditCtrl->SetBitmap(bitmap_name);
  m_nameEditCtrl->Create(m_nameEditCtrl->GetWidth(),
                         m_nameEditCtrl->GetHeight());
  m_nameEditCtrl->Move(62, 244);
  m_nameEditCtrl->SetTextLimit(24);
  m_nameEditCtrl->SetId(118);
  AddChild(m_nameEditCtrl);
  MakeButton();
  p_window_mgr_->SetFocusEdit(m_nameEditCtrl);
  m_defPushId = 118;
}

void CUIMakeCharWnd::OnDraw() {
  const std::string filename =
      const_strings::kResourceSubfolder + "login_interface/win_make.bmp";

  auto bitmap =
      static_cast<CBitmapRes *>(g_ResMgr->Get(UIBmp(filename), false));
  DrawBitmap(0, 0, bitmap, 0);

  const auto imf_res =
      static_cast<CImfRes *>(g_ResMgr->Get(m_viewChar.imf_name, false));
  if (imf_res == nullptr) {
    return;
  }

  // Only the first two layers need to be rendered here (no accesories)
  for (size_t layer = 0; layer < 2; layer++) {
    int off_x = 0;
    int off_y = 0;

    const auto act_res = static_cast<CActRes *>(
        g_ResMgr->Get(m_viewChar.act_name[layer], false));
    const auto spr_res = static_cast<CSprRes *>(
        g_ResMgr->Get(m_viewChar.spr_name[layer], false));
    if (act_res == nullptr || spr_res == nullptr) {
      continue;
    }

    const CMotion *motion =
        act_res->GetMotion(m_viewChar.cur_action, m_viewChar.cur_motion);

    const auto point = std::move(
        imf_res->GetPoint(layer, m_viewChar.cur_action, m_viewChar.cur_motion));

    off_x = point.x;
    off_y = point.y;

    const SprClip *clip = nullptr;
    if (layer == 1) {  // Head
      const auto base_act_res =
          static_cast<CActRes *>(g_ResMgr->Get(m_viewChar.act_name[0], false));
      const CMotion *base_motion =
          base_act_res->GetMotion(m_viewChar.cur_action, m_viewChar.cur_motion);
      if (motion->attach_count > 0 && base_motion->attach_count > 0 &&
          base_motion->attach_info[0].m_attr == motion->attach_info[0].m_attr) {
        off_x += base_motion->attach_info[0].x - motion->attach_info[0].x;
        off_y += base_motion->attach_info[0].y - motion->attach_info[0].y;
      }
    }

    clip = motion->GetClip(layer);
    if (clip == nullptr || clip->spr_index == -1) {
      continue;
    }

    const SprImg *img = spr_res->GetSprImg(clip->clip_type, clip->spr_index);
    off_x += clip->x - img->width / 2;
    off_y += clip->y - img->height / 2;

    CSurface *surface = g_Renderer->GetSpriteIndex(img, spr_res->GetPalette());
    if (surface == nullptr) {
      surface = g_Renderer->AddSpriteIndex(img, spr_res->GetPalette());
    }

    m_surface->BlitSurface(off_x + m_viewChar.x, off_y + m_viewChar.y, surface,
                           0, 0, img->width, img->height, clip->is_mirror,
                           clip->zoomx, clip->zoomy);
  }
}

void CUIMakeCharWnd::OnProcess() {
  if (m_state_cnt % 34 == 0) {
    Invalidate();

    m_viewChar.cur_action++;
    if (m_viewChar.cur_action >= m_viewChar.base_action + 8) {
      m_viewChar.cur_action = m_viewChar.base_action;
    }
  }

  m_state_cnt++;
  m_viewChar.cur_motion = 0;
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
  constexpr size_t kButtonsCount = 11;
  const std::string button_name[kButtonsCount][3] = {
      {"btn_ok.bmp", "btn_ok_a.bmp", "btn_ok_b.bmp"},
      {"btn_cancel.bmp", "btn_cancel_b.bmp", "btn_cancel_b.bmp"},
      {"login_interface/arw-str0.bmp", "login_interface/arw-str1.bmp",
       "login_interface/arw-str0.bmp"},
      {"login_interface/arw-agi0.bmp", "login_interface/arw-agi1.bmp",
       "login_interface/arw-agi0.bmp"},
      {"login_interface/arw-vit0.bmp", "login_interface/arw-vit1.bmp",
       "login_interface/arw-vit0.bmp"},
      {"login_interface/arw-int0.bmp", "login_interface/arw-int1.bmp",
       "login_interface/arw-int0.bmp"},
      {"login_interface/arw-dex0.bmp", "login_interface/arw-dex1.bmp",
       "login_interface/arw-dex0.bmp"},
      {"login_interface/arw-luk0.bmp", "login_interface/arw-luk1.bmp",
       "login_interface/arw-luk0.bmp"},
      {"scroll1left.bmp", "scroll1left.bmp", "scroll1left.bmp"},
      {"scroll0up.bmp", "scroll0up.bmp", "scroll0up.bmp"},
      {"scroll1right.bmp", "scroll1right.bmp", "scroll1right.bmp"}};
  const size_t ids[kButtonsCount] = {118, 119, 139, 140, 141, 142,
                                     143, 144, 154, 155, 156};
  const int pos[kButtonsCount][2] = {
      {483, 318}, {530, 318}, {270, 50}, {190, 104}, {349, 104}, {270, 244},
      {190, 190}, {349, 190}, {47, 135}, {87, 105},  {127, 135}};

  for (size_t i = 0; i < kButtonsCount; i++) {
    auto bitmap_btn = new CUIBitmapButton(p_window_mgr_);

    constexpr size_t kStatesCount =
        sizeof(button_name[i]) / sizeof(button_name[i][0]);
    for (size_t state = 0; state < kStatesCount; state++) {
      bitmap_btn->SetBitmapName(
          const_strings::kResourceSubfolder + button_name[i][state], state);
    }

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
      if (name.length() > sizeof(m_charInfo.name) - 1) {
        LOG(error, "Character's name is too long");
        return nullptr;
      }

      strncpy(m_charInfo.name, name.c_str(), sizeof(m_charInfo.name));
    } break;

    case WM_BUTTON_PRESSED: {
      const size_t btn_id = reinterpret_cast<size_t>(val1);

      switch (btn_id) {
        case 118:  // ok_btn
          if (m_nameEditCtrl->GetTextSize() < 4) {
            const auto error_msg =
                g_MsgStrMgr->GetMsgStr(MSI_ENTER_NAME_MORE_THAN_4_CHAR);
            p_window_mgr_->ErrorMsg(error_msg, 0, 1, 0, 0);
            return nullptr;
          }

          g_Session->SetCharName(m_nameEditCtrl->GetText());
          g_ModeMgr->GetCurMode()->SendMsg(LMM_SENDCHARINFO, &m_charInfo);
          p_window_mgr_->PostQuit(this);
          p_window_mgr_->SetCurScreen(1);
          break;
        case 119:  // cancel_btn
          p_window_mgr_->PostQuit(this);
          p_window_mgr_->SetCurScreen(110);
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
        case 154:  // scroll1left
          m_charInfo.head_style--;
          if (m_charInfo.head_style < 1) {
            m_charInfo.head_style = 26;
          } else if (m_charInfo.head_style > 26) {
            m_charInfo.head_style = 1;
          }

          m_viewChar.act_name[1] = std::move(
              g_Session->GetHeadActName(m_charInfo.head_style, m_sex));
          m_viewChar.spr_name[1] = std::move(
              g_Session->GetHeadSprName(m_charInfo.head_style, m_sex));
          Invalidate();
          break;
        case 155:  // scroll0up
          m_charInfo.head_color = (m_charInfo.head_color + 1) % 10;
          Invalidate();
          break;
        case 156:  // scroll1right
          m_charInfo.head_style++;
          if (m_charInfo.head_style < 1) {
            m_charInfo.head_style = 26;
          } else if (m_charInfo.head_style > 26) {
            m_charInfo.head_style = 1;
          }

          m_viewChar.act_name[1] = std::move(
              g_Session->GetHeadActName(m_charInfo.head_style, m_sex));
          m_viewChar.spr_name[1] = std::move(
              g_Session->GetHeadSprName(m_charInfo.head_style, m_sex));
          Invalidate();
          break;
      }
    } break;
  }

  return nullptr;
}
