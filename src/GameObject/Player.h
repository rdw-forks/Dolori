#ifndef DOLORI_GAMEOBJECT_PLAYER_H_
#define DOLORI_GAMEOBJECT_PLAYER_H_

#include "Pc.h"

class CPlayer : public CPc {
 private:
  int m_destCellX;
  int m_destCellZ;
  unsigned long m_attackReqTime;
  unsigned long m_preMoveStartTick;
  // enum PROCEEDTYPE m_proceedType;
  int m_preMoveOn;
  int m_attackMode;
  int m_isAttackRequest;
  int m_isWaitingMoveAck;
  int m_isPreengageStateOfMove;
  unsigned long m_proceedTargetGid;
  unsigned long m_totalAttackReqCnt;
  unsigned long m_tickOfMoveForAttack;
  unsigned long m_moveReqTick;
  unsigned long m_standTick;
  int m_skillId;
  int m_skillAttackRange;
  int m_skillUseLevel;
  int m_gSkillDx;
  int m_gSkillDy;
  int m_preengageXOfMove;
  int m_preengageYOfMove;
};

// class CPlayer {
//  CPc, offset = 0x0
//
//    public void CPlayer(const class CPlayer &)
//    public void CPlayer::CPlayer()
//    public void CPlayer::~CPlayer()
//    public void CPlayer::OnInit()
//    public void CPlayer::OnExit()
//    public unsigned char CPlayer::OnProcess()
//    public unsigned char CPlayer::ProcessState()
//    public void CPlayer::SendMsg(class CGameObject *, int, int, int, int)
//    public void CPlayer::SetState(int)
//    public void CPlayer::RegisterPos()
//    public void CPlayer::UnRegisterPos()
//    public void CPlayer::ProcessProceed()
//    public void CPlayer::ProcessPreengageMove()
//    public void CPlayer::ReLaunchBlurEffects()
//    /* this+0x3f8 */ int m_destCellX
//    /* this+0x3fc */ int m_destCellZ
//    /* this+0x400 */ unsigned long m_attackReqTime
//    /* this+0x404 */ unsigned long m_preMoveStartTick
//    /* this+0x408 */ enum PROCEEDTYPE m_proceedType
//    /* this+0x40c */ int m_preMoveOn
//    /* this+0x410 */ int m_attackMode
//    /* this+0x414 */ int m_isAttackRequest
//    /* this+0x418 */ int m_isWaitingMoveAck
//    /* this+0x41c */ int m_isPreengageStateOfMove
//    /* this+0x420 */ unsigned long m_proceedTargetGid
//    /* this+0x424 */ unsigned long m_totalAttackReqCnt
//    /* this+0x428 */ unsigned long m_tickOfMoveForAttack
//    /* this+0x42c */ unsigned long m_moveReqTick
//    /* this+0x430 */ unsigned long m_standTick
//    /* this+0x434 */ int m_skillId
//    /* this+0x438 */ int m_skillAttackRange
//    /* this+0x43c */ int m_skillUseLevel
//    /* this+0x440 */ int m_gSkillDx
//    /* this+0x444 */ int m_gSkillDy
//    /* this+0x448 */ int m_preengageXOfMove
//    /* this+0x44c */ int m_preengageYOfMove
//    /* this+0x450 */ class CRagEffect * m_statusEffect
//    public class CPlayer & operator=(const class CPlayer &)
//    public void __local_vftable_ctor_closure()
//    public void * __vecDelDtor(unsigned int)
//}

#endif /* DOLORI_GAMEOBJECT_PLAYER_H_ */
