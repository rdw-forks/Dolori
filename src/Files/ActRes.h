#ifndef DOLORI_RENDER_ACTRES_H_
#define DOLORI_RENDER_ACTRES_H_

#include <string>
#include <vector>

#include "Files/Res.h"
#include "Render/Action.h"

class CActRes : public CRes {
 public:
  CActRes();
  ~CActRes();

  CRes* Clone() override;
  void Reset() override;
  bool Load(const std::string& filename) override;

  const CMotion* GetMotion(size_t action_id, size_t motion_id) const;
  float GetDelay(size_t action_id) const;

 private:
  std::vector<CAction> m_actions;
  size_t m_numMaxClipPerMotion;
  std::vector<std::string> m_events;
  std::vector<float> m_delay;
};

// class CActRes {
//  CRes, offset = 0x0
//
//    public void CActRes(const class CActRes &)
//    public void CActRes::CActRes(class Exemplar, const char *, const char *)
//    public void CActRes::CActRes()
//    public class CRes * CActRes::Clone()
//    public unsigned char CActRes::Load(const char *)
//    public void CActRes::Reset()
//    public void CActRes::Create(unsigned int)
//    public struct CAction * CActRes::GetAction(unsigned int)
//    public struct CMotion * CActRes::GetMotion(unsigned int, unsigned int)
//    public int CActRes::GetMotionCount(unsigned int)
//    public int GetActionCount()
//    public float CActRes::GetDelay(unsigned int)
//    public const char * CActRes::GetEventName(int)
//    public void CActRes::ReCalcClipXY(struct CSprClip *, int, int, int, int)
//    public int GetNumMaxClipPerMotion()
//    /* this+0x110 */ class std::vector<CAction, std::allocator<CAction> >
//    actions
//
//    /* this+0x120 */ int numMaxClipPerMotion
//    /* this+0x124 */ class std::vector<std::string, std::allocator<std::string
//    > > m_events
//
//    /* this+0x134 */ class std::vector<float, std::allocator<float> > m_delay
//
//    public class CActRes & operator=(const class CActRes &)
//    public void CActRes::~CActRes()
//    public void __local_vftable_ctor_closure()
//    public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_RENDER_ACTRES_H_
