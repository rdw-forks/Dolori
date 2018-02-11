#include "UISelectCharWnd.h"
#include "Common/GetTick.h"
#include "Common/Globals.h"
#include "Render/ActRes.h"
#include "UIBmp.h"

CUISelectCharWnd::CUISelectCharWnd() {
  m_defPushId = 117;
  m_defCancelPushId = 117;
  m_startGlobalX = 0;
  m_startGlobalY = 0;
  m_state_cnt = 0;
  m_ok_button = NULL;
  m_make_button = NULL;
  m_cancel_button = NULL;
  m_delete_button = NULL;
  m_charge_button = NULL;
  m_notice_button = NULL;
  m_dontmove = false;
  memset(m_viewChar, 0, sizeof(m_viewChar));
  if (g_extendedSlot)
    m_pageCount = 3;
  else
    m_pageCount = 1;
  for (int i = 0; i < SLOTS_PER_PAGE * m_pageCount; i++)
    m_isAvailable[i] = true;
  m_cur_slot = 0;
  m_cur_page = 0;
  m_stateStartTick = GetTick();
  m_change_name_btn = NULL;
}

CUISelectCharWnd::~CUISelectCharWnd() {}

void CUISelectCharWnd::OnCreate(int cx, int cy) {
  std::string path_name = "유저인터페이스/login_interface/";
  std::string box_select = path_name + "box_select.bmp";

  g_selected_char_num = m_cur_slot + m_cur_page * SLOTS_PER_PAGE;

  for (int i = 0; i < SLOTS_PER_PAGE; i++) {
    m_slots[i] = new CUISlotBitmap(i);
    m_slots[i]->SetBitmap(box_select.c_str());
    m_slots[i]->Create(m_slots[i]->GetWidth(), m_slots[i]->GetHeight());
    m_slots[i]->Move(56 + i * 163, 40);
    m_slots[i]->SetId(138);
    m_slots[i]->SendMsg(this, 13, (void *)(m_cur_slot != i), 0, 0, 0);
    AddChild(m_slots[i]);
  }

  m_change_name_btn = new CUIBitmapButton();
  m_change_name_btn->SetBitmapName((path_name + "btn_change_name.bmp").c_str(),
                                   0);
  m_change_name_btn->SetBitmapName(
      (path_name + "btn_change_name_a.bmp").c_str(), 1);
  m_change_name_btn->SetBitmapName(
      (path_name + "btn_change_name_b.bmp").c_str(), 2);

  m_change_name_btn->Create(m_change_name_btn->GetBitmapWidth(),
                            m_change_name_btn->GetBitmapHeight());
  m_change_name_btn->Move(-100, -100);
  m_change_name_btn->SetId(285);
  AddChild(m_change_name_btn);

  for (int i = 0; i < NB_OF_SLOTS; i++) {
    m_text[i] = new CUIStaticText();
    m_text[i]->Create(90, 15);
    m_text[i]->Move(144 * (i / 6) + 69, 16 * (i % 6) + 205);
    m_text[i]->SetText("", false);
    AddChild(m_text[i]);
  }
  InitTextControls();

  for (int i = 0; i < SLOTS_PER_PAGE * m_pageCount; i++) {
    CHARACTER_INFO *char_info;
    char buffer[256];
    VIEW_SPRITE *vs;
    uint16_t job;
    int sex;

    char_info = (CHARACTER_INFO *)g_ModeMgr->GetCurMode()->SendMsg(
        MM_QUERYCHARICTORINFO, (void *)i, 0, 0);
    if (!char_info) continue;

    vs = &m_viewChar[char_info->char_slot];
    job = char_info->class_;
    sex = g_Session->GetSex();
    m_isEmpty[char_info->char_slot] = false;
    vs->x = 163 * (i % SLOTS_PER_PAGE) + 124;
    vs->y = 157;
    vs->act_name[0] = g_Session->GetJobActName(job, sex, buffer);
    vs->spr_name[0] = g_Session->GetJobSprName(job, sex, buffer);
    vs->act_name[1] =
        g_Session->GetHeadActName(job, &char_info->head_style, sex, buffer);
    vs->spr_name[1] =
        g_Session->GetHeadSprName(job, &char_info->head_style, sex, buffer);
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

  g_WindowMgr->SetCapture(this);
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
  const char *filename;
  CBitmapRes *bitmap;

  filename = UIBmp("유저인터페이스/login_interface/win_select.bmp");
  bitmap = (CBitmapRes *)g_ResMgr->Get(filename, false);
  DrawBitmap(0, 0, bitmap, 0);

  for (int i = 0; i < SLOTS_PER_PAGE; i++) {
    int char_id = SLOTS_PER_PAGE * m_cur_page + i;

    if (!m_isAvailable[char_id]) {
      TextOutA(163 * char_id + 82, 107, "Not available", 0, 1, 18, 0);
      continue;
    }
    if (!m_isEmpty[char_id]) {
      // TEST CODE ==============
      for (int layer = 0; layer < 5; layer++) {
        VIEW_SPRITE *vs;
        CMotion *motion;
        SPR_CLIP *clip;
        int off_x = 0;
        int off_y = 0;
        SPR_IMG *img;
        CSprRes *spr;
        CActRes *act;

        vs = &m_viewChar[char_id];
        spr = (CSprRes *)g_ResMgr->Get(vs->spr_name[layer].c_str(), false);
        act = (CActRes *)g_ResMgr->Get(vs->act_name[layer].c_str(), false);
        if (!spr || !act) continue;

        motion = act->GetMotion(vs->cur_action, vs->cur_motion);
        if (motion) {
          if (layer == 1)  // Head
            clip = motion->GetClip(1);
          else
            clip = motion->GetClip(0);
          if (!clip || clip->spr_index == -1) continue;

          img = spr->GetSprImg(clip->clip_type, clip->spr_index);
          off_x = clip->x - img->width / 2;
          off_y = clip->y - img->height / 2;
          // if (motion->attach_count > 0) {
          //  off_x += motion->attach_info[0].x;
          //  off_y += motion->attach_info[0].y;
          //}

          CSurface *surface =
              g_Renderer->GetSpriteIndex(img, spr->GetPalette());
          if (!surface)
            surface = g_Renderer->AddSpriteIndex(img, spr->GetPalette());
          m_surfaces->BlitSurface(off_x + vs->x, off_y + vs->y, surface, 0, 0,
                                  img->width, img->height, 0, 1, 1);
        }
      }
      // g_ResMgr->Get(m_viewChar[char_id].imf_name.c_str(), false);
      // TEST CODE ==============
    }
  }
}

void CUISelectCharWnd::InitTextControls() {
  CHARACTER_INFO *char_info;
  char buffer[256];

  char_info = (CHARACTER_INFO *)g_ModeMgr->GetCurMode()->SendMsg(
      MM_QUERYCHARICTORINFO, (void *)(m_cur_slot + SLOTS_PER_PAGE * m_cur_page),
      0, 0);
  if (m_change_name_btn) m_change_name_btn->Move(-100, -100);
  if (char_info) {
    if (m_change_name_btn && !char_info->can_rename)
      m_change_name_btn->Move(360, 318);
    m_text[0]->SetText(char_info->name, false);
    m_text[1]->SetText(g_Session->GetJobName(char_info->class_), false);
    sprintf(buffer, "%d", char_info->base_level);
    m_text[2]->SetText(buffer, false);
    sprintf(buffer, "%d", char_info->base_exp);
    m_text[3]->SetText(buffer, false);
    sprintf(buffer, "%d / %d", char_info->hp, char_info->max_hp);
    m_text[4]->SetText(buffer, false);
    sprintf(buffer, "%d / %d", char_info->sp, char_info->max_sp);
    m_text[5]->SetText(buffer, false);
    sprintf(buffer, "%d", char_info->str);
    m_text[6]->SetText(buffer, false);
    sprintf(buffer, "%d", char_info->agi);
    m_text[7]->SetText(buffer, false);
    sprintf(buffer, "%d", char_info->vit);
    m_text[8]->SetText(buffer, false);
    sprintf(buffer, "%d", char_info->int_);
    m_text[9]->SetText(buffer, false);
    sprintf(buffer, "%d", char_info->dex);
    m_text[10]->SetText(buffer, false);
    sprintf(buffer, "%d", char_info->luk);
    m_text[11]->SetText(buffer, false);
  } else {
    for (int i = 0; i < NB_OF_SLOTS; i++) m_text[i]->SetText("", false);
  }
}

void *CUISelectCharWnd::SendMsg(CUIWindow *sender, int message, void *val1,
                                void *val2, void *val3, void *val4) {
  void *result = NULL;

  switch (message) {
    case 6: {
      size_t btn_id = (size_t)val1;
      size_t slot_id = m_cur_slot + SLOTS_PER_PAGE * m_cur_page;
      CHARACTER_INFO *char_info;

      if (btn_id == 118) {
        if (!m_ok_button) return result;

        m_dontmove = true;
        char_info = (CHARACTER_INFO *)g_ModeMgr->GetCurMode()->SendMsg(
            MM_QUERYCHARICTORINFO, (void *)slot_id, 0, 0);
        g_Session->SetCharName(char_info->name);
        // PlayWave(waveFileName, 0.0, 0.0, 0.0, 250, 40, 1.0);
        g_ModeMgr->GetCurMode()->SendMsg(MM_COMMAND, (void *)10002, 0, 0);
        g_ModeMgr->GetCurMode()->SendMsg(LMM_SELECT_CHARACTER, (void *)slot_id,
                                         0, 0);
        g_WindowMgr->PostQuit(this);
      } else if (btn_id == 138) {
        Invalidate();
        for (int i = 0; i < SLOTS_PER_PAGE; i++) {
          size_t index = i + m_cur_page * SLOTS_PER_PAGE;

          if (m_slots[index] == sender) {
            m_cur_slot = index;
            m_slots[index]->SendMsg(this, 13, 0, 0, 0, 0);
          } else
            m_slots[index]->SendMsg(this, 13, (void *)1, 0, 0, 0);
        }
        InitTextControls();
        g_selected_char_num = (uint8_t)slot_id;
      }
    } break;
    case 13:
      m_cur_slot = (size_t)val1;
      break;
  };

  return result;
}

void CUISelectCharWnd::MakeButton(int id) {
  int index;

  switch (id) {
    case 118:
      if (!m_ok_button) {
        if (m_make_button) m_make_button = NULL;
        index = 0;
      } else
        return;
      break;
    case 137:
      if (!m_make_button) {
        if (m_ok_button) m_ok_button = NULL;
        if (m_delete_button) {
          RemoveChild(m_delete_button);
          m_delete_button = NULL;
        }
        index = 1;
      } else
        return;
      break;
    case 119:
      if (!m_cancel_button)
        index = 2;
      else
        return;
      break;
    case 145:
      if (!m_delete_button) {
        if (m_make_button) {
          RemoveChild(m_make_button);
          m_make_button = NULL;
        }
        index = 3;
      } else
        return;
      break;
    case 218:
      if (!m_charge_button) index = 4;
      break;
    case 220:
      if (m_notice_button) return;
      index = 5;
      break;
    default:
      return;
  };

  CUIBitmapButton *new_button = new CUIBitmapButton();
  std::string path_name = "유저인터페이스/";
  const char *button_name[6];
  int x_offset = 0;
  int ids[6];

  button_name[0] = "btn_ok";
  button_name[1] = "btn_make";
  button_name[2] = "btn_cancel";
  button_name[3] = "btn_del";
  button_name[4] = "btn_charge";
  button_name[5] = "btn_charge";
  ids[0] = 118;
  ids[1] = 137;
  ids[2] = 119;
  ids[3] = 145;
  ids[4] = 218;
  ids[5] = 220;

  new_button->SetBitmapName((path_name + button_name[index] + ".bmp").c_str(),
                            0);
  new_button->SetBitmapName((path_name + button_name[index] + "_a.bmp").c_str(),
                            1);
  new_button->SetBitmapName((path_name + button_name[index] + "_b.bmp").c_str(),
                            2);
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
  };
  new_button->Move(x_offset, 318);
  new_button->SetId(ids[index]);
  AddChild(new_button);
}