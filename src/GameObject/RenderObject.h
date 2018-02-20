#ifndef DOLORI_GAMEOBJECT_RENDEROBJECT_H_
#define DOLORI_GAMEOBJECT_RENDEROBJECT_H_

#include <glm/vec3.hpp>
#include "GameObject.h"

class CRenderObject : public CGameObject {
 public:
  CRenderObject();

  const glm::vec3& GetPos() const;

 protected:
  glm::vec3 m_pos;
};

// class CRenderObject {
//  CGameObject, offset = 0x0
//
//    public void CRenderObject(const class CRenderObject &)
//    public void CRenderObject::CRenderObject()
//    public void CRenderObject::~CRenderObject()
//    public unsigned char CRenderObject::OnProcess()
//    public void CRenderObject::Render(struct matrix &)
//    public void CRenderObject::SetRenderInfo(struct RENDER_INFO_RECT &, const
//    float, const float) public void CRenderObject::SetTlvert(float, float)
//    public void CRenderObject::SendMsg(class CGameObject *, int, int, int,
//    int) public void CRenderObject::SetAction(int, int, int) public void
//    CRenderObject::ProcessMotion() public void CRenderObject::OnInit() public
//    void CRenderObject::OnExit() public void
//    CRenderObject::UpdateTlvertex(struct matrix &) public void
//    CRenderObject::RenderBody(struct matrix &, char) public void
//    CRenderObject::RenderMercenary(struct matrix &, int) public void
//    CRenderObject::RenderShadow(struct matrix &, float) public void
//    CRenderObject::RenderSprite(const struct RPSprite &, unsigned long *, int)
//    public float CRenderObject::CalcDir(float, float, float, float)
//    public void CRenderObject::CalcDir(float, float)
//    public void CRenderObject::ModifyArgb(int, int, int, int)
//    public void CRenderObject::SetArgb(int, int, int, int)
//    public void CRenderObject::ProcessSound()
//    public void CRenderObject::SetLmIntensity(float &, float &, float &)
//    public float CRenderObject::CalcDist(float, float, float)
//    public float CRenderObject::CalcDist(float, float)
//    public float GetStateCnt()
//    public float GetLastPixelRatio()
//    public unsigned char CRenderObject::GetTargetPos(unsigned long, struct
//    vector3d &) public int GetLastTlvertX() public int GetLastTlvertY()
//    /* this+0x4 */ struct vector3d m_pos
//
//    /* this+0x10 */ class std::string m_bodyPaletteName
//
//    /* this+0x20 */ int m_baseAction
//    /* this+0x24 */ int m_curAction
//    /* this+0x28 */ int m_curMotion
//    /* this+0x2c */ int m_oldBaseAction
//    /* this+0x30 */ int m_oldMotion
//    /* this+0x34 */ int m_bodyPalette
//    /* this+0x38 */ float m_roty
//    /* this+0x3c */ float m_zoom
//    /* this+0x40 */ float m_shadowZoom
//    /* this+0x44 */ float m_motionSpeed
//    /* this+0x48 */ float m_lastPixelRatio
//    /* this+0x4c */ float m_loopCountOfmotionFinish
//    /* this+0x50 */ float m_modifyFactorOfmotionSpeed
//    /* this+0x54 */ float m_modifyFactorOfmotionSpeed2
//    /* this+0x58 */ int m_motionType
//    /* this+0x5c */ int m_stateId
//    /* this+0x60 */ int m_oldstateId
//    /* this+0x64 */ int m_sprShift
//    /* this+0x68 */ int m_sprAngle
//    /* this+0x6c */ int m_offsetOow
//    /* this+0x70 */ unsigned long m_colorOfSingleColor
//    /* this+0x74 */ unsigned long m_singleColorStartTick
//    /* this+0x78 */ unsigned long m_stateStartTick
//    /* this+0x7c */ struct ACTOR_COLOR m_oldColor
//
//    /* this+0x80 */ struct ACTOR_COLOR m_curColor
//
//    /* this+0x84 */ unsigned long m_sprArgb
//    /* this+0x84 */ struct COLOR m_sprColor
//
//    /* this+0x88 */ unsigned char m_isLieOnGround
//    /* this+0x89 */ unsigned char m_isMotionFinished
//    /* this+0x8a */ unsigned char m_isMotionFreezed
//    /* this+0x8b */ unsigned char m_isSingleColor
//    /* this+0x8c */ unsigned char m_isVisible
//    /* this+0x8d */ unsigned char m_isVisibleBody
//    /* this+0x8e */ unsigned char m_alwaysTopLayer
//    /* this+0x8f */ unsigned char m_isSprArgbFixed
//    /* this+0x90 */ unsigned char m_shadowOn
//    /* this+0x91 */ unsigned char m_shouldAddPickInfo
//    /* this+0x94 */ int m_isPc
//    /* this+0x98 */ int m_lastTlvertX
//    /* this+0x9c */ int m_lastTlvertY
//    /* this+0xa0 */ unsigned char m_forceAct
//    /* this+0xa1 */ unsigned char m_forceMot
//    /* this+0xa2 */ unsigned char[0x5] m_forceAct2
//    /* this+0xa7 */ unsigned char[0x5] m_forceMot2
//    /* this+0xac */ unsigned char m_forceMaxMot
//    /* this+0xad */ unsigned char m_forceAnimSpeed
//    /* this+0xae */ unsigned char m_forceFinishedAct
//    /* this+0xaf */ unsigned char m_forceFinishedMot
//    /* this+0xb0 */ unsigned char m_forceStartMot
//    /* this+0xb4 */ int m_isForceState
//    /* this+0xb8 */ int m_isForceAnimLoop
//    /* this+0xbc */ int m_isForceAnimation
//    /* this+0xc0 */ int m_isForceAnimFinish
//    /* this+0xc4 */ int m_isForceState2
//    /* this+0xc8 */ int m_isForceState3
//    /* this+0xcc */ unsigned long m_forceStateCnt
//    /* this+0xd0 */ unsigned long m_forceStateEndTick
//    public void CRenderObject::SetForceAnimSpeed(unsigned char)
//    public void CRenderObject::SetForceAnimEndTick(unsigned long)
//    public void CRenderObject::SetForceAnimation(int, int, int, int, int, int,
//    unsigned long, int) public void CRenderObject::SetForceAnimation2(int,
//    int, int, int, int, int, int, int, int, int, int, unsigned long, int)
//    public void CRenderObject::SetForceAnimation3(int, int, int, int, unsigned
//    long, int)
//    /* this+0xd4 */ int m_BodyLight
//    /* this+0xd8 */ char m_BeZero
//    /* this+0xd9 */ char m_BodyFlag
//    /* this+0xda */ unsigned char m_BodySin
//    /* this+0xdb */ unsigned char m_BodySin2
//    /* this+0xdc */ unsigned char m_BodySin3
//    /* this+0xdd */ unsigned char m_BodySin4
//    /* this+0xde */ unsigned char m_BodySin5
//    /* this+0xe0 */ short m_BodyTime
//    /* this+0xe2 */ unsigned char m_BodyTime2
//    /* this+0xe3 */ unsigned char m_BodyTime3
//    /* this+0xe4 */ short m_FlyMove
//    /* this+0xe6 */ unsigned char m_FlyNow
//    /* this+0xe7 */ char m_camp
//    /* this+0xe8 */ short m_charfont
//    /* this+0xea */ unsigned char m_BodyAni
//    /* this+0xeb */ unsigned char m_BodyAct
//    /* this+0xec */ unsigned char m_BodyAniFrame
//    public void CRenderObject::SetSprName(const char *)
//    public const char * CRenderObject::GetSprName()
//    public class CSprRes * CRenderObject::GetSprRes()
//    public void CRenderObject::Palette_BW(class CPaletteRes *)
//    public void CRenderObject::SetActName(const char *)
//    public void CRenderObject::SetCharacterSquare(float *, float *, float *,
//    float *) public void CRenderObject::SetCharacterAngle(float *) public void
//    CRenderObject::SetCharacterPreAngle(int, int *, int *, int *, int *)
//    public void CRenderObject::SetCharacterLight(struct RPSprite, unsigned
//    long *) public void CRenderObject::SetCharacterPixelRatio(float *) public
//    short CRenderObject::SetCharacterFlying() public class CActRes *
//    CRenderObject::SetCharacterActRes(int, int) public class CSprRes *
//    CRenderObject::SetCharacterSprRes(int, int) public const char *
//    CRenderObject::GetActName() public class CActRes *
//    CRenderObject::GetActRes()
//    /* this+0xf0 */ class CSprRes * m_sprRes
//    /* this+0xf4 */ class CActRes * m_actRes
//    public class CRenderObject & operator=(const class CRenderObject &)
//    public void __local_vftable_ctor_closure()
//    public void * __vecDelDtor(unsigned int)
//}

#endif /* DOLORI_GAMEOBJECT_RENDEROBJECT_H_ */