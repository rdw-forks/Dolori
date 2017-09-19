#include "UISelectCharWnd.h"
#include "../Common/GetTick.h"
#include "../Common/Globals.h"
#include "../Render/ActRes.h"
#include "UIBmp.h"

CUISelectCharWnd::CUISelectCharWnd() {
  m_defPushId = 117;
  m_defCancelPushId = 117;
  m_startGlobalX = 0;
  m_startGlobalY = 0;
  m_state_cnt = 0;
  m_okButton = NULL;
  m_makeButton = NULL;
  m_cancelButton = NULL;
  m_deleteButton = NULL;
  m_chargeButton = NULL;
  m_noticeButton = NULL;
  m_dontmove = false;
  memset(m_viewChar, 0, sizeof(m_viewChar));
  if (g_extendedSlot)
    m_pageCount = 3;
  else
    m_pageCount = 1;
  for (int i = 0; i < SLOTS_PER_PAGE * m_pageCount; i++)
    m_isAvailable[i] = true;
  m_cur_slot = 0;
  m_curPage = 0;
  m_stateStartTick = GetTick();
  m_changeNameBtn = NULL;
}

CUISelectCharWnd::~CUISelectCharWnd() {}

void CUISelectCharWnd::OnCreate(int cx, int cy) {
  std::string path_name = "유저인터페이스/login_interface/";
  std::string box_select = path_name + "box_select.bmp";

  for (int i = 0; i < SLOTS_PER_PAGE; i++) {
    m_slots[i] = new CUISlotBitmap(i);
    m_slots[i]->SetBitmap(box_select.c_str());
    m_slots[i]->Create(m_slots[i]->GetWidth(), m_slots[i]->GetHeight());
    m_slots[i]->Move((i + 1) * 56, 40);
    m_slots[i]->SetId(138);
    m_slots[i]->SendMsg(this, 13, (void *)(m_cur_slot != i), 0, 0, 0);
    AddChild(m_slots[i]);
  }

  m_changeNameBtn = new CUIBitmapButton();
  m_changeNameBtn->SetBitmapName((path_name + "btn_change_name.bmp").c_str(),
                                 0);
  m_changeNameBtn->SetBitmapName((path_name + "btn_change_name_a.bmp").c_str(),
                                 1);
  m_changeNameBtn->SetBitmapName((path_name + "btn_change_name_b.bmp").c_str(),
                                 2);

  m_changeNameBtn->Create(m_changeNameBtn->GetBitmapWidth(),
                          m_changeNameBtn->GetBitmapHeight());
  m_changeNameBtn->Move(-100, -100);
  m_changeNameBtn->SetId(285);
  AddChild(m_changeNameBtn);

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

  // MakeButton(119);
  if (m_isEmpty[m_cur_slot]) {
    //  MakeButton(137);
  } else {
    //  MakeButton(118);
    //  MakeButton(145);
  }
  // MakeButton(218);
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
    int char_id = SLOTS_PER_PAGE * m_curPage + i;

    if (!m_isAvailable[char_id]) {
      TextOutA(163 * char_id + 82, 107, "Not available", 0, 1, 18, 0);
      continue;
    }
    if (!m_isEmpty[char_id]) {
      // TEST CODE ==============
      for (int j = 0; j < 5; j++) {
        VIEW_SPRITE *vs;
        CMotion *motion;
        SPR_CLIP *clip;
        int off_x = 0;
        int off_y = 0;
        SPR_IMG *img;
        CSprRes *spr;
        CActRes *act;

        vs = &m_viewChar[char_id];
        spr = (CSprRes *)g_ResMgr->Get(vs->spr_name[j].c_str(), false);
        act = (CActRes *)g_ResMgr->Get(vs->act_name[j].c_str(), false);
        if (!spr || !act) continue;

        motion = act->GetMotion(vs->cur_action, vs->cur_motion);
        if (motion) {
          if (j == 1)  // Head
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
          m_surface->BlitSurface(off_x + vs->x, off_y + vs->y, surface, 0, 0,
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
      MM_QUERYCHARICTORINFO, (void *)(m_cur_slot + SLOTS_PER_PAGE * m_curPage),
      0, 0);
  if (m_changeNameBtn) m_changeNameBtn->Move(-100, -100);
  if (char_info) {
    if (m_changeNameBtn) {
      if (!char_info->can_rename) m_changeNameBtn->Move(360, 318);
    }
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
    case 13:
      m_cur_slot = (size_t)val1;
      break;
  };

  return result;
}