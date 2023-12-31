#ifndef DOLORI_RENDER_ACTION_H_
#define DOLORI_RENDER_ACTION_H_

#include <vector>

#include "Render/Motion.h"

class CAction {
 public:
  CAction();

  void Create(unsigned int motion_count);
  void SetMotion(size_t motion_id, CMotion motion);
  const CMotion* GetMotion(size_t motion_id) const;

 private:
  std::vector<CMotion> m_motions;
};

// struct CAction {
//  public void CAction::Create(unsigned int)
//    public struct CMotion * CAction::GetMotion(unsigned int)
//    /* this+0x0 */ class std::vector<CMotion, std::allocator<CMotion> >
//    motions
//
//    public void CAction(const struct CAction &)
//    public void CAction::CAction()
//    public struct CAction & operator=(const struct CAction &)
//    public void CAction::~CAction()
//    public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_RENDER_ACTION_H_
