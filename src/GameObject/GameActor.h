#ifndef DOLORI_GAMEOBJECT_GAMEACTOR_H_
#define DOLORI_GAMEOBJECT_GAMEACTOR_H_

#include "GameObject/AbleToMakeEffect.h"

class CGameActor : public CAbleToMakeEffect {
 protected:
  int m_moveDestX;
  int m_moveDestY;
  unsigned long m_speed;
  int m_isCounter;
  int m_isTrickDead;
  int m_isPlayHitWave;
  int m_isAsuraAttack;
  char* m_emblemWnd;
  char* m_WordDisplayWnd;
  char m_hitWaveName[0x80];
  unsigned long m_colorEndTick;
  short m_clevel;
  short m_MaxHp;
  short m_Hp;
  short m_MaxSp;
  short m_Sp;
  int m_Exp;
  short m_Str;
  short m_Int;
  short m_Dex;
  short m_Vit;
  short m_Luk;
  short m_Agi;
};

// class CGameActor {
//  CAbleToMakeEffect, offset = 0x0
//
//    public void CGameActor(const class CGameActor &)
//    public void CGameActor::CGameActor()
//    public void CGameActor::~CGameActor()
//    public void CGameActor::OnInit()
//    public void CGameActor::OnExit()
//    public unsigned char OnProcess()
//    public unsigned char CGameActor::ProcessState()
//    public void CGameActor::SendMsg(class CGameObject *, int, int, int, int)
//    public void CGameActor::SetRenderInfo(struct RENDER_INFO_RECT &, const
//    float, const float) public void CGameActor::SetState(int) public void
//    CGameActor::RegisterPos() public void CGameActor::UnRegisterPos() public
//    void CGameActor::SetAction(int, int, int) public int
//    CGameActor::Get8Dir(float) public void CGameActor::SetSprAct(int, int)
//    public void CGameActor::SetSprAct(int, int, int, int, int, int, int, int,
//    int, int) public void CGameActor::SetSprAct2(int, int, int, int, int, int,
//    int, int, int, int, int) public void CGameActor::SetSprJob(int) public
//    void CGameActor::SetSprHead(int) public void CGameActor::SetSprJobDye(int)
//    public void CGameActor::SetSprWeapon(int)
//    public void CGameActor::SetSprWeapon2(int)
//    public void CGameActor::SetSprAccessory(int)
//    public void CGameActor::SetSprAccessory2(int)
//    public void CGameActor::SetSprAccessory3(int)
//    public void CGameActor::SetSprShield(int)
//    public void CGameActor::SetSprShoe(int)
//    public void CGameActor::SetImfFileName()
//    public void CGameActor::SetHeadPaletteName()
//    public void CGameActor::SetBodyPaletteName()
//    public void CGameActor::SetBodyPalette(int)
//    public void CGameActor::SetHeadPalette(int)
//    public int CGameActor::GetWeapon()
//    public void CGameActor::ProcessMotionWithDist()
//    public int CGameActor::GetAttackMotion()
//    public void CGameActor::MakeCorpse()
//    public void CGameActor::SetModifyFactorOfmotionSpeed(int)
//    public void CGameActor::SetHonor(int)
//    public void CGameActor::SetPropensityInfo(int, int)
//    public unsigned char CGameActor::FindPath(int, int, int, int, int, int,
//    int) public void CGameActor::ProcessWillBeAttacked() public void
//    CGameActor::MakeSpecialAttackEffect(unsigned long, float) public void
//    CGameActor::CalcAccel(float) public struct vector3d
//    CGameActor::CalcAccel3d(struct vector3d, float) public void
//    CGameActor::ProcessActionWithDir() public void CGameActor::AddDist(struct
//    vector3d &, struct vector3d &) public unsigned long GetGID() public void
//    CGameActor::ProcessChatBalloon() public void
//    CGameActor::DeleteChatBalloon() public void CGameActor::SetJob(int) public
//    int CGameActor::GetJob() public int CGameActor::IsThisPC(int) public void
//    CGameActor::SetSex(int) public int GetSex() public class UIChatRoomTitle *
//    GetChatRoomTitle() public void CGameActor::SetPKState(int) public void
//    CGameActor::SetAttrState(int, int, int, unsigned char) public void
//    CGameActor::ProcessEffectState() public void
//    CGameActor::DeleteMatchingEffect(class CMsgEffect *) public unsigned char
//    CGameActor::ProcessVanish() public void CGameActor::ProcessBodyState()
//    public void CGameActor::SetVanish()
//    public class CMsgEffect * GetBird()
//    public int CGameActor::GetProperJob(int, int)
//    public int CGameActor::GetBodyState()
//    public int CGameActor::GetEffectState()
//    public void SetEffectState(int)
//    public void SetHeadType(int)
//    public int GetHeadType()
//    public int GetActorType()
//    public void CGameActor::Am_Skill(class CGameObject *, int, int, int)
//    public void CGameActor::Am_Action(class CGameObject *, int, int, int)
//    public void CGameActor::Am_Groundskill(class CGameObject *, int, int, int)
//    public void CGameActor::Am_Make_Number(class CGameObject *, int, int, int)
//    public void CGameActor::MakePartyEffect(int)
//    public void CGameActor::DeleteTotalNumber()
//    public void AddMsgEffect(class CMsgEffect *)
//    public int CGameActor::IsDarkEffect(int)
//    public void CGameActor::Delete99LevelEffects()
//    public void CGameActor::SetGuildInfo(int, int)
//    public int CGameActor::GetGdid()
//    public int CGameActor::GetEmblemVersion()
//    public void CGameActor::DeleteEmblemWnd()
//    public void CGameActor::MakeEmblemWnd()
//    public void CGameActor::DeleteWordDisplayWnd()
//    public void CGameActor::MakeWordDisplayWnd()
//    public int CGameActor::IsFreezeState()
//    public void CGameActor::SetGroupMemberAndVisible(int)
//    public int GetGroupMemberAndVisible()
//    public void SetFreezeEndTick(unsigned long)
//    public int GetTargetGid()
//    public struct _MSG2AI & CGameActor::GetMsg2AI(int)
//    public void CGameActor::SetMsg2AI(struct _MSG2AI &, int)
//    public struct _MSG2AI & CGameActor::GetResMsg2AI(int)
//    public void CGameActor::SetResMsg2AI(struct _MSG2AI &, int)
//    public unsigned char CGameActor::HomunAIIsOpened()
//    public unsigned char CGameActor::MerAIIsOpened()
//    /* this+0x118 */ int m_moveDestX
//    /* this+0x11c */ int m_moveDestY
//    /* this+0x120 */ unsigned long m_speed
//    /* this+0x124 */ int m_isCounter
//    /* this+0x128 */ int m_isTrickDead
//    /* this+0x12c */ int m_isPlayHitWave
//    /* this+0x130 */ int m_isAsuraAttack
//    /* this+0x134 */ char * m_emblemWnd
//    /* this+0x138 */ char * m_WordDisplayWnd
//    /* this+0x13c */ char[0x80] m_hitWaveName
//    /* this+0x1bc */ unsigned long m_colorEndTick
//    /* this+0x1c0 */ short m_clevel
//    /* this+0x1c2 */ short m_MaxHp
//    /* this+0x1c4 */ short m_Hp
//    /* this+0x1c6 */ short m_MaxSp
//    /* this+0x1c8 */ short m_Sp
//    /* this+0x1cc */ int m_Exp
//    /* this+0x1d0 */ short m_Str
//    /* this+0x1d2 */ short m_Int
//    /* this+0x1d4 */ short m_Dex
//    /* this+0x1d6 */ short m_Vit
//    /* this+0x1d8 */ short m_Luk
//    /* this+0x1da */ short m_Agi
//    /* this+0x1dc */ struct vector3d m_accel
//
//    /* this+0x1e8 */ class CPathInfo m_path
//
//    /* this+0x204 */ unsigned long m_moveStartTime
//    /* this+0x208 */ unsigned char m_isNeverAnimation
//    /* this+0x20c */ int m_pathStartCell
//    /* this+0x210 */ float m_dist
//    /* this+0x214 */ unsigned long m_lastProcessStateTime
//    /* this+0x218 */ unsigned long m_lastServerTime
//    /* this+0x21c */ unsigned long m_chatTick
//    /* this+0x220 */ unsigned long m_targetGid
//    /* this+0x224 */ float m_attackMotion
//    /* this+0x228 */ int m_isBladeStop
//    /* this+0x22c */ unsigned long m_gid
//    /* this+0x230 */ int m_job
//    /* this+0x234 */ int m_sex
//    /* this+0x238 */ class UIBalloonText * m_balloon
//    /* this+0x23c */ class UIChatRoomTitle * m_chatTitle
//    /* this+0x240 */ class UIMerchantShopTitle * m_merchantShopTitle
//    /* this+0x244 */ class UIRechargeGage * m_skillRechargeGage
//    /* this+0x248 */ unsigned long m_freezeEndTick
//    /* this+0x24c */ unsigned long m_petEmotionStartTick
//    /* this+0x250 */ unsigned long m_skillRechargeEndTick
//    /* this+0x254 */ unsigned long m_skillRechargeStartTick
//    /* this+0x258 */ int m_chatWidth
//    /* this+0x25c */ int m_chatHeight
//    /* this+0x260 */ int m_nameWidth
//    /* this+0x264 */ int m_xSize
//    /* this+0x268 */ int m_ySize
//    /* this+0x26c */ int m_headType
//    /* this+0x270 */ class std::list<WBA, std::allocator<WBA> >
//    m_willBeAttackList
//
//    /* this+0x27c */ class std::list<WBA, std::allocator<WBA> >
//    m_willBeAttackedList
//
//    /* this+0x288 */ int m_willBeDead
//    /* this+0x28c */ int m_is99
//    /* this+0x290 */ char m_99
//    /* this+0x294 */ int m_bodyState
//    /* this+0x298 */ int m_effectState
//    /* this+0x29c */ int m_healthState
//    /* this+0x2a0 */ int m_pkState
//    /* this+0x2a4 */ float m_damageDestX
//    /* this+0x2a8 */ float m_damageDestZ
//    /* this+0x2ac */ unsigned long m_effectLaunchCnt
//    /* this+0x2b0 */ unsigned long m_vanishTime
//    /* this+0x2b4 */ int m_actorType
//    /* this+0x2b8 */ int m_bIsMemberAndVisible
//    /* this+0x2bc */ int m_gdid
//    /* this+0x2c0 */ int m_emblemVersion
//    /* this+0x2c4 */ class CMercenaryAI * m_homunAI
//    /* this+0x2c8 */ class CMercenaryAI * m_merAI
//    /* this+0x2cc */ unsigned char m_objectType
//    /* this+0x2d0 */ struct _MSG2AI m_homunMsg
//
//    /* this+0x2e8 */ struct _MSG2AI m_homunResMsg
//
//    /* this+0x300 */ struct _MSG2AI m_merMsg
//
//    /* this+0x318 */ struct _MSG2AI m_merResMsg
//
//    /* this+0x330 */ class CMsgEffect * m_birdEffect
//    /* this+0x334 */ class CMsgEffect * m_cartEffect
//    /* this+0x338 */ class CMsgEffect * m_pkEffect
//    /* this+0x33c */ class CMsgEffect * m_iceEffect
//    /* this+0x340 */ class CMsgEffect * m_curseEffect
//    /* this+0x344 */ class CMsgEffect * m_sleepEffect
//    /* this+0x348 */ class CMsgEffect * m_stunEffect
//    /* this+0x34c */ class CMsgEffect * m_silenceEffect
//    /* this+0x350 */ class CMsgEffect * m_angelusEffect
//    /* this+0x354 */ class CMsgEffect * m_crusisEffect
//    /* this+0x358 */ class CMsgEffect * m_chatProhibitEffect
//    /* this+0x35c */ class CMsgEffect * m_cursorEffect
//    /* this+0x360 */ class std::list<CMsgEffect *, std::allocator<CMsgEffect
//    *> > m_msgEffectList
//
//    public class CGameActor & operator=(const class CGameActor &)
//    public void __local_vftable_ctor_closure()
//    public void * __vecDelDtor(unsigned int)
//}

#endif /* DOLORI_GAMEOBJECT_GAMEACTOR_H_ */
