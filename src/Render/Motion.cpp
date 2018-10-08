#include "Render/Motion.h"

CMotion::CMotion()
    : range1(),
      range2(),
      spr_clips(),
      num_clips(),
      attach_info(),
      attach_count(),
      event_id() {}

int CMotion::NumberOfClips() const { return num_clips; }

const SPR_CLIP *CMotion::GetClip(unsigned int clip_number) const {
  if (!spr_clips.empty() && clip_number < spr_clips.size()) {
    return &spr_clips[clip_number];
  }

  return nullptr;
}
