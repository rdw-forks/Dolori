#include "Render/Motion.h"

CMotion::CMotion()
    : range1(),
      range2(),
      spr_clips(),
      attach_info(),
      attach_count(),
      event_id() {}

size_t CMotion::NumberOfClips() const { return spr_clips.size(); }

const SprClip *CMotion::GetClip(size_t clip_number) const {
  if (!spr_clips.empty() && clip_number < spr_clips.size()) {
    return &spr_clips[clip_number];
  }

  return nullptr;
}
