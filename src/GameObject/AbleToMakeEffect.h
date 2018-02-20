#ifndef DOLORI_GAMEOBJECT_ABLETOMAKEEFFECT_H_
#define DOLORI_GAMEOBJECT_ABLETOMAKEEFFECT_H_

#include <list>
#include "RenderObject.h"

class CAbleToMakeEffect : public CRenderObject {
 protected:
  int m_efId;
  int m_Sk_Level;
  int m_isLoop;
  std::list<class CRagEffect *> m_effectList;
  class CRagEffect *m_beginSpellEffect;
  class CRagEffect *m_magicTargetEffect;
};

// class CAbleToMakeEffect {
//  CRenderObject, offset = 0x0
//
//    public void CAbleToMakeEffect(const class CAbleToMakeEffect &)
//    public void CAbleToMakeEffect::CAbleToMakeEffect()
//    public void CAbleToMakeEffect::~CAbleToMakeEffect()
//    public void CAbleToMakeEffect::SendMsg(class CGameObject *, int, int, int,
//    int) public void CAbleToMakeEffect::OnInit() public void
//    CAbleToMakeEffect::OnExit() public class CRagEffect *
//    CAbleToMakeEffect::LaunchEffect(int, struct vector3d, float) public
//    unsigned char CAbleToMakeEffect::IsExistEffect(class CRagEffect *) public
//    int CAbleToMakeEffect::IsEffectExist(int)
//    /* this+0xf8 */ int m_efId
//    /* this+0xfc */ int m_Sk_Level
//    /* this+0x100 */ int m_isLoop
//    /* this+0x104 */ class std::list<CRagEffect *, std::allocator<CRagEffect
//    *> > m_effectList
//
//    /* this+0x110 */ class CRagEffect * m_beginSpellEffect
//    /* this+0x114 */ class CRagEffect * m_magicTargetEffect
//    public class CAbleToMakeEffect & operator=(const class CAbleToMakeEffect
//    &) public void __local_vftable_ctor_closure() public void *
//    __vecDelDtor(unsigned int)
//}

#endif /* DOLORI_GAMEOBJECT_ABLETOMAKEEFFECT_H_ */