#include "Files/ActRes.h"

#include <string.h>

#include "Common/debug.h"
#include "Files/File.h"

#define ACT_RES_HEADER "AC"

#pragma pack(push)
#pragma pack(1)

typedef struct _ActHeader {
  uint16_t magic;
  uint16_t version;
  uint16_t action_count;
  uint8_t reserved[10];
} ActHeader;

#pragma pack(pop)

CActRes::CActRes()
    : m_actions(), m_numMaxClipPerMotion(), m_events(), m_delay() {}

CActRes::~CActRes() {
  m_delay.clear();
  Reset();
}

CRes* CActRes::Clone() { return new CActRes(); }

void CActRes::Reset() {
  m_events.clear();
  m_actions.clear();
}

bool CActRes::Load(const std::string& filename) {
  ActHeader header;
  CFile fp;

  if (!fp.Open(filename, 0)) {
    LOG(error, "Failed to find file: {}", filename);
    return false;
  }

  fp.Read(&header, sizeof(header));
  if (memcmp(&header.magic, ACT_RES_HEADER, sizeof(header.magic)) != 0) {
    LOG(error, "Failed to parse file: {}", filename);
    return false;
  }

  LOG(debug, "ACT file version: {:x}", header.version);
  if (header.version > 0x205) {
    LOG(error, "Unsupported version. Content may be corrupted");
    return false;
  }

  Reset();
  m_actions.resize(header.action_count);

  for (int i = 0; i < header.action_count; i++) {
    CAction* cur_action = &m_actions[i];
    uint32_t motion_count;

    fp.Read(&motion_count, sizeof(motion_count));
    cur_action->Create(motion_count);

    for (uint32_t j = 0; j < motion_count; j++) {
      CMotion cur_motion;
      uint32_t sprite_count;

      fp.Read(&cur_motion.range1, sizeof(cur_motion.range1));
      fp.Read(&cur_motion.range2, sizeof(cur_motion.range2));
      fp.Read(&sprite_count, sizeof(sprite_count));

      if (sprite_count > m_numMaxClipPerMotion) {
        m_numMaxClipPerMotion = sprite_count;
      }

      cur_motion.spr_clips.resize(sprite_count);

      for (uint32_t k = 0; k < sprite_count; k++) {
        SPR_CLIP* cur_clip = &cur_motion.spr_clips[k];

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
          if (header.version <= 0x203) {
            cur_clip->zoomy = cur_clip->zoomx;
          } else {
            fp.Read(&cur_clip->zoomy, 4);
          }
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
          cur_clip->clip_type = SPR_TYPE_PAL;
          cur_clip->w = 0;
          cur_clip->h = 0;
        }
      }

      if (header.version >= 0x200) {
        fp.Read(&cur_motion.event_id, 4);
      } else {
        cur_motion.event_id = -1;
      }

      if (header.version >= 0x203) {
        fp.Read(&cur_motion.attach_count, 4);
        cur_motion.attach_info.resize(cur_motion.attach_count);

        for (int k = 0; k < cur_motion.attach_count; k++) {
          ATTACH_POINT_INFO* cur_attach = &cur_motion.attach_info[k];

          fp.Seek(4, SEEK_CUR);  // ?
          fp.Read(cur_attach, sizeof(*cur_attach));
        }
      }

      cur_action->SetMotion(j, cur_motion);
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
      for (int i = 0; i < m_delay.size(); i++) {
        fp.Read(&m_delay[i], 4);
      }
    }
  }

  fp.Close();
  return true;
}

const CMotion* CActRes::GetMotion(unsigned int act_index,
                            unsigned int mot_index) const {
  if (act_index < m_actions.size()) {
    return m_actions[act_index].GetMotion(mot_index);
  }

  return nullptr;
}

float CActRes::GetDelay(unsigned int act_index) const {
  float result;

  if (!m_delay.empty() && act_index < m_delay.size()) {
    result = m_delay[act_index];
  } else {
    result = 4.f;
  }

  return result;
}
