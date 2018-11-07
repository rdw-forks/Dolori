#ifndef DOLORI_MODES_GAMEMODE_H_
#define DOLORI_MODES_GAMEMODE_H_

#include <string>

#include <glm/vec2.hpp>

#include "Modes/Mode.h"
#include "Network/RagConnection.h"
#include "Render/View.h"
#include "Render/World.h"

class CGameMode : public CMode {
 public:
  CGameMode(CRagConnection *p_rag_connection, CUIWindowMgr *p_window_mgr);

  void OnInit(const std::string &mode_name) override;
  int OnRun() override;
  void OnExit() override;
  void *SendMsg(size_t msg, const void *val1 = nullptr,
                const void *val2 = nullptr,
                const void *val3 = nullptr) override;

  void Intialize();
  void OnChangeState(int);
  void OnUpdate();
  void ProcessTalkType(int, const std::string &);
  void ProcessInput();
  void ProcessRightButton();
  void ProcessMouseWheel(int process_type);
  void PollNetworkStatus();
  void Zc_Notify_Playerchat(const char *buffer);
  void Zc_Npcack_Mapmove(const char *buffer);

  const std::string &rsw_name() const;

 private:
  int m_areaLeft;
  int m_areaRight;
  int m_areaTop;
  int m_areaBottom;
  std::string m_rsw_name;
  char m_minimapBmpName[0x3c];
  CWorld m_world;
  CView m_view;
  class CMousePointer *m_mousePointer;
  unsigned long m_leftBtnClickTick;
  static unsigned long m_lastLockOnPcGid;
  static unsigned long m_dwOldAutoFollowTime;
  static unsigned long m_dwOldDisappearTime;
  int m_oldMouseX;
  int m_oldMouseY;
  int m_rBtnClickX;
  int m_rBtnClickY;
  unsigned long m_lastPcGid;
  unsigned long m_lastMonGid;
  unsigned long m_lastLockOnMonGid;
  int m_isAutoMoveClickOn;
  int m_isWaitingWhisperSetting;
  int m_isWaitingEnterRoom;
  int m_isWaitingAddExchangeItem;
  unsigned long m_waitingWearEquipAck;
  unsigned long m_waitingTakeoffEquipAck;
  int m_isReqUpgradeSkillLevel;
  int m_exchangeItemCnt;
  int m_isWaitingCancelExchangeItem;
  int m_noMove;
  unsigned long m_noMoveStartTick;
  int m_isOnQuest;
  int m_isPlayerDead;
  int m_canRotateView;
  int m_hasViewPoint;
  short ViewPointData[0x9];
  int m_receiveSyneRequestTime;
  unsigned long m_syncRequestTime;
  unsigned long m_usedCachesUnloadTick;
  unsigned long m_reqEmotionTick;
  unsigned long m_reqTickChatRoom;
  unsigned long m_reqTickMerchantShop;
  int m_isReqEmotion;
  float m_fixedLongitude;
  unsigned long m_lastCouplePacketAid;
  unsigned long m_lastCouplePacketGid;
  char m_CoupleName[0x18];
  class UINameBalloonText *m_nameBalloon;
  class UINameBalloonText *m_targetNameBalloon;
  class UITransBalloonText *m_broadcastBalloon;
  class UIPlayerGage *m_playerGage;
  class UITransBalloonText *m_skillNameBalloon;
  class UITransBalloonText *m_skillMsgBalloon;
  class UITransBalloonText *m_skillUsedMsgBalloon;
  unsigned long m_skillUsedTick;
  unsigned long m_broadCastTick;
  int m_nameDisplayed;
  int m_nameDisplayed2;
  int m_waitingUseItemAck;
  int m_waitingItemThrowAck;
  int m_waitingReqStatusAck;
  unsigned long m_nameActorAid;
  unsigned long m_lastNaid;
  unsigned long m_menuTargetAID;
  int m_nameBalloonWidth;
  int m_nameBalloonHeight;
  int m_dragType;
  // struct DRAG_INFO m_dragInfo;
  // struct ChatRoomInfo m_lastChatroomInfo;
  // struct SKILL_USE_INFO m_skillUseInfo;
  // struct SHOW_IMAGE_INFO m_showImageInfo;
  std::string m_lastChat;
  int m_sameChatRepeatCnt;
  int m_numNotifyTime;
  int m_isCheckGndAlpha;
  int m_lastCardItemIndex;
  int m_SkillBallonSkillId;
  unsigned long m_nameBalloonType;
  unsigned long m_show_time_start_tick;
  int m_record_chat_num;
  std::string m_recordChat[0xb];
  unsigned long m_recordChatTime[0xb];
  int m_strike_num;
  unsigned long m_strikeTime[0x3];
  unsigned long m_doritime[0x6];
  int m_is_ctrl_lock;
  int m_isUseYgdrasil;
  int m_isMakeYgdrasil;
  int m_auto_save_chat_cnt;
  glm::vec2 m_posOfBossMon;
  unsigned char m_isBossAlarm;
  unsigned char m_onCopyName;
  // CScheduler m_scheduler;
};

// class CGameMode {
//	CMode, offset = 0x0
//
//		 int m_areaLeft
//		 int m_areaRight
//		 int m_areaTop
//		 int m_areaBottom
//		 char[0x28] m_rswName
//		 char[0x3c] m_minimapBmpName
//		 class CWorld * m_world
//		 class CView * m_view
//		 class CMousePointer * m_mousePointer
//		 unsigned long m_leftBtnClickTick
//		 static  unsigned long
// m_lastLockOnPcGid
//		 static  unsigned long
// m_dwOldAutoFollowTime
//		 static  unsigned long
// m_dwOldDisappearTime
//		 int m_oldMouseX
//		 int m_oldMouseY
//		 int m_rBtnClickX
//		 int m_rBtnClickY
//		 unsigned long m_lastPcGid
//		 unsigned long m_lastMonGid
//		 unsigned long m_lastLockOnMonGid
//		 int m_isAutoMoveClickOn
//		 int m_isWaitingWhisperSetting
//		 int m_isWaitingEnterRoom
//		 int m_isWaitingAddExchangeItem
//		 unsigned long m_waitingWearEquipAck
//		 unsigned long m_waitingTakeoffEquipAck
//		 int m_isReqUpgradeSkillLevel
//		 int m_exchangeItemCnt
//		 int m_isWaitingCancelExchangeItem
//		 class std::string m_refuseWhisperName
//
//		 class std::string m_streamFileName
//
//		 class std::string m_lastExchangeCharacterName
//
//		 class std::map<unsigned long, NamePair,
// std::less<unsigned long>, std::allocator<NamePair> > m_actorNameList
//
//		 class std::map<unsigned long, unsigned long,
// std::less<unsigned long>, std::allocator<unsigned long> > m_actorNameReqTimer
//
//		 class std::map<unsigned long, NamePair,
// std::less<unsigned long>, std::allocator<NamePair> > m_actorNameListByGID
//
//		 class std::map<unsigned long, unsigned long,
// std::less<unsigned long>, std::allocator<unsigned long> >
// m_actorNameByGIDReqTimer
//
//		 class std::map<unsigned long, int,
// std::less<unsigned long>, std::allocator<int> > m_guildMemberStatusCache
//
//		 class std::map<unsigned long, CellPos,
// std::less<unsigned long>, std::allocator<CellPos> > m_actorPosList
//
//		 class std::list<unsigned long,
// std::allocator<unsigned long> > m_pickupReqItemNaidList
//
//		 class std::map<unsigned long, unsigned long,
// std::less<unsigned long>, std::allocator<unsigned long> > m_aidList
//
//		 class std::map<unsigned long, ColorCellPos,
// std::less<unsigned long>, std::allocator<ColorCellPos> > m_partyPosList
//
//		 class std::map<unsigned long, ColorCellPos,
// std::less<unsigned long>, std::allocator<ColorCellPos> > m_guildPosList
//
//		 class std::map<unsigned long, ColorCellPos2,
// std::less<unsigned long>, std::allocator<ColorCellPos2> > m_compassPosList
//
//		 class std::vector<int, std::allocator<int> >
// m_menuIdList
//
//		 class std::list<unsigned long,
// std::allocator<unsigned long> > m_visibleTrapList
//
//		 class std::list<unsigned long,
// std::allocator<unsigned long> > m_emblemReqGdidQueue
//
//		 unsigned long m_lastEmblemReqTick
//		 unsigned long m_lastNameWaitingListTick
//		 class std::vector<PLAY_WAVE_INFO,
// std::allocator<PLAY_WAVE_INFO> > m_playWaveList
//
//		 class std::vector<unsigned long,
// std::allocator<unsigned long> > m_KillerList
//
//		 class std::string
// m_lastWhisperMenuCharacterName
//
//		 class std::string m_lastWhisper
//
//		 class std::string m_lastWhisperName
//
//		 int m_noMove
//		 unsigned long m_noMoveStartTick
//		 int m_isOnQuest
//		 int m_isPlayerDead
//		 int m_canRotateView
//		 int m_hasViewPoint
//		 short[0x9] ViewPointData
//		 int m_receiveSyneRequestTime
//		 unsigned long m_syncRequestTime
//		 unsigned long m_usedCachesUnloadTick
//		 unsigned long m_reqEmotionTick
//		 unsigned long m_reqTickChatRoom
//		 unsigned long m_reqTickMerchantShop
//		 int m_isReqEmotion
//		 float m_fixedLongitude
//		 unsigned long m_lastCouplePacketAid
//		 unsigned long m_lastCouplePacketGid
//		 char[0x18] m_CoupleName
//		 class UINameBalloonText * m_nameBalloon
//		 class UINameBalloonText * m_targetNameBalloon
//		 class UITransBalloonText * m_broadcastBalloon
//		 class UIPlayerGage * m_playerGage
//		 class UITransBalloonText * m_skillNameBalloon
//		 class UITransBalloonText * m_skillMsgBalloon
//		 class UITransBalloonText *
// m_skillUsedMsgBalloon
//		 unsigned long m_skillUsedTick
//		 unsigned long m_broadCastTick
//		 int m_nameDisplayed
//		 int m_nameDisplayed2
//		 int m_waitingUseItemAck
//		 int m_waitingItemThrowAck
//		 int m_waitingReqStatusAck
//		 unsigned long m_nameActorAid
//		 unsigned long m_lastNaid
//		 unsigned long m_menuTargetAID
//		 int m_nameBalloonWidth
//		 int m_nameBalloonHeight
//		 int m_dragType
//		 struct DRAG_INFO m_dragInfo
//
//		 struct ChatRoomInfo m_lastChatroomInfo
//
//		 struct SKILL_USE_INFO m_skillUseInfo
//
//		 struct SHOW_IMAGE_INFO m_showImageInfo
//
//		 class std::string m_lastChat
//
//		 int m_sameChatRepeatCnt
//		 int m_numNotifyTime
//		 int m_isCheckGndAlpha
//		 int m_lastCardItemIndex
//		 int m_SkillBallonSkillId
//		 unsigned long m_nameBalloonType
//		 unsigned long m_showTimeStartTick
//		 int m_recordChatNum
//		 class std::string[0xb] m_recordChat
//		 unsigned long[0xb] m_recordChatTime
//		 int m_strikeNum
//		 unsigned long[0x3] m_strikeTime
//		 unsigned long[0x6] m_doritime
//		 int m_isCtrlLock
//		 int m_isUseYgdrasil
//		 int m_isMakeYgdrasil
//		 int m_autoSaveChatCnt
//		 struct CellPos m_posOfBossMon
//
//		 unsigned char m_isBossAlarm
//		 unsigned char m_onCopyName
//		 class CScheduler m_scheduler
//
//		private void CGameMode::OnChangeState(int)
//		private void ProcessNeverDie()
//		private void CGameMode::PollNetworkStatus()
//		private void CGameMode::OnProcessState(int)
//		private void CGameMode::DeleteCompassPos(int)
//		private void CGameMode::MakeNameBalloonTextWindow(class UIWindow
//*
//*)
//		private void CGameMode::MoveBalloonTextWindow(class UIWindow *,
// class CRenderObject *) 		private void
// CGameMode::ProcessAutoFollow() 		private void
// CGameMode::MonsterTalk(class CGameActor *, int, int, int, unsigned long)
//		private void CGameMode::DrawMinimapTriangle(float, float, float,
// unsigned long) 		private void
// CGameMode::SetMemberVisibleState(unsigned long, int) 		private
// int  CGameMode::IsExceptionState(int) 		private void
// CGameMode::DrawBossMonsterOnMiniMap(const struct UVRECT &)
//		public void CGameMode(const class CGameMode &)
//		public void CGameMode::CGameMode()
//		public void CGameMode::OnInit(const char *)
//		public int CGameMode::OnRun()
//		public void CGameMode::OnExit()
//		public void CGameMode::OnUpdate()
//		public int CGameMode::SendMsg(int, int, int, int)
//		public class CWorld * CGameMode::GetWorld()
//		public class CView * GetView()
//		public void CGameMode::ChatDori()
//		public void CGameMode::Initialize()
//		public void CGameMode::MakeFog(int)
//		public void CGameMode::PlayBGM()
//		public void CGameMode::SetCheckGndAlpha()
//		public void CGameMode::SetCamera()
//		public void CGameMode::SaveCamera()
//		public void CGameMode::PushGameObject(class CGameObject *)
//		public void CGameMode::RemoveGameActorAllAndMake()
//		public void MakeMousePointer(struct vector2d &)
//		public void CGameMode::MakeMenu(class CActorPickInfo *, int)
//		public void CGameMode::ProcessMouseSnap(class CActorPickInfo *,
// int) 		public void CGameMode::ProcessWheel(int)
// public  void CGameMode::ProcessRBtn() 		public int
// CGameMode::ProcessGroundPick(int) 		public void
// CGameMode::ProceedAttack(unsigned long, int) 		public unsigned
// char  CGameMode::AttackSkillOverWeightMessage() 		public void
// CGameMode::UnloadRarelyUsedCaches() 		public void
// CGameMode::ProcessReqEmblem() 		public void
// CGameMode::ProcessPeriodicalJobs() 		public void
// CGameMode::ProcessNameWaitingTimer() 		public void
// CGameMode::GetServerCoor(float, float, int &, int &, int &, int &)
//		public void CGameMode::GetServerCoor(float, float, int &, int &)
//		public void CGameMode::GetClientCoor(int, int, int, int, float
//&,  float &) 		public void CGameMode::GetClientCoor(int, int, float &,
// float &)
//		public void CGameMode::ConvertToNumCellClose(int &, int &, int
//&,  int &, int) 		public void CGameMode::ConvertToNoRedCell(int &,
// int &, int &, int
//&)
//		public void
// CGameMode::ConvertToNumCellCloseAndFindNoRedCell(float, float, float, float,
// int &, int &, int)
//		public unsigned char CGameMode::IsInsideCell(int &, int &, int
//&,  int &, int) 		public unsigned char CGameMode::IsRedCell(int,
// int) 		public int CGameMode::GetCellFlag(int, int)
// public
// unsigned char CGameMode::IsValidCell(int, int) 		public unsigned
// char CGameMode::CanFindPath(int, int, int, int,  int, int) 		public
// unsigned char CGameMode::GetClosestValidCell(int &, int
//&) 		public unsigned char CGameMode::IsRegisterCell(int, int)
//		public void CGameMode::MakeGroundMousePointer()
//		public void CGameMode::ShowMousePointer(float, float, int)
//		public void CGameMode::HideMousePointer(int)
//		public void CGameMode::SynchronizeTimeWithServer(unsigned char)
//		public void CGameMode::ProcessInput()
//		public unsigned char CGameMode::GetGroundAttrPos(int &, int &)
//		public void RecalcAveragePingTime(unsigned long)
//		public int CGameMode::ProcessObjClick(class CActorPickInfo *,
// int) 		public const struct NamePair &
// CGameMode::GetNullNamePair() 		public unsigned long
// CGameMode::GetActorNameRequestTimer(unsigned  long) 		public void
// CGameMode::RemoveActorNameRequestTimer(unsigned long) 		public
// const struct NamePair & CGameMode::GetActorName(unsigned long)
//		public void CGameMode::RequestActorName(unsigned long)
//		public unsigned long
// CGameMode::GetActorNameByGIDRequestTimer(unsigned long) 		public
// void CGameMode::RemoveActorNameByGIDRequestTimer(unsigned long)
//		public const struct NamePair &
// CGameMode::GetActorNameByGID(unsigned long) 		public void
// CGameMode::RequestActorNameByGID(unsigned long) 		public void
// CGameMode::CheckGuildMemberStatusCache(unsigned long, const struct NamePair
// &) 		public unsigned long CGameMode::GetActorNameColor(int, unsigned
// long) 		public void CGameMode::MakeNameBalloon(unsigned long)
//		public void CGameMode::MakeActorNameBalloon(class CGameActor *)
//		public void CGameMode::MakeAttackedActorNameBalloon(class
// CGameActor *) 		public void CGameMode::ProcessNameBalloon()
//		public void CGameMode::DeleteBroadcastBalloon()
//		public class CGameActor * CGameMode::MakeGameActor(int)
//		public class CGameActor * CGameMode::NewNpc(int)
//		public void CGameMode::PlaceEffect(struct vector3d *, int, int,
// int) 		public void CGameMode::MakeBlowEffect(float, float,
// float)
//		public void CGameMode::MakeArrowEffect(struct vector3d &,
// unsigned  long, float, int) 		public void
// CGameMode::MakeArrowEffectPos(struct  vector3d &, struct vector3d &, float)
// public void  CGameMode::MakeMandraAttackEffect(unsigned long, int, float)
//		public void CGameMode::MakeCorpse(float, float, float, const
// char
//*, const char *, int, int, float) 		public void
// CGameMode::MakeCorpse3d(float, float, float, const char *, int, float, struct
// vector3d, float) 		public void CGameMode::MakeGrannyCorpse3d(float,
// float, float, float, const char *) 		public void
// CGameMode::MakePotionEffect(int, unsigned long) 		public void
// CGameMode::MakeNumEffect(struct vector3d &, int, unsigned long, unsigned
// long) 		public class CMsgEffect *
// CGameMode::MakeMissEffect(struct  vector3d &, unsigned long, unsigned long)
//		public class CMsgEffect * CGameMode::MakeEmotion(struct vector3d
//&, int, unsigned long) 		public class CMsgEffect *
// CGameMode::MakeMsgEffect(enum MAKE_MSG_EFFECT_TYPE, struct vector3d &,
// unsigned long) 		public void CGameMode::MakeEmblemWnd(class
// CGameActor *, int, int) 		public void
// CGameMode::MakeWordDisplayWnd(class CGameActor *) 		public void
// CGameMode::InvalidatePlayerGage() 		public void
// CGameMode::HideCheck() 		public void DrawCompass()
//		public void CGameMode::DrawMiniMap()
//		public void CGameMode::DrawActorsOnMiniMap(const struct UVRECT
//&) 		public void CGameMode::DrawCompassOnMiniMap(const struct UVRECT
//&) 		public void CGameMode::DrawPKRanking() 		public void
// CGameMode::DrawPKZoneTime()
//		public void CGameMode::DrawTime(unsigned long, int)
//		public void CGameMode::DrawTimeAttack()
//		public void CGameMode::ShowTime()
//		public void CGameMode::AutoStatusUp()
//		public void CGameMode::CheckFrame()
//		public void DrawArenaRemainTime()
//		public void CGameMode::DrawDragImage()
//		public void CGameMode::DrawIllustImage()
//		public void CGameMode::DrawUseSkillLevelNumber()
//		public void CGameMode::RotatePoint(float, float, float &, float
//&,  int) 		public const char * CGameMode::GetDragItemName()
//		public struct DRAG_INFO * GetDragInfo()
//		public enum ENUM_DRAGTYPE GetDragType()
//		public int CanRotateView()
//		public int GetNumDragItem()
//		public int GetDragItemIndex()
//		public struct ChatRoomInfo * GetLastChatroomInfo()
//		public unsigned long CGameMode::GetAid(const char *)
//		public void CGameMode::ProcessTalkType(int, int)
//		public void CGameMode::ProcessLockOnMouse()
//		public void CGameMode::ProcessDamageSituation()
//		public void CGameMode::GainExp(short, int)
//		public int CGameMode::GetNextExpValue(short)
//		public short CGameMode::GetWeaponPower(int)
//		public int CGameMode::GetWeaponCost(int)
//		public void CGameMode::ProcessAssignAID()
//		public int CGameMode::ProcessActorPick(int, class CActorPickInfo
//*)
//		public void CGameMode::ProcessPcPick(int &, class CActorPickInfo
//*, class CGameActor *) 		public void
// CGameMode::ProcessMonsterPick(int &, class CActorPickInfo *, class CGameActor
//*) 		public void CGameMode::WriteNameBalloonPosToReg()
//		public void CGameMode::InitNameBalloonPosFromReg()
//		public unsigned char CGameMode::IsReqPickupItemNaid(unsigned
// long) 		public void CGameMode::RemovePickupItemNaid(unsigned
// long) 		public void CGameMode::AddPickupItemNaid(unsigned long)
//		public void CGameMode::ProcessPlayWave()
//		public void CGameMode::ResetDrag()
//		public void CGameMode::PrintDebugString()
//		public int GetSkillAttackRange()
//		public int IsPlayerDead()
//		public void SetWaitUseItemAck(int)
//		public void CGameMode::WriteRagPathToReg()
//		public unsigned char CGameMode::IsKillerAid(unsigned long)
//		public unsigned char CGameMode::HaveSiegfriedItem()
//		public unsigned char CGameMode::HaveBookItem(int)
//		public void CGameMode::ProceedSkillToFriendList(unsigned long)
//		public void CGameMode::InsertScheduler()
//		public const char * CGameMode::SetPaddingValue(char *, int)
//		public void CGameMode::Zc_Notify_Standentry(const char *)
//		public void CGameMode::Zc_Notify_Newentry(const char *)
//		public void CGameMode::Zc_Refuse_Quit(const char *)
//		public void CGameMode::Zc_Notify_Move(const char *)
//		public void CGameMode::Zc_Notify_Playermove(const char *)
//		public void CGameMode::Zc_Notify_Act(unsigned long, unsigned
// long,  unsigned long, int, int, int, short, unsigned char, int)
//		public void CGameMode::Zc_Notify_Playerchat(const char *)
//		public void CGameMode::Zc_Notify_Chat(const char *)
//		public void CGameMode::Zc_Notify_Time(const char *)
//		public void CGameMode::Zc_Npcack_Mapmove(const char *)
//		public void CGameMode::Zc_Npcack_Enable(const char *)
//		public void CGameMode::Zc_Npcack_Servermove(const char *)
//		public void CGameMode::Zc_Accept_Enter(const char *)
//		public void CGameMode::Zc_Accept_Enter2(const char *)
//		public void CGameMode::Zc_Ack_Reqname(const char *)
//		public void CGameMode::Zc_Broadcast(const char *)
//		public void CGameMode::Zc_BroadCast_HP(int)
//		public void CGameMode::Zc_Whisper(const char *)
//		public void CGameMode::Zc_Ack_Whisper(const char *)
//		public void CGameMode::Zc_Change_Direction(const char *)
//		public void CGameMode::Zc_Ack_Disconnect_Character(const char *)
//		public void CGameMode::Zc_Item_Entry(const char *)
//		public void CGameMode::Zc_Item_Pickup_Ack(const char *)
//		public void CGameMode::Zc_Item_Disappear(const char *)
//		public void CGameMode::Zc_Notify_Actentry(const char *)
//		public void CGameMode::Zc_Notify_Moveentry(const char *)
//		public void CGameMode::Zc_Notify_Vanish(const char *)
//		public void CGameMode::Sc_Notify_Ban(const char *)
//		public void CGameMode::Zc_Accept_Quit(const char *)
//		public void CGameMode::Zc_Normal_Itemlist(const char *)
//		public void CGameMode::Zc_Normal_Itemlist2(const char *)
//		public void CGameMode::Zc_Normal_Itemlist3(const char *)
//		public void CGameMode::Zc_Equipment_Itemlist(const char *)
//		public void CGameMode::Zc_Item_Fall_Entry(const char *)
//		public void CGameMode::Zc_Stopmove(const char *)
//		public void CGameMode::Zc_HighJump(const char *)
//		public void CGameMode::Zc_Par_Change(const char *)
//		public void CGameMode::Zc_Longpar_Change(const char *)
//		public void CGameMode::Zc_Use_Item_Ack(const char *)
//		public void CGameMode::Zc_Req_Wear_Equip_Ack(const char *)
//		public void CGameMode::Zc_Req_Takeoff_Equip_Ack(const char *)
//		public void CGameMode::Zc_Item_Throw_Ack(const char *)
//		public void CGameMode::Zc_Notify_Standentry_Npc(const char *)
//		public void CGameMode::Zc_Say_Dialog(const char *)
//		public void CGameMode::Zc_Wait_Dialog(const char *)
//		public void CGameMode::Zc_Close_Dialog(const char *)
//		public void CGameMode::Zc_Menu_List(const char *)
//		public void CGameMode::Zc_Restart_Ack(const char *)
//		public void CGameMode::Zc_Status_Change_Ack(const char *)
//		public void CGameMode::Zc_Status(const char *)
//		public void CGameMode::Zc_Status_Change(const char *)
//		public void CGameMode::Zc_Emotion(const char *)
//		public void CGameMode::Zc_User_Count(const char *)
//		public void CGameMode::Zc_Sprite_Change(const char *)
//		public void CGameMode::Zc_Select_Dealtype(const char *)
//		public void CGameMode::Zc_Pc_Purchase_Itemlist(const char *)
//		public void CGameMode::Zc_Pc_Sell_Itemlist(const char *)
//		public void CGameMode::Zc_Pc_Purchase_Result(const char *)
//		public void CGameMode::Zc_Pc_Sell_Result(const char *)
//		public void CGameMode::Zc_Setting_Whisper_Pc(const char *)
//		public void CGameMode::Zc_Setting_Whisper_State(const char *)
//		public void CGameMode::Zc_Whisper_List(const char *)
//		public void CGameMode::Zc_Ack_Create_Chatroom(const char *)
//		public void CGameMode::Zc_Room_Newentry(const char *)
//		public void CGameMode::Zc_Destroy_Room(const char *)
//		public void CGameMode::Zc_Enter_Room(const char *)
//		public void CGameMode::Zc_Member_Newentry(const char *)
//		public void CGameMode::Zc_Member_Exit(const char *)
//		public void CGameMode::Zc_Role_Change(const char *)
//		public void CGameMode::Zc_Refuse_Enter_Room(const char *)
//		public void CGameMode::Zc_Change_Chatroom(const char *)
//		public void CGameMode::Zc_Req_Exchange_Item(const char *)
//		public void CGameMode::Zc_Req_Exchange_Item2(const char *)
//		public void CGameMode::Zc_Ack_Exchange_Item(const char *)
//		public void CGameMode::Zc_Ack_Exchange_Item2(const char *)
//		public void CGameMode::Zc_Add_Exchange_Item(const char *)
//		public void CGameMode::Zc_Ack_Add_Exchange_Item(const char *)
//		public void CGameMode::Zc_Conclude_Exchange_Item(const char *)
//		public void CGameMode::Zc_Cancel_Exchange_Item(const char *)
//		public void CGameMode::Zc_Exec_Exchange_Item(const char *)
//		public void CGameMode::Zc_Store_Normal_Itemlist(const char *)
//		public void CGameMode::Zc_Store_Normal_Itemlist2(const char *)
//		public void CGameMode::Zc_Store_Normal_Itemlist3(const char *)
//		public void CGameMode::Zc_Store_Equipment_Itemlist(const char *)
//		public void CGameMode::Zc_Add_Item_To_Store(const char *)
//		public void CGameMode::Zc_Delete_Item_From_Store(const char *)
//		public void CGameMode::Zc_Close_Store(const char *)
//		public void CGameMode::Zc_Notify_Storeitem_Countinfo(const char
//*) 		public void CGameMode::Zc_Ack_Make_Group(const char *)
//		public void CGameMode::Zc_Group_List(const char *)
//		public void CGameMode::Zc_Ack_Req_Join_Group(const char *)
//		public void CGameMode::Zc_Req_Join_Group(const char *)
//		public void CGameMode::Zc_Req_Couple(const char *)
//		public void CGameMode::Zc_StarPlace(const char *)
//		public void CGameMode::Zc_NotifyBindOnEquip(const char *)
//		public void CGameMode::Zc_Battlefield_Notify_Campinfo(const char
//*) 		public void CGameMode::Zc_Battlefield_Chat(const char *)
//		public void CGameMode::Zc_Battlefield_Notify_Point(const char *)
//		public void CGameMode::Zc_Battlefield_Notify_Position(const char
//*) 		public void CGameMode::Zc_Battlefield_Notify_Hp(const char *)
//		public void CGameMode::Zc_Notify_Font(const char *)
//		public void CGameMode::Zc_Progress(const char *)
//		public void CGameMode::Zc_Progress_Cancel(const char *)
//		public void CGameMode::Zc_Req_Baby(const char *)
//		public void CGameMode::Zc_StarSkill(const char *)
//		public void CGameMode::Zc_Ack_Status_GM(const char *)
//		public void CGameMode::Zc_Add_Member_To_Group(const char *)
//		public void CGameMode::Zc_Add_Member_To_Group2(const char *)
//		public void CGameMode::Zc_Delete_Member_From_Group(const char *)
//		public void CGameMode::Zc_Notify_Hp_To_Groupm(const char *)
//		public void CGameMode::Zc_Notify_Position_To_Groupm(const char
//*) 		public void CGameMode::Zc_Notify_Chat_Party(const char *)
//		public void CGameMode::Zc_Exchangeitem_Undo(const char *)
//		public void CGameMode::Zc_Mvp_Getting_Item(const char *)
//		public void CGameMode::Zc_Mvp_Getting_Special_Exp(const char *)
//		public void CGameMode::Zc_Mvp(const char *)
//		public void CGameMode::Zc_Throw_Mvpitem(const char *)
//		public void CGameMode::Zc_Skillinfo_Update(const char *)
//		public void CGameMode::Zc_Skillinfo_List(const char *)
//		public void CGameMode::Zc_All_Quest_List(const char *)
//		public void CGameMode::Zc_All_Quest_Mission(const char *)
//		public void CGameMode::Zc_Update_Mission_Hunt(const char *)
//		public void CGameMode::Zc_Active_Quest(const char *)
//		public void CGameMode::Zc_Add_Quest(const char *)
//		public void CGameMode::Zc_Del_Quest(const char *)
//		public void CGameMode::Zc_Ack_Touseskill(const char *)
//		public void CGameMode::Zc_SKILLMSG(const char *)
//		public void CGameMode::Zc_BABYMSG(const char *)
//		public void CGameMode::Zc_Add_Skill(const char *)
//		public void CGameMode::Zc_Notify_Skill(const char *)
//		public void CGameMode::Zc_Notify_Groundskill(const char *)
//		public void CGameMode::Zc_State_Change(const char *)
//		public void CGameMode::Zc_State_Change3(const char *)
//		public void CGameMode::Zc_Use_Skill(const char *)
//		public void CGameMode::Zc_Skill_Entry(const char *)
//		public void CGameMode::Zc_Skill_Disappear(const char *)
//		public void CGameMode::Zc_Notify_Act_Position(const char *)
//		public void CGameMode::Zc_Notify_Skill_Position(const char *)
//		public void CGameMode::Zc_Warplist(const char *)
//		public void CGameMode::Zc_Ack_Remember_Warppoint(const char *)
//		public void CGameMode::Zc_Notify_Cartitem_Countinfo(const char
//*) 		public void CGameMode::Zc_Cart_Normal_Itemlist(const char *)
//		public void CGameMode::Zc_Cart_Normal_Itemlist2(const char *)
//		public void CGameMode::Zc_Cart_Normal_Itemlist3(const char *)
//		public void CGameMode::Zc_Cart_Equipment_Itemlist(const char *)
//		public void CGameMode::Zc_Cartoff(const char *)
//		public void CGameMode::Zc_Ack_Additem_To_Cart(const char *)
//		public void CGameMode::Zc_Add_Item_To_Cart(const char *)
//		public void CGameMode::Zc_Delete_Item_From_Cart(const char *)
//		public void CGameMode::Zc_openstore(const char *)
//		public void CGameMode::Zc_store_entry(const char *)
//		public void CGameMode::Zc_disappear_entry(const char *)
//		public void CGameMode::Zc_pc_purchase_itemlist_frommc(const char
//*) 		public void CGameMode::Zc_pc_purchase_result_frommc(const char
//*) 		public void CGameMode::Zc_pc_purchase_myitemlist(const char *)
//		public void CGameMode::Zc_deleteitem_from_mcstore(const char *)
//		public void CGameMode::Zc_attack_failure_for_distance(const char
//*) 		public void CGameMode::Zc_attack_range(const char *)
//		public void CGameMode::Zc_action_failure(const char *)
//		public void CGameMode::Zc_equip_arrow(const char *)
//		public void CGameMode::Zc_recovery(const char *)
//		public void CGameMode::Zc_useskill_ack(const char *)
//		public void CGameMode::Zc_groupinfo_change(const char *)
//		public void CGameMode::Zc_couplestatus(const char *)
//		public void CGameMode::Zc_open_editdlg(const char *)
//		public void CGameMode::Zc_compass(const char *)
//		public void CGameMode::Zc_show_image(const char *)
//		public void CGameMode::Zc_show_image2(const char *)
//		public void CGameMode::Zc_autorun_skill(const char *)
//		public void CGameMode::Zc_resurrection(const char *)
//		public void CGameMode::Zc_guild_emblem_img(const char *)
//		public void CGameMode::Zc_guild_info(const char *)
//		public void CGameMode::Zc_myguild_basic_info(const char *)
//		public void CGameMode::Zc_ack_guild_menuinterface(const char *)
//		public void CGameMode::Zc_position_id_name_info(const char *)
//		public void CGameMode::Zc_ack_req_change_members(const char *)
//		public void CGameMode::Zc_membermgr_info(const char *)
//		public void CGameMode::Zc_ack_open_member_info(const char *)
//		public void CGameMode::Zc_ack_leave_guild(const char *)
//		public void CGameMode::Zc_ack_ban_guild(const char *)
//		public void CGameMode::Zc_ack_disorganize_guild_result(const
// char
//*) 		public void CGameMode::Zc_ack_disorganize_guild(const char *)
//		public void CGameMode::Zc_position_info(const char *)
//		public void CGameMode::Zc_ban_list(const char *)
//		public void CGameMode::Zc_other_guild_list(const char *)
//		public void CGameMode::Zc_result_make_guild(const char *)
//		public void CGameMode::Zc_ack_req_join_guild(const char *)
//		public void CGameMode::Zc_req_join_guild(const char *)
//		public void CGameMode::Zc_update_gdid(const char *)
//		public void CGameMode::Zc_update_charstat(const char *)
//		public void CGameMode::Zc_update_charstat2(const char *)
//		public void CGameMode::Zc_ack_give_manner_point(const char *)
//		public void CGameMode::Zc_notify_manner_point_given(const char
//*) 		public void CGameMode::Zc_guild_notice(const char *)
//		public void CGameMode::Zc_guild_chat(const char *)
//		public void CGameMode::Zc_req_ally_guild(const char *)
//		public void CGameMode::Zc_ack_req_ally_guild(const char *)
//		public void CGameMode::Zc_ack_change_guild_positioninfo(const
// char
//*) 		public void CGameMode::Zc_itemidentify_list(const char *)
//		public void CGameMode::Zc_ack_itemidentify(const char *)
//		public void CGameMode::Zc_itemcomposition_list(const char *)
//		public void CGameMode::Zc_ack_itemcomposition(const char *)
//		public void CGameMode::Zc_ack_req_hostile_guild(const char *)
//		public void CGameMode::Zc_member_add(const char *)
//		public void CGameMode::Zc_delete_related_guild(const char *)
//		public void CGameMode::Zc_add_related_guild(const char *)
//		public void CGameMode::Zc_Notify_Position_To_Guildm(const char
//*) 		public void CGameMode::Zc_Guild_Member_Map_Change(const char *)
//		public void CGameMode::Zc_ack_itemrefining(const char *)
//		public void CGameMode::Zc_notify_mapinfo(const char *)
//		public void CGameMode::Zc_ack_req_disconnect(const char *)
//		public void CGameMode::Zc_monster_info(const char *)
//		public void CGameMode::Zc_makable_item_list(const char *)
//		public void CGameMode::Zc_repair_item_list(const char *)
//		public void CGameMode::Zc_notify_weapon_item_list(const char *)
//		public void CGameMode::Zc_ack_weaponrefine(const char *)
//		public void CGameMode::Zc_ack_itemrepair(const char *)
//		public void CGameMode::Zc_ack_req_itemmaking(const char *)
//		public void CGameMode::Zc_talkbox_chat_contents(const char *)
//		public void CGameMode::Zc_update_mapinfo(const char *)
//		public void CGameMode::Zc_Ack_Reqname_bygid(const char *)
//		public void CGameMode::Zc_Ack_Reqnameall(const char *)
//		public void CGameMode::Zc_Msg_State_Change(const char *)
//		public void CGameMode::Zc_Npc_Showefst_Update(const char *)
//		public void CGameMode::Zc_Notify_Mapproperty(const char *)
//		public void CGameMode::Zc_Notify_Ranking(const char *)
//		public void CGameMode::Zc_Notify_Effect(const char *)
//		public void CGameMode::Zc_Notify_Effect2(const char *)
//		public void CGameMode::Zc_Notify_Effect3(const char *)
//		public void CGameMode::Zc_Start_Capture(const char *)
//		public void CGameMode::Zc_Start_Couple(const char *)
//		public void CGameMode::Zc_Start_Baby(const char *)
//		public void CGameMode::Zc_CoupleName(const char *)
//		public void CGameMode::Zc_Congratulation(const char *)
//		public void CGameMode::Zc_TryCapture_Monster(const char *)
//		public void CGameMode::Zc_Change_Pet_Status(const char *)
//		public void CGameMode::Zc_PetEgg_List(const char *)
//		public void CGameMode::Zc_Property_Pet(const char *)
//		public void CGameMode::Zc_Feed_Pet(const char *)
//		public void CGameMode::Zc_Pet_Act(const char *)
//		public void CGameMode::Zc_Par_Change_User(const char *)
//		public void CGameMode::Zc_Skill_Update(const char *)
//		public void CGameMode::Zc_MakingArrowList(const char *)
//		public void CGameMode::Zc_MakingItemList(const char *)
//		public void CGameMode::Zc_ChangeCartList(const char *)
//		public void CGameMode::Zc_NpcSpriteChange(const char *)
//		public void CGameMode::Zc_ShowDigit(const char *)
//		public void CGameMode::Zc_ChangeGuild(const char *)
//		public void CGameMode::Zc_GuildInfo2(const char *)
//		public void CGameMode::Zc_GuildZenyAck(const char *)
//		public void CGameMode::Zc_Dispel(const char *)
//		public void CGameMode::Zc_Reply_RemainTime(const char *)
//		public void CGameMode::Zc_Info_RemainTime(const char *)
//		public void CGameMode::Zc_Broadcast2(const char *)
//		public void CGameMode::Zc_GuildSkillInfo(const char *)
//		public void CGameMode::Zc_AddItemToStore2(const char *)
//		public void CGameMode::Zc_Add_Item_To_Cart2(const char *)
//		public void CGameMode::Sc_Ack_Encryption(const char *)
//		public void CGameMode::Zc_Use_Item_Ack2(const char *)
//		public void CGameMode::Zc_Skill_Entry2(const char *)
//		public void CGameMode::Zc_Monster_Talk(const char *)
//		public void CGameMode::Zc_AutoSpellList(const char *)
//		public void CGameMode::Zc_DevotionList(const char *)
//		public void CGameMode::Zc_Spirits(const char *)
//		public void CGameMode::Zc_Spirits2(const char *)
//		public void CGameMode::Zc_BladeStop(const char *)
//		public void CGameMode::Zc_Sound(const char *)
//		public void CGameMode::Zc_Open_EditDlgStr(const char *)
//		public void CGameMode::Zc_ComboDelay(const char *)
//		public void CGameMode::Zc_Notify_Mapproperty2(const char *)
//		public void CGameMode::Zc_Sprite_Change2(const char *)
//		public void CGameMode::Zc_Notify_Newentry2(const char *)
//		public void CGameMode::Zc_Notify_Standentry2(const char *)
//		public void CGameMode::Zc_Notify_Moveentry2(const char *)
//		public void CGameMode::Zc_Notify_Standentry3(const char *)
//		public void CGameMode::Zc_Notify_Standentry4(const char *)
//		public void CGameMode::Zc_Notify_Entry_HP(int, short, short)
//		public void CGameMode::Zc_Notify_Entry_Mob(int, int, short,
// short) 		public void CGameMode::Zc_Notify_Newentry3(const char *)
//		public void CGameMode::Zc_Notify_Newentry4(const char *)
//		public void CGameMode::Zc_Notify_Moveentry3(const char *)
//		public void CGameMode::Zc_Notify_Moveentry4(const char *)
//		public void CGameMode::GameModeShowEFST(int, int, int, int)
//		public void CGameMode::Zc_Notify_Skill2(const char *)
//		public void CGameMode::Zc_Ack_AccountName(const char *)
//		public void CGameMode::Zc_Friends_List(const char *)
//		public void CGameMode::Zc_Req_Join_Friend(const char *)
//		public void CGameMode::Zc_Add_Friends_List(const char *)
//		public void CGameMode::Zc_Req_Delete_Friend(const char *)
//		public void CGameMode::Zc_Friends_State(const char *)
//		public void CGameMode::Zc_Divorce(const char *)
//		public void CGameMode::ZC_BLACKSMITH_RANK(const char *)
//		public void CGameMode::ZC_ALCHEMIST_RANK(const char *)
//		public void CGameMode::ZC_TAEKWON_RANK(const char *)
//		public void CGameMode::ZC_GANGSI_RANK(const char *)
//		public void CGameMode::ZC_BLACKSMITH_POINT(const char *)
//		public void CGameMode::ZC_ALCHEMIST_POINT(const char *)
//		public void CGameMode::ZC_TAEKWON_POINT(const char *)
//		public void CGameMode::ZC_GANGSI_POINT(const char *)
//		public void CGameMode::ZC_DEATH_QUESTION(const char *)
//		public void CGameMode::Zc_Ack_PvpPoint(const char *)
//		public void CGameMode::Zc_Notify_PKinfo(const char *)
//		public void CGameMode::Zc_Notify_CrazyKiller(const char *)
//		public void CGameMode::Zc_Game_Guard(const char *)
//		public void CGameMode::Zc_Change_Mer_Status(const char *)
//		public void CGameMode::Zc_Property_Homun(const char *)
//		public void CGameMode::Zc_Mer_Init(const char *)
//		public void CGameMode::Zc_Mer_Par_Change(const char *)
//		public void CGameMode::ZC_KILLER_POINT(const char *)
//		public void CGameMode::ZC_KILLER_RANK(const char *)
//		public void CGameMode::Zc_Mail_Req_Get_List(const char *)
//		public void CGameMode::Zc_Mail_Req_Open(const char *)
//		public void CGameMode::Zc_Mail_Req_Get_Item(const char *)
//		public void CGameMode::Zc_Mail_Req_Send(const char *)
//		public void CGameMode::Zc_Mail_Receive(const char *)
//		public void CGameMode::Zc_Ack_Mail_Add_Item(const char *)
//		public void CGameMode::Zc_Ack_Mail_Delete(const char *)
//		public void CGameMode::Zc_Mail_Windows(const char *)
//		public void CGameMode::Zc_Ack_Mail_Return(const char *)
//		public void CGameMode::Zc_Ack_Auction_Add_Item(const char *)
//		public void CGameMode::Zc_Auction_Result(const char *)
//		public void CGameMode::Zc_Auction_Item_Req_Search(const char *)
//		public void CGameMode::Zc_Auction_My_Sell_Stop(const char *)
//		public void CGameMode::Zc_Auction_Windows(const char *)
//		public void CGameMode::Zc_HuntingList(const char *)
//		public void CGameMode::Zc_Pcbang_Effect(const char *)
//		public void CGameMode::Zc_Aid(const char *)
//		public void CGameMode::Zc_Pc_Cash_Point_ItemList(const char *)
//		public void CGameMode::Zc_Pc_Cash_Point_Update(const char *)
//		public void CGameMode::Zc_Boss_Info(const char *)
//		public void CGameMode::Zc_Msg(const char *)
//		public void CGameMode::Zc_Read_Book(const char *)
//		public void CGameMode::Zc_Equipment_Itemlist2(const char *)
//		public void CGameMode::Zc_Store_Equipment_Itemlist2(const char
//*) 		public void CGameMode::Zc_Cart_Equipment_Itemlist2(const char *)
//		public void CGameMode::Zc_Cash_Time_Counter(const char *)
//		public void CGameMode::Zc_Cash_Item_Delete(const char *)
//		public void CGameMode::Zc_Item_Pickup_Ack2(const char *)
//		public void CGameMode::Zc_Equipment_Itemlist3(const char *)
//		public void CGameMode::Zc_Store_Equipment_Itemlist3(const char
//*) 		public void CGameMode::Zc_Cart_Equipment_Itemlist3(const char *)
//		public void CGameMode::Zc_Item_Pickup_Ack3(const char *)
//		public void CGameMode::Zc_Item_Pickup_Party(const char *)
//		public void CGameMode::Zc_EquipItem_Damaged(const char *)
//		public void CGameMode::Zc_ShortCut_Key_List(const char *)
//		public void CGameMode::Zc_Npc_Chat(const char *)
//		public void CGameMode::Zc_Formatstring_Msg(const char *)
//		public void CGameMode::Zc_Party_Config(const char *)
//		public void
// CGameMode::Zc_MemorialDungeon_Subscription_Info(const  char *)
// public void  CGameMode::Zc_MemorialDungeon_Subscription_Notify(const char *)
//		public void CGameMode::Zc_MemorialDungeon_Info(const char *)
//		public void CGameMode::Zc_MemorialDungeon_Notify(const char *)
//		public void CGameMode::Zc_Isvr_Disconnect(const char *)
//		public void CGameMode::Zc_EquipwinMicroscope(const char *)
//		public void CGameMode::Zc_Config(const char *)
//		public void CGameMode::Zc_Config_Notify(const char *)
//		public void CGameMode::Zc_Mapproperty(const char *)
//		public void CGameMode::WriteChat(char *)
//		public void CGameMode::MakeChatFile()
//		public void CGameMode::CloseChatFile()
//		public void CGameMode::SetAutoFollowTime(unsigned long, unsigned
// long)
//		 unsigned char[0x6] m_SiyeonStatus
//		 int m_MouseRollCount
//		 int m_MouseRollMax
//		public void CGameMode::Inner_Zc_Item_Fall_Entry2(const unsigned
// long, const unsigned short, const unsigned char, const short, const short,
// const short, const unsigned char, const unsigned char) 		public
// void CGameMode::Zc_Item_Fall_Entry2(const char *) 		public void
// Zc_Item_Fall_Entry2__m1(const char *) 		public void
// CGameMode::Zc_Item_Fall_Entry2__m2(const char *) 		public void
// Zc_Item_Fall_Entry2__m3(const char *) 		public void
// CGameMode::Zc_Item_Fall_Entry2__m4(const char *) 		public void
// CGameMode::Zc_Item_Fall_Entry2__m5(const char *) 		public void
// Zc_Item_Fall_Entry2__m6(const char *) 		public void
// CGameMode::Inner_Zc_Notify_Moveentry5(const unsigned char, const unsigned
// long, const short, const short, const short, const int, const short, const
// short, const int, const short, const unsigned long, const short, const short,
// const short, const short, const short, const unsigned long, const short,
// const  short, const int, const unsigned char, const unsigned char, const
// unsigned  char *, const unsigned char, const unsigned char, const short)
//		public void Zc_Notify_Moveentry5(const char *)
//		public void Zc_Notify_Moveentry5__m1(const char *)
//		public void Zc_Notify_Moveentry5__m2(const char *)
//		public void Zc_Notify_Moveentry5__m3(const char *)
//		public void CGameMode::Zc_Notify_Moveentry5__m4(const char *)
//		public void Zc_Notify_Moveentry5__m5(const char *)
//		public void CGameMode::Zc_Notify_Moveentry5__m6(const char *)
//		public void CGameMode::Inner_Zc_Notify_Npc_Standentry(const
// unsigned char, const unsigned long, const short, const short, const short,
// const short, const short, const short, const short, const short, const short,
// const short, const short, const short, const short, const short, const
// unsigned long, const short, const short, const short, const unsigned char,
// const unsigned char, const unsigned char *, const unsigned char, const
// unsigned char, const unsigned char, const short) 		public void
// CGameMode::Zc_Notify_Npc_Standentry(const char *) 		public void
// Zc_Notify_Npc_Standentry__m1(const char *) 		public void
// Zc_Notify_Npc_Standentry__m2(const char *) 		public void
// Zc_Notify_Npc_Standentry__m3(const char *) 		public void
// Zc_Notify_Npc_Standentry__m4(const char *) 		public void
// Zc_Notify_Npc_Standentry__m5(const char *) 		public void
// Zc_Notify_Npc_Standentry__m6(const char *) 		public void
// Zc_Reassembly_Certify(const int) 		public class CGameMode &
// operator=(const class CGameMode &) 		public void
// CGameMode::~CGameMode() 		public void
//__local_vftable_ctor_closure() 		public void *
//__vecDelDtor(unsigned int)
//}

#endif  // DOLORI_MODES_GAMEMODE_H_
