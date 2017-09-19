#include "Motion.h"

CMotion::CMotion() {}

CMotion::~CMotion() {}

int CMotion::NumberOfClips() { return num_clips; }

SPR_CLIP *CMotion::GetClip(unsigned int clip_number) {
  SPR_CLIP *result;

  if (spr_clips.size() && clip_number < spr_clips.size())
    result = &spr_clips[clip_number];
  else
    result = NULL;

  return result;
}
