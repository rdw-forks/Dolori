#include "UI/UISelectCharWnd.h"

#include "Common/GetTick.h"
#include "Common/Globals.h"
#include "Common/const_strings.h"
#include "Files/ActRes.h"
#include "UI/UIBmp.h"

CUISelectCharWnd::CUISelectCharWnd(CUIWindowMgr *p_window_mgr)
    : CUIFrameWnd(p_window_mgr),
      m_viewChar(),
      m_stateStartTick(GetTick()),
      m_dontmove(false),
      m_cur_page(),
      m_cur_slot(),
      m_ok_button(),
      m_make_button(),
      m_cancel_button(),
      m_delete_button(),
      m_notice_button(),
      m_charge_button(),
      m_change_name_btn() {
  m_defPushId = 117;
  m_defCancelPushId = 117;

  if (g_extendedSlot) {
    m_pageCount = 3;
  } else {
    m_pageCount = 1;
  }

  for (int i = 0; i < SLOTS_PER_PAGE * m_pageCount; i++) {
    m_isAvailable[i] = true;
  }
}

void CUISelectCharWnd::OnCreate(int /*cx*/, int /*cy*/) {
  const std::string path_name =
      const_strings::kResourceSubfolder + "login_interface/";
  const std::string box_select = path_name + "box_select.bmp";

  g_ModeMgr->GetCurMode()->SendMsg(
      LMM_SELECT_CHARACTER,
      reinterpret_cast<void *>(m_cur_slot + m_cur_page * SLOTS_PER_PAGE));

  for (int i = 0; i < SLOTS_PER_PAGE; i++) {
    m_slots[i] = new CUISlotBitmap(p_window_mgr_, i);
    m_slots[i]->SetBitmap(box_select.c_str());
    m_slots[i]->Create(m_slots[i]->GetWidth(), m_slots[i]->GetHeight());
    m_slots[i]->Move(56 + i * 163, 40);
    m_slots[i]->SetId(138);
    m_slots[i]->SendMsg(this, 13, reinterpret_cast<void *>(m_cur_slot != i));
    AddChild(m_slots[i]);
  }

  m_change_name_btn = new CUIBitmapButton(p_window_mgr_);
  m_change_name_btn->SetBitmapName(path_name + "btn_change_name.bmp", 0);
  m_change_name_btn->SetBitmapName(path_name + "btn_change_name_a.bmp", 1);
  m_change_name_btn->SetBitmapName(path_name + "btn_change_name_b.bmp", 2);

  m_change_name_btn->Create(m_change_name_btn->GetBitmapWidth(),
                            m_change_name_btn->GetBitmapHeight());
  m_change_name_btn->Move(-100, -100);
  m_change_name_btn->SetId(285);
  AddChild(m_change_name_btn);

  for (int i = 0; i < NB_OF_SLOTS; i++) {
    m_text[i] = new CUIStaticText(p_window_mgr_);
    m_text[i]->Create(90, 15);
    m_text[i]->Move(144 * (i / 6) + 69, 16 * (i % 6) + 205);
    m_text[i]->SetText("", false);
    AddChild(m_text[i]);
  }
  InitTextControls();

  for (size_t i = 0; i < SLOTS_PER_PAGE * m_pageCount; i++) {
    CharacterInfo *char_info;
    VIEW_SPRITE *vs;
    uint16_t job;
    int sex;

    char_info = static_cast<CharacterInfo *>(g_ModeMgr->GetCurMode()->SendMsg(
        MM_QUERYCHARICTORINFO, reinterpret_cast<void *>(i)));
    if (!char_info) {
      continue;
    }

    vs = &m_viewChar[char_info->char_slot];
    job = char_info->job;
    sex = g_Session->GetSex();
    m_isEmpty[char_info->char_slot] = false;
    vs->x = 163 * (i % SLOTS_PER_PAGE) + 124;
    vs->y = 157;
    vs->act_name[0] = std::move(g_Session->GetJobActName(job, sex));
    vs->spr_name[0] = std::move(g_Session->GetJobSprName(job, sex));
    vs->act_name[1] =
        std::move(g_Session->GetHeadActName(char_info->head_style, sex));
    vs->spr_name[1] =
        std::move(g_Session->GetHeadSprName(char_info->head_style, sex));
  }

  MakeButton(119);
  if (m_isEmpty[m_cur_slot]) {
    MakeButton(137);
  } else {
    MakeButton(118);
    MakeButton(145);
  }

  MakeButton(218);
  m_defPushId = 118;
}

void CUISelectCharWnd::OnLBtnDown(int x, int y) {
  int x_global;
  int y_global;

  p_window_mgr_->SetCapture(this);
  GetGlobalCoor(&x_global, &y_global);
  m_startGlobalX = x_global;
  m_startGlobalY = y_global;
  m_orgX = m_x;
  m_orgY = m_y;
  m_transTarget = 128;
  m_transTime = GetTick();
  // CSnapMgr::BeginMove(&g_snapMgr, (UIWindow *)&v3->vfptr);
}

void CUISelectCharWnd::OnDraw() {
  const std::string filename =
      const_strings::kResourceSubfolder + "login_interface/win_select.bmp";

  auto bitmap =
      static_cast<CBitmapRes *>(g_ResMgr->Get(UIBmp(filename), false));
  DrawBitmap(0, 0, bitmap, 0);

  for (size_t i = 0; i < SLOTS_PER_PAGE; i++) {
    const size_t char_id = SLOTS_PER_PAGE * m_cur_page + i;

    if (!m_isAvailable[char_id]) {
      TextOutA(163 * char_id + 82, 107, "Not available", 0, 1, 18, 0);
      continue;
    }

    if (m_isEmpty[char_id]) {
      continue;
    }

    for (int layer = 0; layer < VIEW_SPRITE_LAYERS_COUNT; layer++) {
      const SprClip *clip;
      VIEW_SPRITE *vs;
      int off_x = 0;
      int off_y = 0;
      SprImg *img;
      CSprRes *spr;
      CActRes *act;

      vs = &m_viewChar[char_id];
      spr = static_cast<CSprRes *>(g_ResMgr->Get(vs->spr_name[layer], false));
      act = static_cast<CActRes *>(g_ResMgr->Get(vs->act_name[layer], false));
      if (spr == nullptr || act == nullptr) {
        continue;
      }

      const CMotion *motion = act->GetMotion(vs->cur_action, vs->cur_motion);
      if (motion == nullptr) {
        continue;
      }

      if (layer == 1) {  // Head
        clip = motion->GetClip(1);
      } else {
        clip = motion->GetClip(0);
      }

      if (clip == nullptr || clip->spr_index == -1) {
        continue;
      }

      img = spr->GetSprImg(clip->clip_type, clip->spr_index);
      off_x = clip->x - img->width / 2;
      off_y = clip->y - img->height / 2;
      // if (motion->attach_count > 0) {
      //  off_x += motion->attach_info[0].x;
      //  off_y += motion->attach_info[0].y;
      //}

      CSurface *surface = g_Renderer->GetSpriteIndex(img, spr->GetPalette());
      if (surface == nullptr) {
        surface = g_Renderer->AddSpriteIndex(img, spr->GetPalette());
      }

      m_surface->BlitSurface(off_x + vs->x, off_y + vs->y, surface, 0, 0,
                             img->width, img->height, clip->is_mirror,
                             clip->zoomx, clip->zoomy);
    }
    // g_ResMgr->Get(m_viewChar[char_id].imf_name.c_str(), false);
  }
}

void CUISelectCharWnd::InitTextControls() {
  const auto char_info =
      static_cast<CharacterInfo *>(g_ModeMgr->GetCurMode()->SendMsg(
          MM_QUERYCHARICTORINFO,
          reinterpret_cast<void *>(m_cur_slot + SLOTS_PER_PAGE * m_cur_page)));
  if (m_change_name_btn) {
    m_change_name_btn->Move(-100, -100);
  }

  if (char_info) {
    if (m_change_name_btn && !char_info->can_rename) {
      m_change_name_btn->Move(360, 318);
    }

    const auto hp_str = std::to_string(char_info->hp) + " / " +
                        std::to_string(char_info->max_hp);
    const auto sp_str = std::to_string(char_info->sp) + " / " +
                        std::to_string(char_info->max_sp);

    m_text[0]->SetText(char_info->name, false);
    m_text[1]->SetText(g_Session->GetJobName(char_info->job), false);
    m_text[2]->SetText(std::to_string(char_info->base_level), false);
    m_text[3]->SetText(std::to_string(char_info->base_exp), false);
    m_text[4]->SetText(hp_str, false);
    m_text[5]->SetText(sp_str, false);
    m_text[6]->SetText(std::to_string(char_info->str), false);
    m_text[7]->SetText(std::to_string(char_info->agi), false);
    m_text[8]->SetText(std::to_string(char_info->vit), false);
    m_text[9]->SetText(std::to_string(char_info->int_), false);
    m_text[10]->SetText(std::to_string(char_info->dex), false);
    m_text[11]->SetText(std::to_string(char_info->luk), false);
  } else {
    for (int i = 0; i < NB_OF_SLOTS; i++) {
      m_text[i]->SetText("", false);
    }
  }
}

void *CUISelectCharWnd::SendMsg(CUIWindow *sender, int message, void *val1,
                                void *val2, void *val3, void *val4) {
  void *result = nullptr;

  switch (message) {
    case WM_BUTTON_PRESSED: {
      const size_t btn_id = reinterpret_cast<size_t>(val1);
      const size_t slot_id = m_cur_slot + SLOTS_PER_PAGE * m_cur_page;

      if (btn_id == 118) {
        if (m_ok_button == nullptr) {
          return nullptr;
        }

        m_dontmove = true;
        const auto char_info =
            static_cast<CharacterInfo *>(g_ModeMgr->GetCurMode()->SendMsg(
                MM_QUERYCHARICTORINFO, reinterpret_cast<void *>(slot_id)));
        if (char_info == nullptr) {
          return nullptr;
        }

        g_Session->SetCharName(char_info->name);
        // PlayWave(waveFileName, 0.0, 0.0, 0.0, 250, 40, 1.0);
        g_ModeMgr->GetCurMode()->SendMsg(MM_COMMAND,
                                         reinterpret_cast<void *>(10002));
        g_ModeMgr->GetCurMode()->SendMsg(LMM_SELECT_CHARACTER,
                                         reinterpret_cast<void *>(slot_id));
        p_window_mgr_->PostQuit(this);
      } else if (btn_id == 137) {
        if (m_make_button == nullptr) {
          return nullptr;
        }

        if (!m_isAvailable[slot_id] || !m_isEmpty[slot_id]) {
          return nullptr;
        }

        g_ModeMgr->GetCurMode()->SendMsg(MM_COMMAND,
                                         reinterpret_cast<void *>(10001), 0, 0);
        g_ModeMgr->GetCurMode()->SendMsg(LMM_SELECT_CHARACTER,
                                         reinterpret_cast<void *>(slot_id));
        p_window_mgr_->PostQuit(this);

        return nullptr;
      } else if (btn_id == 138) {
        Invalidate();
        for (int i = 0; i < SLOTS_PER_PAGE; i++) {
          size_t index = i + m_cur_page * SLOTS_PER_PAGE;

          if (m_slots[index] == sender) {
            m_cur_slot = index;
            m_slots[index]->SendMsg(this, 13);
          } else {
            m_slots[index]->SendMsg(this, 13, reinterpret_cast<void *>(1));
          }
        }
        InitTextControls();
      }
    } break;
    case 13:
      m_cur_slot = reinterpret_cast<size_t>(val1);
      if (m_isEmpty[m_cur_slot]) {
        MakeButton(137);
      } else {
        MakeButton(118);
        MakeButton(145);
      }
      break;
  };

  return result;
}

void CUISelectCharWnd::MakeButton(int id) {
  int index;

  switch (id) {
    case 118:
      if (m_ok_button) {
        return;
      }

      if (m_make_button) {
        RemoveChild(m_make_button);
        m_make_button = nullptr;
      }

      index = 0;
      break;
    case 137:
      if (m_make_button) {
        return;
      }

      if (m_ok_button) {
        RemoveChild(m_ok_button);
        m_ok_button = nullptr;
      }

      if (m_delete_button) {
        RemoveChild(m_delete_button);
        m_delete_button = nullptr;
      }

      index = 1;
      break;
    case 119:
      if (m_cancel_button) {
        return;
      }

      index = 2;
      break;
    case 145:
      if (m_delete_button) {
        return;
      }

      if (m_make_button) {
        RemoveChild(m_make_button);
        m_make_button = nullptr;
      }

      index = 3;
      break;
    case 218:
      if (m_charge_button) {
        return;
      }

      index = 4;
      break;
    case 220:
      if (m_notice_button) {
        return;
      }

      index = 5;
      break;
    default:
      return;
  };

  CUIBitmapButton *new_button = new CUIBitmapButton(p_window_mgr_);
  const std::string path_name = const_strings::kResourceSubfolder;
  const std::string button_name[6] = {"btn_ok",  "btn_make",   "btn_cancel",
                                      "btn_del", "btn_charge", "btn_charge"};
  const int ids[6] = {118, 137, 119, 145, 218, 220};
  int x_offset = 0;

  new_button->SetBitmapName(path_name + button_name[index] + ".bmp", 0);
  new_button->SetBitmapName(path_name + button_name[index] + "_a.bmp", 1);
  new_button->SetBitmapName(path_name + button_name[index] + "_b.bmp", 2);
  new_button->Create(new_button->GetBitmapWidth(),
                     new_button->GetBitmapWidth());

  switch (id) {
    case 118:
      x_offset = 525 - new_button->GetBitmapWidth();
      m_ok_button = new_button;
      break;
    case 137:
      x_offset = 525 - new_button->GetBitmapWidth();
      m_make_button = new_button;
      break;
    case 119:
      x_offset = 530;
      m_cancel_button = new_button;
      break;
    case 145:
      x_offset = 5;
      m_delete_button = new_button;
      break;
    case 218:
      x_offset = 402;
      m_charge_button = new_button;
      break;
    case 220:
      x_offset = 402;
      m_notice_button = new_button;
      break;
  }

  new_button->Move(x_offset, 318);
  new_button->SetId(ids[index]);
  AddChild(new_button);
}
