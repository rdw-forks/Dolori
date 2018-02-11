#include "ActRes.h"
#include "Common/ErrorMsg.h"
#include "Files/File.h"

CActRes::CActRes() { m_numMaxClipPerMotion = 0; }

CActRes::~CActRes() {
  m_delay.clear();

  for (auto it = m_events.begin(); it != m_events.end(); ++it) it->clear();
  m_events.clear();

  for (auto it = m_actions.begin(); it != m_actions.end(); ++it) delete &(*it);
  m_actions.clear();
}

CRes* CActRes::Clone() {
  CRes* res;

  res = new CActRes();
  if (res) return res;

  return NULL;
}

void CActRes::Reset() {
  for (auto it = m_events.begin(); it != m_events.end(); ++it) it->clear();
  m_events.clear();

  for (auto it = m_actions.begin(); it != m_actions.end(); ++it) delete &(*it);
  m_actions.clear();
}

bool CActRes::Load(const char* filename) {
  ACT_HEADER header;
  CFile fp;

  if (!fp.Open(filename, false)) {
    std::string error = "Cannot find ";
    error += filename;
    ErrorMsg(error.c_str());
    return false;
  }

  fp.Read(&header, sizeof(header));
  if (header.magic != 'CA') {
    std::string error = "Illegal file format: ";
    error += filename;
    ErrorMsg(error.c_str());
    fp.Close();
    return false;
  }

  if (header.version > 0x205) {
    ErrorMsg("Unsupported version. Content may be corrupted");
    fp.Close();
    return false;
  }
  Reset();
  m_actions.resize(header.action_count);

  // printf("Act version: %X\n", header.version);
  // printf("%d actions\n", header.action_count);
  for (int i = 0; i < header.action_count; i++) {
    CAction* cur_action = &m_actions[i];
    uint32_t motion_count;

    fp.Read(&motion_count, sizeof(motion_count));
    cur_action->Create(motion_count);
    // printf("%d motions\n", motion_count);
    for (int j = 0; j < motion_count; j++) {
      CMotion* cur_motion = &cur_action->motions[j];
      uint32_t sprite_count;

      fp.Read(&cur_motion->range1, sizeof(RECT_));
      fp.Read(&cur_motion->range2, sizeof(RECT_));
      fp.Read(&sprite_count, 4);

      if (sprite_count > m_numMaxClipPerMotion)
        m_numMaxClipPerMotion = sprite_count;

      cur_motion->spr_clips.resize(sprite_count);
      // printf("%d sprites\n", sprite_count);
      for (int k = 0; k < sprite_count; k++) {
        SPR_CLIP* cur_clip = &cur_motion->spr_clips[k];

        fp.Read(&cur_clip->x, 4);
        fp.Read(&cur_clip->y, 4);
        fp.Read(&cur_clip->spr_index, 4);
        fp.Read(&cur_clip->flags, 4);

        if (header.version >= 0x200) {
          fp.Read(&cur_clip->r, 1);
          fp.Read(&cur_clip->g, 1);
          fp.Read(&cur_clip->b, 1);
          fp.Read(&cur_clip->a, 1);
          fp.Read(&cur_clip->zoomx, 4);
          if (header.version <= 0x203)
            cur_clip->zoomy = cur_clip->zoomx;
          else
            fp.Read(&cur_clip->zoomy, 4);
          fp.Read(&cur_clip->angle, 4);
          fp.Read(&cur_clip->clip_type, 4);
          if (header.version >= 0x205) {
            fp.Read(&cur_clip->w, 4);
            fp.Read(&cur_clip->h, 4);
          } else {
            cur_clip->w = 0;
            cur_clip->h = 0;
          }
        } else {
          cur_clip->r = 0;
          cur_clip->g = 0;
          cur_clip->b = 0;
          cur_clip->a = 0;
          cur_clip->zoomx = .0f;
          cur_clip->zoomy = .0f;
          cur_clip->angle = 0;
          cur_clip->clip_type = SPR_PAL;
          cur_clip->w = 0;
          cur_clip->h = 0;
        }
      }
      // printf("Clip #0\nPos: %d, %d\n", cur_motion->spr_clips[0].x,
      //       cur_motion->spr_clips[0].y);
      // printf("Sprite index: %d\n", cur_motion->spr_clips[0].spr_index);
      // printf("Type: %d\n", cur_motion->spr_clips[0].clip_type);

      if (header.version >= 0x200)
        fp.Read(&cur_motion->event_id, 4);
      else
        cur_motion->event_id = -1;
      // printf("Event id: %d\n", cur_motion->event_id);

      if (header.version >= 0x203) {
        fp.Read(&cur_motion->attach_count, 4);
        cur_motion->attach_info.resize(cur_motion->attach_count);
        // printf("%d attach points\n", cur_motion->attach_count);
        for (int k = 0; k < cur_motion->attach_count; k++) {
          ATTACH_POINT_INFO* cur_attach = &cur_motion->attach_info[k];

          fp.Seek(4, SEEK_CUR);  // ?
          fp.Read(cur_attach, sizeof(ATTACH_POINT_INFO));
          // printf("x: %d, y: %d\n", cur_attach->x, cur_attach->y);
        }
      }
    }
  }

  if (header.version >= 0x201) {
    char buffer[40];
    int event_count;

    fp.Read(&event_count, 4);
    m_events.resize(event_count);
    for (int i = 0; i < event_count; i++) {
      fp.Read(buffer, 40);
      m_events[i] = buffer;
    }

    if (header.version >= 0x202) {
      for (int i = 0; i < m_delay.size(); i++) fp.Read(&m_delay[i], 4);
    }
  }

  fp.Close();
  return true;
}

CMotion* CActRes::GetMotion(unsigned int act_index, unsigned int mot_index) {
  if (act_index < m_actions.size())
    return m_actions[act_index].GetMotion(mot_index);
  else
    return NULL;
}

double CActRes::GetDelay(unsigned int act_index) {
  double result;

  if (m_delay.size() && act_index < m_delay.size())
    result = m_delay[act_index];
  else
    result = 4.0;

  return result;
}