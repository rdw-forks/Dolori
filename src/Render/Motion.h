#ifndef DOLORI_RENDER_MOTION_H_
#define DOLORI_RENDER_MOTION_H_

#include <vector>

#include "Files/SprRes.h"
#include "Render/attach_point_info.h"
#include "Render/rect.h"

#pragma pack(push)
#pragma pack(1)

typedef struct _SprClip {
  int32_t x;
  int32_t y;
  int32_t spr_index;
  int32_t is_mirror;
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
  float zoomx;
  float zoomy;
  int32_t angle;
  SPR_TYPE clip_type;
  int32_t w;
  int32_t h;
} SprClip;

#pragma pack(pop)

class CMotion {
 public:
  CMotion();

  size_t NumberOfClips() const;
  const SprClip* GetClip(size_t clip_number) const;

 public:
  RECT range1;
  RECT range2;
  std::vector<SprClip> spr_clips;
  std::vector<ATTACH_POINT_INFO> attach_info;
  int attach_count;
  int event_id;
};

// struct CMotion {
//  public void CMotion::Create(unsigned int)
//    public struct CSprClip * CMotion::GetClip(unsigned int)
//    /* this+0x0 */ struct tagRECT range1
//
//    /* this+0x10 */ struct tagRECT range2
//
//    /* this+0x20 */ class std::vector<CSprClip, std::allocator<CSprClip> >
//    sprClips
//
//    /* this+0x30 */ int numClips
//    /* this+0x34 */ int m_eventId
//    /* this+0x38 */ class std::vector<CAttachPointInfo,
//    std::allocator<CAttachPointInfo> > attachInfo
//
//    /* this+0x48 */ int attachCnt
//    public void CMotion(const struct CMotion &)
//    public void CMotion::CMotion()
//    public struct CMotion & CMotion::operator=(const struct CMotion &)
//    public void CMotion::~CMotion()
//    public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_RENDER_MOTION_H_
