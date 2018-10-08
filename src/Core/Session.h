#ifndef DOLORI_CORE_SESSION_H_
#define DOLORI_CORE_SESSION_H_

#include <list>
#include <map>
#include <string>
#include <vector>

class CSession {
 public:
  CSession();

  void Init();
  bool Create();

  void SetSex(int);
  int GetSex();
  bool InitTable();
  void SetTextType(bool, bool);
  void SetCharName(const std::string &char_name);
  void SetServerTime(unsigned int);
  void SetPlayerPosDir(int x, int y, int dir);
  std::list<std::string> GetNumExNameList();
  bool IsGravityAid(uint32_t);
  void InvalidateBasicWnd();
  void InitPcNameTable();
  void InitJobNameTable();
  const char *GetCharName() const;
  const char *GetJobName(unsigned int job) const;
  std::string GetJobActName(int job, int sex) const;
  std::string GetJobSprName(int job, int sex);
  char *GetHeadActName(uint16_t head, int sex, char *buf);
  char *GetHeadSprName(uint16_t head, int sex, char *buf);
  std::string GetImfName(int job, int sex);
  bool IsMasterAid(uint32_t);

 private:
  int m_diffTime;
  char m_curMap[0x14];
  int m_numLatePacket;
  int m_showType;
  unsigned long m_averagePingTime;
  unsigned long m_showDigitTick;
  unsigned long m_killTimeStartTick;
  int m_isShowTime;
  int m_isNeverDie;
  std::string m_char_name;
  char m_aName[0x40];
  // struct TAG_CHARACTER_BLOCK_INFO m_charBlockInfo2[0x9];
  int m_sex;
  int m_charNum;
  int m_authCode;
  unsigned long m_userLevel;
  unsigned long m_lastLoginIP;
  char m_lastLoginTime[0x1c];
  int m_mkcount;
  int m_haircolor;
  int m_deadcount;
  int m_head;
  int m_weapon;
  int m_shield;
  int m_bodyPalette;
  int m_headPalette;
  int m_accessory;
  int m_accessory2;
  int m_accessory3;
  int m_bodyState;
  int m_healthState;
  int m_effectState;
  int m_posX;
  int m_posY;
  int m_dir;
  char m_camp;
  int m_camp_A;
  int m_camp_B;
  char m_charfont;
  short m_DayCount;
  int m_cartCurCount;
  int m_cartMaxCount;
  int m_cartCurWeight;
  int m_cartMaxWeight;
  int m_maxNumOfSellItemOfMerchant;
  int m_attackRange;
  int m_charSlot;
  int m_BgmVolume;
  float m_LoadingTime;
  int m_isShowWhisperWnd;
  int m_isPlayWhisperOpenSound;
  int m_isShowWhisperWnd_Friend;
  int m_isItemSnap;
  int m_isShowGameOver;
  int m_monsterSnapOn_Skill;
  int m_monsterSnapOn_NoSkill;
  int m_isShowTeamGravityPlanetLogo;
  unsigned long m_aid;
  unsigned long m_gid;
  std::list<std::string> m_exNameList;
  std::map<unsigned int, char const *> m_newPcJobNameTable;
  std::map<unsigned int, char const *> m_newPcSexNameTable;
  std::map<unsigned int, char const *> m_newPcHeadNameTable_M;
  std::map<unsigned int, char const *> m_newPcHeadNameTable_F;
  std::map<unsigned int, char const *> m_newPcJobImfNameTable;
  std::map<unsigned int, char const *> m_newAccessoryNameTable;
  std::map<unsigned int, char const *> m_pcWeaponNameTable;
  std::map<unsigned int, char const *> m_pcSexImfNameTable;
  std::map<unsigned int, char const *> m_pcJobNameTable;
  std::map<unsigned int, char const *> m_pcSexNameTable;
  std::map<unsigned int, char const *> m_jobNameTable;
  std::map<unsigned int, char const *> m_sexNameTable;
  std::map<unsigned int, char const *> m_shieldNameTable;
  std::list<unsigned long> m_pingTimeList;
  std::map<unsigned int, char const *> m_palJobNameTable;
  std::vector<std::string> m_shortcutText;
};

// class CSession {
//	public void CSession(const class CSession &)
//		public void CSession::CSession()
//		public void CSession::~CSession()
//		public void CSession::Init()
//		public void CSession::Create()
//		public void CSession::InitTable()
//		public void CSession::InitLanguageTable()
//		public void CSession::InitVariables()
//		public void CSession::InitPcNameTable()
//		public void CSession::InitJobNameTable()
//		public void CSession::InitTalkTypeTable()
//		public void CSession::InitMapTypeInfoTable()
//		 int m_curMapType
//		 int[0xf][0x1e] m_mapInfoTable
//		public int CSession::IsSpace(char)
//		public int CSession::IsEnablePK()
//		public int CSession::IsEnableAllyGuild()
//		public int CSession::IsEnableSiegeMode()
//		public int CSession::IsEnableNeverMemory()
//		public int CSession::IsEnableGomok()
//		public int CSession::IsEnableMemory()
//		public int CSession::IsEnableDropExp()
//		public int CSession::IsEnableTeleport()
//		public int CSession::IsEnableDropItem()
//		public int CSession::IsEnableAllyParty()
//		public int IsEnableUseSimpleEffect()
//		public int IsEnableDisableLockOn()
//		public int IsEnableCountPK()
//		public int IsEnableNoPartyFormation()
//		public int IsEnableBattleField()
//		public int CSession::InitMapNameTable()
//		public int CSession::InitSystemInfoTable()
//		public int CSession::InitEnableObjLightMapTable()
//		public int CSession::InitMp3NameTable()
//		public int CSession::InitIndoorRswTable()
//		public int CSession::InitViewPointTable()
//		public int CSession::InitMapPosTable()
//		public int CSession::InitDivisionMapPosTable()
//		public void CSession::CalculateMapPos(struct MapPosInfo *)
//		public void CSession::RefreshSkillItemWnd()
//		public void CSession::RefreshQuestWnd()
//		public void CSession::RefreshQuestDetailWnd()
//		 class std::list<SKILL_INFO> m_guildSkillList
//
//		 class std::list<SKILL_INFO> m_skillInfoList
//
//		 class std::list<SKILL_INFO> m_homunSkillList
//
//		 class std::list<SKILL_INFO> m_merSkillList
//
//		 class std::list<QUEST_INFO> m_QuestList
//
//		public void ClearQuestList()
//		public unsigned char CSession::AddQuestList(struct QUEST_INFO &,
// unsigned char) 		public void ClearSkillItem()
//		public int GetSkillItemCount()
//		public unsigned char CSession::AddSkillItem(struct SKILL_INFO &,
// unsigned char) 		public struct SKILL_INFO
// CSession::GetSkillItemInfoBySkillId(int) 		public struct SKILL_INFO
// CSession::GetSkillItemInfoBySequence(int) 		public struct SKILL_INFO
// CSession::GetSkillItemInfoByName(const char *) 		public int
// GetHomunSkillItemCount() 		public unsigned char
// CSession::AddHomunSkillItem(struct SKILL_INFO &, unsigned char)
//		public void CSession::RefreshHomunSkillItemWnd()
//		public void ClearHomunSkillItem()
//		public void CSession::SetHomunSkillUseLevel(int, int)
//		public int GetHomunSkillPoint()
//		public int CSession::GetHomunSkillUseLevel(int)
//		public struct SKILL_INFO
// CSession::GetHomunSkillItemInfoBySkillId(int) 		public struct
// SKILL_INFO CSession::GetHomunSkillItemInfoBySequence(int) 		public
// struct SKILL_INFO CSession::GetHomunSkillItemInfoByName(const char *)
//		public int GetMerSkillItemCount()
//		public unsigned char CSession::AddMerSkillItem(struct SKILL_INFO
//&, unsigned char) 		public void CSession::RefreshMerSkillItemWnd()
//		public void ClearMerSkillItem()
//		public void CSession::SetMerSkillUseLevel(int, int)
//		public int GetMerSkillPoint()
//		public int CSession::GetMerSkillUseLevel(int)
//		public struct SKILL_INFO
// CSession::GetMerSkillItemInfoBySkillId(int) 		public struct SKILL_INFO
// CSession::GetMerSkillItemInfoBySequence(int) 		public struct
// SKILL_INFO  CSession::GetMerSkillItemInfoByName(const char *)
// public int  CSession::GetGuildSkillUseLevel(int) 		public int
// GetGuildSkillPoint() 		public void ClearGuildSkillItem()
//		public void CSession::SetGuildSkillUseLevel(int, int)
//		public int GetGuildSkillItemCount()
//		public unsigned char CSession::AddGuildSkillItem(struct
// SKILL_INFO
//&, unsigned char) 		public struct SKILL_INFO
// CSession::GetGuildSkillItemInfoBySequence(int)
//		 class std::list<SKILL_INFO> m_tempSkillList
//
//		public unsigned char CSession::AddTempSkillItem(struct
// SKILL_INFO
//&) 		public struct SKILL_INFO
// CSession::GetTempSkillItemInfoBySkillId(int)
//		 unsigned char m_shortcutSlotCnt
//		 class std::string[0x1b] m_shortenItemName
//		 int[0x1b] m_shortenSkillUseLevel
//		 struct ShortCutKey[0x1b] m_shortCutList
//		public void CSession::ClearShortenSkillUseLevel()
//		public int CSession::GetShortenSkillUseLevel(int)
//		public void CSession::SetShortenSkillUseLevel(int, int)
//		public void CSession::SetShortenSkillName(const char *, int,
// int) 		public void InitLevelUseSkillList() 		public
// void  CSession::InitSkillEffectIdTable() 		public void
// CSession::SetSkillUseLevel(int, int) 		public void
// CSession::GetSkillBitmapFileName(const char *, char *) 		public
// int CSession::GetSkillUseLevel(int) 		public int
// CSession::GetAttackEffectIdBySkillId(int) 		public int
// CSession::GetAttackedEffectIdBySkillId(int) 		public const char *
// CSession::GetItemSpriteFileName_Skill(const char *) 		public class
// std::vector<int, std::allocator<int> > & LevelUseSkillSpAmountList(const char
//*, int &) 		public void CSession::GetSkillActionInfo(int, int &, int
//&)
//		public void CSession::GetSkillActionInfo2(int, int &, int &,
// int,  int) 		public void CSession::LaunchSkillSpecialEffect(int, int,
// class  CGameActor *, class CGameActor *)
//		 class std::vector<int, std::allocator<int> >
// m_skillUseLevelList
//
//		 class std::vector<int, std::allocator<int> >
// m_skillAttackedEffectIdTable
//
//		 class std::vector<int, std::allocator<int> >
// m_skillAttackEffectIdTable
//
//		 class std::vector<int, std::allocator<int> >
// m_guildSkillUseLevelList
//
//		 class std::vector<int, std::allocator<int> >
// m_homunSkillUseLevelList
//
//		 class std::vector<int, std::allocator<int> >
// m_merSkillUseLevelList
//
//		public int CSession::IsAbracatabra(int)
//		public void CSession::InitWithClear()
//		public void CSession::InitJobHitWaveName()
//		public int CSession::InitFogParameterTable()
//		public void CSession::InitWeaponHitWaveName()
//		public void CSession::InitShadowFactorWithJob()
//		public void CSession::InitWeaponSwingWaveName()
//		public void CSession::WriteOptionToRegistry()
//		public void CSession::WriteExListToRegistry()
//		public void CSession::InitExListWithRegistry()
//		public void CSession::InitOptionWithRegistry()
//		public void CSession::InitWhenServerMove()
//		public int CSession::GetHeadJob(int, int)
//		public void CSession::CorrectHead(int &, int)
//		public unsigned long CSession::GetServerTime()
//		public unsigned long CSession::GetCurSystemTime()
//		public void CSession::SetServerTime(unsigned long)
//		public unsigned char CSession::IsOnlyEnglish(const char *)
//		public void CSession::UpdateServerTime(unsigned long)
//		public void RecalcAverageDiffTime(int)
//		public void CSession::RecalcAveragePingTime(unsigned long)
//		public void CSession::SetPlayerPosDir(int, int, int)
//		public unsigned char CSession::IsBadNameWithSpaceChar(const char
//*) 		public void CSession::SetPlayerInfo(int, int, char *, int)
//		public int CSession::GetTalkType(const char *, enum TALKTYPE *,
// class std::string *) 		public void CSession::ClearPlusValue()
//		public void CSession::ClearShortenItemName()
//		public int GetDistByNumCell(int)
//		public const char * CSession::RemoveUnderbar(const char *, char
//*) 		public int CSession::NumExName() 		public void
// CSession::DeleteAllExNameList() 		public int
// CSession::IsExName(const char *) 		public void
// CSession::AddToExNameList(const char *) 		public void
// CSession::DeleteFromExNameList(const char *) 		public int
// CSession::NumExAid() 		public int CSession::IsExAid(unsigned
// long) 		public void CSession::DeleteAllExAidList()
//		public void CSession::AddToExAidList(unsigned long)
//		public void CSession::DeleteFromExAidList(unsigned long)
//		public class std::list<std::string, std::allocator<std::string >
//> & CSession::GetNumExNameList() 		public const char *
// CSession::GetAttrWaveName(int) 		public const char *
// CSession::GetJobHitWaveName(int) 		public const char *
// CSession::GetMp3Name(const char *) 		public const char *
// CSession::GetMapName(const char *) 		public const char *
// CSession::GetWeaponHitWaveName(int) 		public const char *
// CSession::GetWeaponSwingWaveName(int) 		public const char *
// CSession::GatName2RswName(const char *) 		public const char *
// CSession::GetItemSpriteFileName(const char *, int)
//		public unsigned char CSession::IsIndoorRswName(const char *)
//		public unsigned char CSession::IsEnableObjLightMap(const char *)
//		public class std::vector<std::string, std::allocator<std::string
//> > & CSession::GetFogParameter(const char *, int &) 		public class
// std::vector<std::string, std::allocator<std::string > > &
// CSession::GetViewPointParameter(const char *, int &) 		public
// void  CSession::GetItemBitmapFileName(const char *, char *, int)
//		public int CSession::GetNumItem()
//		public unsigned char CSession::IsVisibleNPC(enum JOBTYPE)
//		public struct ITEM_INFO CSession::GetItemInfoById(int)
//		public struct ITEM_INFO CSession::GetItemInfoByIndex(int)
//		public struct ITEM_INFO CSession::GetItemInfoBySequence(int)
//		public char * CSession::GetJobActName(int, int, char *)
//		public char * CSession::GetJobSprName(int, int, char *)
//		public char * CSession::GetJobDyeActName(int, int, char *)
//		public char * CSession::GetJobDyeSprName(int, int, char *)
//		public char * CSession::GetImfName(int, int, int, char *)
//		public char * CSession::GetHeadActName(int, int &, int, char *)
//		public char * CSession::GetHeadSprName(int, int &, int, char *)
//		public char * CSession::GetShieldActName(int, int, int, char *)
//		public char * CSession::GetShieldSprName(int, int, int, char *)
//		public char * CSession::GetAccessoryActName(int, int &, int,
// int,  char *) 		public char * CSession::GetAccessorySprName(int,
// int
// &,
// int, int, char *) 		public const char * CSession::GetItemName(int)
//		public void CSession::SetItem(struct ITEM_INFO *)
//		public unsigned char CSession::AddItem(struct ITEM_INFO *)
//		public void CSession::DecItem(unsigned long, int)
//		public unsigned char CSession::AddEquipItem(struct ITEM_INFO *)
//		public unsigned char CSession::AddItemNoRefresh(struct ITEM_INFO
//*) 		public unsigned char CSession::IsValidItemIndexInEquiped(int)
//		public unsigned char AddItemWithNoRefresh(struct ITEM_INFO *)
//		public unsigned char CSession::IsValidItemIndexInUnequiped(int)
//		public unsigned char
// CSession::MoveItemFromEquipWndToItemWnd(int) 		public void
// CSession::BitMaskToSlotNum(int, int *) 		public unsigned char
// CSession::MoveItemFromItemWndToEquipWnd(struct ITEM_INFO *)
//		public void CSession::ClearItem()
//		public void CSession::ClearShopItem()
//		public void CSession::ClearDealItems()
//		public void CSession::ClearEquipItem()
//		public void CSession::ClearMerchantDealItems()
//		public void CSession::ClearEquipItemInInventory()
//		public void CSession::ClearAntiEquipItemInInventory()
//		public void CSession::ClearMerchantShopItem()
//		public void CSession::ClearMerchantMyShopItem()
//		public int CSession::GetNumShopItem()
//		public int CSession::GetShopItemNum(int)
//		public void CSession::DecShopItem(struct ITEM_INFO &)
//		public unsigned char CSession::IsExistInShopItemList(int)
//		public struct ITEM_INFO CSession::GetShopItemInfoBySequence(int)
//		public void CSession::AddShopItemFromSell(struct ITEM_INFO &)
//		public void CSession::AddShopItem(struct SHOP_ITEM &, int)
//		public int CSession::GetNumMerchantShopItem()
//		public int CSession::GetMerchantShopItemNum(int)
//		public void CSession::AddMerchantShopItem(struct ITEM_INFO &)
//		public void CSession::DecMerchantShopItem(struct ITEM_INFO &)
//		public struct ITEM_INFO
// CSession::GetMerchantShopItemInfoBySequence(int) 		public int
// CSession::GetNumMerchantMyShopItem() 		public int
// CSession::GetMerchantMyShopItemNum(int) 		public void
// CSession::AddMerchantMyShopItem(struct ITEM_INFO &) 		public void
// CSession::DecMerchantMyShopItem(struct ITEM_INFO &)
//		public unsigned char
// CSession::IsExistInMerchantMyShopItemList(int) 		public struct
// ITEM_INFO CSession::GetMerchantMyShopItemInfoBySequence(int)
//		public void CSession::ClearPurchaseItem()
//		public int CSession::GetNumPurchaseItem()
//		public int CSession::GetPurchaseItemTotalPrice()
//		public void CSession::AddPurchaseItem(struct ITEM_INFO &)
//		public void CSession::DecPurchaseItem(struct ITEM_INFO &)
//		public int CSession::GetPurchaseItemNum(const char *)
//		public struct ITEM_INFO
// CSession::GetPurchaseItemInfoBySequence(int) 		public struct
// ITEM_INFO  CSession::GetPurchaseItemInfoByName(const char *)
// public void  CSession::ClearMerchantPurchaseItem() 		public int
// CSession::GetNumMerchantPurchaseItem() 		public int
// CSession::GetMerchantPurchaseItemTotalPrice() 		public struct
// ITEM_INFO CSession::GetMerchantPurchaseItemSaved(int) 		public
// int CSession::GetMerchantPurchaseItemNumByIndex(int) 		public
// void  CSession::AddMerchantPurchaseItem(struct ITEM_INFO &) 		public
// void CSession::DecMerchantPurchaseItem(struct ITEM_INFO &)
//		public int CSession::GetMerchantPurchaseItemNum(const char *)
//		public struct ITEM_INFO
// CSession::GetMerchantPurchaseItemInfoBySequence(int) 		public
// void  CSession::CloneMerchantPurchaseItemToMerchantPurchaseItemSaved()
//		public struct ITEM_INFO
// CSession::GetMerchantPurchaseItemInfoByName(const char *)
//		public void CSession::ClearSellItem()
//		public int CSession::GetNumSellItem()
//		public int CSession::IsSellItemValid()
//		public int CSession::GetSellItemNum(int)
//		public void CSession::AddSellItem(struct ITEM_INFO &)
//		public void CSession::DecSellItem(struct ITEM_INFO &)
//		public struct ITEM_INFO CSession::GetSellItemInfoBySequence(int)
//		public struct ITEM_INFO CSession::GetSellItemInfoByIndex(int)
//		public void CSession::ClearStoreItem()
//		public int CSession::GetNumStoreItem()
//		public void CSession::RefreshStoreItemWnd()
//		public int CSession::GetStoreItemNum(int)
//		public unsigned char CSession::AddStoreItem(struct ITEM_INFO &)
//		public unsigned char CSession::DecStoreItem(struct ITEM_INFO &)
//		public struct ITEM_INFO CSession::GetStoreItemInfoByIndex(int)
//		public struct ITEM_INFO
// CSession::GetStoreItemInfoBySequence(int) 		public unsigned char
// CSession::AddMerchantItem(struct ITEM_INFO &) 		public unsigned
// char CSession::DecMerchantItem(struct ITEM_INFO &) 		public void
// CSession::ClearMerchantItem() 		public int
// CSession::GetNumMerchantItem() 		public void
// CSession::RefreshMerchantItemWnd() 		public int
// CSession::GetMerchantItemNum(int) 		public struct ITEM_INFO
// CSession::GetMerchantItemInfoByIndex(int) 		public struct ITEM_INFO
// CSession::GetMerchantItemInfoBySequence(int) 		public void
// CSession::ClearMerchantMirrorItem() 		public int
// CSession::GetNumMerchantMirrorItem() 		public void
// CSession::RefreshMerchantMirrorItemWnd() 		public int
// CSession::GetMerchantMirrorItemNum(int) 		public void
// CSession::CloneMerchantItemToMerchantMirrorItem()
//		public unsigned char CSession::AddMerchantMirrorItem(struct
// ITEM_INFO &)
//		public unsigned char CSession::DecMerchantMirrorItem(struct
// ITEM_INFO &) 		public struct ITEM_INFO
// CSession::GetMerchantMirrorItemInfoByIndex(int) 		public struct
// ITEM_INFO CSession::GetMerchantMirrorItemInfoBySequence(int)
//		public void CSession::RefreshMerchantShopMakeWnd()
//		public void CSession::ClearMerchantHopeToSellItem()
//		public int CSession::GetNumMerchantHopeToSellItem()
//		public int CSession::GetMerchantHopeToSellItemNum(int)
//		public unsigned char CSession::AddMerchantHopeToSellItem(struct
// ITEM_INFO &)
//		public unsigned char CSession::DecMerchantHopeToSellItem(struct
// ITEM_INFO &) 		public struct ITEM_INFO
// CSession::GetMerchantHopeToSellItemInfoByIndex(int) 		public struct
// ITEM_INFO CSession::GetMerchantHopeToSellItemInfoBySequence(int)
//		public void CSession::SetMerchantHopeToSellItemPrice(int, int)
//		public unsigned char CSession::DeleteCommaInPrice(char *)
//		public void CSession::ClearExchangeItemList()
//		public int CSession::IsExchangeItemListFull()
//		public int CSession::GetFilledExchangeItemList()
//		public void CSession::AddToExchangeList(struct ITEM_INFO)
//		public void CSession::SetToExchangeList(struct ITEM_INFO)
//		public unsigned char CSession::IsExistIndexInMyChangeList(int)
//		public unsigned char CSession::MoveItemToExchangeList(struct
// ITEM_INFO) 		public void CSession::CancelExchange()
//		public int CSession::GetNumOtherExchangeItems()
//		public int GetMyExchangeMoney()
//		public int GetOtherExchangeMoney()
//		public void CSession::ClearOtherExchangeItemList()
//		public int CSession::IsOtherExchangeItemListFull()
//		public void CSession::SetMyExchangeMoney(int)
//		public void CSession::SetOtherExchangeMoney(int)
//		public void CSession::AddToOtherExchangeList(struct ITEM_INFO)
//		public void CSession::SetToOtherExchangeList(struct ITEM_INFO)
//		public void CSession::CancelExchangeNoRefresh()
//		public struct ITEM_INFO CSession::GetExchangeItemInfo(int)
//		public struct ITEM_INFO CSession::GetOtherExchangeItemInfo(int)
//		public void CSession::ClearFriend()
//		public int CSession::GetNumFriend()
//		public struct FRIEND_INFO CSession::GetFriendInfoBySequence(int)
//		public void CSession::AddFriendToList(struct FRIEND_INFO &)
//		public int CSession::SetFriendState(unsigned long, unsigned
// long,  unsigned char) 		public int
// CSession::DeleteFriendFromList(unsigned long) 		public void
// CSession::RefreshFriendUI()
//		public int CSession::IsFriendName(const char *)
//		public int CSession::IsCheatName(const char *)
//		public void CSession::HiFriends(int)
//		public int CSession::IsGuildMember(const char *)
//		public int CSession::IsCheatGuildName(const char *)
//		public int CSession::CompareTwoNames(const char *, const char *)
//		public void CSession::ClearParty()
//		public int CSession::GetNumParty()
//		public void CSession::RefreshPartyUI()
//		public struct FRIEND_INFO CSession::GetPartyInfoByAid(unsigned
// long) 		public void CSession::AddMemberToParty(struct
// FRIEND_INFO &) 		public void
// CSession::ChangeRoleFromParty(unsigned long, int) 		public void
// CSession::DeleteMemberFromParty(const char *) 		public struct
// FRIEND_INFO CSession::GetPartyInfoBySequence(int) 		public struct
// FRIEND_INFO CSession::GetPartyInfoByName(const char *) 		public
// unsigned long CSession::GetMemberAidFromParty(const char *)
//		public int CSession::GetWeaponType(int)
//		public int CSession::MakeWeaponType(int, int)
//		public const char * CSession::GetShortenItemName(int)
//		public void CSession::SetShortenItemName(const char *, int)
//		public void CSession::ClearShortCutItemList()
//		public void CSession::SetShortCutItemInfo(char, int, int, int)
//		public void CSession::ClearOtherUserEquipItem()
//		public unsigned char CSession::AddOtherUserEquipItem(struct
// ITEM_INFO *) 		public struct ITEM_INFO
// CSession::GetOtherUserEquipedItems(int) 		public int
// CSession::GetSex() 		public void CSession::SetSex(int)
//		public void SetAid(unsigned long)
//		public void SetGid(unsigned long)
//		public unsigned long CSession::GetAid()
//		public unsigned long CSession::GetGid()
//		public void HP_AddItem(int)
//		public int CSession::GetJob()
//		public int CSession::IsThisPC(int)
//		public int GetExp()
//		public int GetStr()
//		public int GetAgi()
//		public int GetVit()
//		public int GetInt()
//		public int GetDex()
//		public int GetLuk()
//		public int GetJobexp()
//		public int GetWeight()
//		public int GetVirtue()
//		public int GetGold()
//		public int GetHonor()
//		public int GetLevel()
//		public int GetPoint()
//		public int GetSpeed()
//		public int GetNextExp()
//		public int GetPlusStr()
//		public int GetPlusAgi()
//		public int GetPlusVit()
//		public int GetPlusInt()
//		public int GetPlusDex()
//		public int GetPlusLuk()
//		public int GetJoblevel()
//		public int GetMaxWeight()
//		public int GetJobNextexp()
//		public int GetSkillPoint()
//		public int GetASPD()
//		public int GetPlusASPD()
//		public int GetAttPower()
//		public int GetMdefPower()
//		public int GetItemDefPower()
//		public int GetPlusdefPower()
//		public int CSession::GetEquipArrowIndex()
//		public int GetHitSuccessValue()
//		public int GetRefiningPower()
//		public int GetMax_mattPower()
//		public int GetMin_mattPower()
//		public int GetPlusmdefPower()
//		public int GetAvoidSuccessValue()
//		public int GetCriticalSuccessValue()
//		public int GetPlusAvoidSuccessValue()
//		public const char * CSession::GetCharName()
//		public int CSession::GetEffectIgnoreCnt(int)
//		public void CSession::SetCharName(const char *)
//		public void CSession::SetTextType(unsigned char, unsigned char)
//		public char * CSession::GetStateFileName(int, int)
//		public int CSession::Encode(int, int)
//		public int CSession::Decode(int, int)
//		public void CSession::ChangeXorValue()
//		public void SetHp(int)
//		public void SetMaxhp(int)
//		public void SetSp(int)
//		public void SetMaxsp(int)
//		public int GetMaxhp()
//		public int GetMaxsp()
//		public int GetHp()
//		public int CSession::GetSp()
//		public void CSession::SetStatusData(class CGameActor *)
//		public void GainSkill(int, unsigned char)
//		public unsigned char HaveThisSkill(int)
//		public int GetHomunHP()
//		public int GetHomunSP()
//		public int GetHomunMaxHP()
//		public int GetHomunMaxSP()
//		public const int * GetHomunExpPointer()
//		public const int * GetHomunNextExpPointer()
//		public void SetHomunHP(int)
//		public void SetHomunSP(int)
//		public void SetHomunMaxHP(int)
//		public void SetHomunMaxSP(int)
//		public void SetHomunExp(int)
//		public void SetHomunNextExp(int)
//		public void SetHomunHungry(int)
//		public void SetHomunSkillPoint(int)
//		public void CSession::InvalidateHomunInfoWnd()
//		public void CSession::InitHomunTargetInfo()
//		public int GetMerHP()
//		public int GetMerSP()
//		public int GetMerMaxHP()
//		public int GetMerMaxSP()
//		public void SetMerHP(int)
//		public void SetMerSP(int)
//		public void SetMerMaxHP(int)
//		public void SetMerMaxSP(int)
//		public void CSession::InvalidateMerInfoWnd()
//		public void CSession::InitMerTargetInfo()
//		public const int * GetExpPointer()
//		public const int * GetJobexpPointer()
//		public const int * GetNextExpPointer()
//		public const int * GetJobnextexpPointer()
//		public const int * GetStandardStrPointer()
//		public const int * GetStandardAgiPointer()
//		public const int * GetStandardVitPointer()
//		public const int * GetStandardIntPointer()
//		public const int * GetStandardDexPointer()
//		public const int * GetStandardLukPointer()
//		public void CSession::InvalidateBasicWnd()
//		public void CSession::InvalidateUI()
//		public void CSession::InvalidateJob()
//		public void SetGoldNoRefresh(int)
//		public void SetGold(int)
//		public void SetJobexp(int)
//		public void SetSpeed(int)
//		public void SetHonor(int)
//		public void SetWeight(int)
//		public void SetVirtue(int)
//		public void SetJobnextexp(int)
//		public void SetMaxWeight(int)
//		public void SetStr(int)
//		public void SetAgi(int)
//		public void SetVit(int)
//		public void SetInt(int)
//		public void SetDex(int)
//		public void SetLuk(int)
//		public void SetExp(int)
//		public void SetLevel(int)
//		public void SetPoint(int)
//		public void SetPlusStr(int)
//		public void SetPlusAgi(int)
//		public void SetPlusVit(int)
//		public void SetPlusInt(int)
//		public void SetPlusDex(int)
//		public void SetPlusLuk(int)
//		public void SetSkillPoint(int)
//		public void SetNextexp(int)
//		public void SetStandardStr(int)
//		public void SetStandardAgi(int)
//		public void SetStandardVit(int)
//		public void SetStandardInt(int)
//		public void SetStandardDex(int)
//		public void SetStandardLuk(int)
//		public void SetJob(int)
//		public void SetJoblevel(int)
//		public void SetGuildSkillPoint(int)
//		public void SetAttPower(int)
//		public void SetMdefPower(int)
//		public void SetItemDefPower(int)
//		public void SetPlusdefPower(int)
//		public void SetRefiningPower(int)
//		public void SetMax_mattPower(int)
//		public void SetMin_mattPower(int)
//		public void SetASPD(int)
//		public void SetPlusASPD(int)
//		public void SetPlusmdefPower(int)
//		public void SetHitSuccessValue(int)
//		public void SetAvoidSuccessValue(int)
//		public void SetCriticalSuccessValue(int)
//		public void SetPlusAvoidSuccessValue(int)
//		public unsigned long CSession::GetPartyColorBySeq(int)
//		public void CSession::SetEquipArrowIndwx(int)
//		public struct ITEM_INFO CSession::GetEquipedItems(int)
//		public enum TALKTYPE CSession::GetNoParamTalkType(const char *)
//		public unsigned char CSession::IsSecondAttack(int, int, int)
//		public float CSession::GetPCAttackMotion(int, int, int, int)
//		public float CSession::GetShadowFactorWithJob(int)
//		public unsigned char CSession::IsProperWeapon(int, int)
//		public int IsItemSnap()
//		public int IsMonsterSnap()
//		public void CSession::RefreshMouseSnapState(int)
//		public const char * CSession::GetRmaName(int)
//		public const char * CSession::GetW3DName(int)
//		public unsigned char CSession::IsHaveAnotherPalette(int, char *)
//		public const char * CSession::GetBodyPaletteName(int, int, int,
// char *)
//		public const char * CSession::GetHeadPaletteName(int, int, int,
// int, char *) 		public const char * CSession::GetJobName(int)
//		public void CSession::ReLoadAlwaysNeededRes()
//		public void CSession::PreLoadAlwaysNeededRes()
//		public int CSession::GetShieldType(int)
//		public int CSession::IsProperShield(int, int)
//		 unsigned long m_targetGID
//		 class std::vector<CHAT_PROHIBIT_LOG,
// std::allocator<CHAT_PROHIBIT_LOG> > m_chatProhibitLog
//
//		 class std::vector<REQ_ACCOUNT_AID,
// std::allocator<REQ_ACCOUNT_AID> > m_recievedAccountName
//
//		 class std::vector<REQ_ACCOUNTNAME_INFO,
// std::allocator<REQ_ACCOUNTNAME_INFO> > m_reqAccountInfo
//
//		public void CSession::RerecordProhibitLog()
//		public void CSession::PrintNumber(class CFile *, unsigned long)
//		public void CSession::InitChattingProhibitLog()
//		public void CSession::DeleteAssignAID(unsigned long)
//		public void CSession::EraseProhibit(unsigned long, unsigned
// long) 		public void CSession::AppendProhibit(unsigned long,
// unsigned long) 		public int CSession::GetChatProhibittedCnt(char
//*) 		public int CSession::GetChatProhibittedCnt(unsigned long)
//		 class std::string m_selectedServerName
//
//		public void SetSelectedServerName(const char *)
//		public const char * GetSelectedServerName()
//		public const char * CSession::GetItemResName_WithId(const char
//*,  int) 		public unsigned long CSession::GetItemDisColor(struct
// ITEM_INFO
//*) 		public unsigned char CSession::GetEmblemState()
//		public void CSession::GetEmblemFileName(char *, int, int)
//		public void SetEmblemState(unsigned char)
//		public void CSession::SetCompressedEmblemImage(const char *,
// unsigned long, int, int) 		public void
// CSession::InitShortCutTextFromReg() 		public int
// CSession::IsExistEffectState(int) 		public int CSession::IsKorean()
//		public int CSession::IsPc(int)
//		public int CSession::IsSiegeMode()
//		public int CSession::IsBattleFieldMode()
//		public int CSession::IsAttack(int)
//		public int CSession::IsMyParty(int)
//		public int CSession::IsMonster(class CGameActor *)
//		public int CSession::IsMyGuild(int)
//		public int CSession::IsGuardian(int)
//		public int CSession::IsPetEgg(int)
//		public int CSession::IsMasterAid(int)
//		public int CSession::IsMerOrHomun(int)
//		public int CSession::IsMer(int)
//		public int CSession::IsHomun(int)
//		public void CSession::InitPetTables()
//		public void CSession::InitPetTalkTable()
//		public void CSession::GetPetSpeak(int, int, int, char *)
//		public void CSession::GetPetHungryStateText(int, char *)
//		public void CSession::GetPetFriendlyStateText(int, char *)
//		public void CSession::GetPetIllustName(int, int, char *)
//		public void CSession::GetPetTalkString(char *, char *, int, int)
//		public void CSession::GetMonsterSkillInfo(char *, int, int &,
// int
//&) 		public void CSession::GetMonsterTalkInfo(int, int, int, char *,
// unsigned long) 		public char * CSession::GetPetName(int)
//		public char * CSession::GetPetActText(int)
//		public char * CSession::GetPetAccActName(int)
//		public char * CSession::GetPetHungryText(int)
//		public int CSession::GetPetHungryState(int)
//		public int CSession::GetPetFriendlyState(int)
//		public int CSession::GetPetTalkNumber(int, int, int)
//		public int GetPetEmotion(int, int, int)
//		public class CGameActor * CSession::GetGameActorByAid(unsigned
// long) 		public void CSession::SetDamageSituation(int, int, int,
// unsigned char) 		public char * CSession::GetStateName(int)
//		 class std::vector<FORCE_ANIM_TICK,
// std::allocator<FORCE_ANIM_TICK> > m_forceAnimEndTick
//
//		public unsigned long CSession::GetForceAnimEndTick(unsigned
// long) 		public void CSession::SetForceAnimEndTick(unsigned long,
// unsigned long) 		public int CSession::IsEFST_Berserk()
//		public int CSession::IsEFST_TrickDead()
//		 int m_diffTime
//		 char[0x14] m_curMap
//		 int m_numLatePacket
//		 int m_showType
//		 unsigned long m_averagePingTime
//		 unsigned long m_showDigitTick
//		 unsigned long m_killTimeStartTick
//		 int m_isShowTime
//		 int m_isNeverDie
//		 char[0x40] m_cName
//		 char[0x40] m_aName
//		 struct TAG_CHARACTER_BLOCK_INFO[0x9]
// m_charBlockInfo2
//		 int m_sex
//		 int m_charNum
//		 int m_authCode
//		 unsigned long m_userLevel
//		 unsigned long m_lastLoginIP
//		 char[0x1c] m_lastLoginTime
//		 int m_mkcount
//		 int m_haircolor
//		 int m_deadcount
//		 int m_head
//		 int m_weapon
//		 int m_shield
//		 int m_bodyPalette
//		 int m_headPalette
//		 int m_accessory
//		 int m_accessory2
//		 int m_accessory3
//		 int m_bodyState
//		 int m_healthState
//		 int m_effectState
//		 int m_posX
//		 int m_posY
//		 int m_dir
//		 char m_camp
//		 int m_camp_A
//		 int m_camp_B
//		 char m_charfont
//		 short m_DayCount
//		 int m_cartCurCount
//		 int m_cartMaxCount
//		 int m_cartCurWeight
//		 int m_cartMaxWeight
//		 int m_maxNumOfSellItemOfMerchant
//		 int m_attackRange
//		 int m_charSlot
//		 int m_BgmVolume
//		 float m_LoadingTime
//		 int m_isShowWhisperWnd
//		 int m_isPlayWhisperOpenSound
//		 int m_isShowWhisperWnd_Friend
//		 int m_isItemSnap
//		 int m_isShowGameOver
//		 int m_monsterSnapOn_Skill
//		 int m_monsterSnapOn_NoSkill
//		 int m_isShowTeamGravityPlanetLogo
//		 class std::vector<char const *,
// std::allocator<char const *> > m_newPcJobNameTable
//
//		 class std::vector<char const *,
// std::allocator<char const *> > m_newPcSexNameTable
//
//		 class std::vector<char const *,
// std::allocator<char const *> > m_newPcHeadNameTable_M
//
//		 class std::vector<char const *,
// std::allocator<char const *> > m_newPcHeadNameTable_F
//
//		 class std::vector<char const *,
// std::allocator<char const *> > m_newPcJobImfNameTable
//
//		 class std::vector<char const *,
// std::allocator<char const *> > m_newAccessoryNameTable
//
//		 class std::vector<char const *,
// std::allocator<char const *> > m_pcWeaponNameTable
//
//		 class std::vector<char const *,
// std::allocator<char const *> > m_pcSexImfNameTable
//
//		 class std::vector<char const *,
// std::allocator<char const *> > m_pcJobNameTable
//
//		 class std::vector<char const *,
// std::allocator<char const *> > m_pcSexNameTable
//
//		 class std::vector<char const *,
// std::allocator<char const *> > m_jobNameTable
//
//		 class std::vector<char const *,
// std::allocator<char const *> > m_sexNameTable
//
//		 class std::vector<char const *,
// std::allocator<char const *> > m_shieldNameTable
//
//		 class std::list<unsigned long,
// std::allocator<unsigned long> > m_pingTimeList
//
//		 class std::vector<char const *,
// std::allocator<char const *> > m_palJobNameTable
//
//		 class std::vector<std::string,
// std::allocator<std::string > > m_shortcutText
//
//		 unsigned long m_petGID
//		 int m_isPetNameModified
//		 char[0x20] m_petName
//		 int m_petAcc
//		 int m_petJob
//		 int m_petLevel
//		 int m_petHungry
//		 int m_petFriendly
//		 int m_petEggIndex
//		 int m_petOldHungry
//		 int[0x7][0x5][0x5] m_petEmotionTable
//		 class std::string[0x5][0x5] m_petTalkTable
//		 class XMLDocument m_petTalkXmlTable
//
//		 class XMLDocument m_monsterSkillInfo
//
//		 class XMLDocument m_monsterTalkTable
//
//		 int m_guildDealZeny
//		 int m_MaxItemIndex
//		 unsigned long m_aid
//		 unsigned long m_gid
//		 int m_isWeaponBow
//		 float m_oneCellDist
//		 int m_job
//		 int m_exp
//		 int m_level
//		 int m_point
//		 int m_nextexp
//		 int m_joblevel
//		 int m_skillPoint
//		 int m_guildSkillPoint
//		 int m_homunSkillPoint
//		 int m_merSkillPoint
//		 int m_plusStr
//		 int m_plusAgi
//		 int m_plusVit
//		 int m_plusInt
//		 int m_plusDex
//		 int m_plusLuk
//		 int m_str
//		 int m_agi
//		 int m_vit
//		 int m_int
//		 int m_dex
//		 int m_luk
//		 int m_standardStr
//		 int m_standardAgi
//		 int m_standardVit
//		 int m_standardInt
//		 int m_standardDex
//		 int m_standardLuk
//		 int m_ASPD
//		 int m_attPower
//		 int m_mdefPower
//		 int m_plusASPD
//		 int m_itemDefPower
//		 int m_plusdefPower
//		 int m_refiningPower
//		 int m_max_mattPower
//		 int m_min_mattPower
//		 int m_plusmdefPower
//		 int m_hitSuccessValue
//		 int m_avoidSuccessValue
//		 int m_criticalSuccessValue
//		 int m_plusAvoidSuccessValue
//		 int m_equipArrowIndex
//		 int m_gold
//		 int m_speed
//		 int m_honor
//		 int m_maxWeight
//		 int m_jobnextexp
//		 int m_jobexp
//		 int m_weight
//		 int m_virtue
//		 int m_isMonsterSnap
//		 int m_systemDiffTime
//		 class std::list<ITEM_INFO,
// std::allocator<ITEM_INFO> > m_itemList
//
//		 class std::list<ITEM_INFO,
// std::allocator<ITEM_INFO> > m_shopItemList
//
//		 class std::list<ITEM_INFO,
// std::allocator<ITEM_INFO> > m_purchaseItemList
//
//		 class std::list<ITEM_INFO,
// std::allocator<ITEM_INFO> > m_sellItemList
//
//		 class std::list<ITEM_INFO,
// std::allocator<ITEM_INFO> > m_storeItemList
//
//		 class std::list<ITEM_INFO,
// std::allocator<ITEM_INFO> > m_merchantItemList
//
//		 class std::list<ITEM_INFO,
// std::allocator<ITEM_INFO> > m_merchantShopItemList
//
//		 class std::list<ITEM_INFO,
// std::allocator<ITEM_INFO> > m_merchantMirrorItemList
//
//		 class std::list<ITEM_INFO,
// std::allocator<ITEM_INFO> > m_merchantMyShopItemList
//
//		 class std::list<ITEM_INFO,
// std::allocator<ITEM_INFO> > m_merchantPurchaseItemList
//
//		 class std::list<ITEM_INFO,
// std::allocator<ITEM_INFO> > m_merchantHopeToSellItemList
//
//		 class std::list<ITEM_INFO,
// std::allocator<ITEM_INFO> > m_merchantPurchaseItemSavedList
//
//		 class std::list<FRIEND_INFO,
// std::allocator<FRIEND_INFO> > m_partyList
//
//		 class std::list<FRIEND_INFO,
// std::allocator<FRIEND_INFO> > m_friendList
//
//		 struct ITEM_INFO[0xa] m_equipedItems
//		 struct ITEM_INFO[0xa] m_otherUserEquipedItems
//		 struct ITEM_INFO[0xa] m_exchangeItems
//		 struct ITEM_INFO[0xa] m_otherExchangeItems
//		 int m_myExchangeMoney
//		 int m_otherExchangeMoney
//		 class std::vector<std::pair<char const *, enum
// TALKTYPE>, std::allocator<std::pair<char const *, enum TALKTYPE> > >
// m_talkTypeTable
//
//		 class std::vector<std::pair<char const *, char
// const *>, std::allocator<std::pair<char const *, char const *> > >
// m_mapNameTable
//
//		 class std::vector<std::pair<char const *, char
// const *>, std::allocator<std::pair<char const *, char const *> > >
// m_mp3NameTable
//
//		 class std::vector<std::pair<std::string,
// std::vector<std::string, std::allocator<std::basic_string<char,
// std::char_traits<char>, std::allocator087911da m_fogParameterTable
//
//		 class std::vector<std::pair<std::string,
// std::vector<std::string, std::allocator<std::basic_string<char,
// std::char_traits<char>, std::allocator087911da m_ViewPointTable
//
//		 class std::vector<char const *,
// std::allocator<char const *> > m_indoorRswTable
//
//		 class std::vector<float, std::allocator<float>
//>  m_shadowFactorTable
//
//		 class std::vector<std::string,
// std::allocator<std::string > > m_msgStringTable
//
//		 class std::vector<std::string,
// std::allocator<std::string > > m_weaponSwingWaveNameTable
//
//		 class std::vector<std::string,
// std::allocator<std::string > > m_jobHitWaveNameTable
//
//		 class std::vector<std::string,
// std::allocator<std::string > > m_weaponHitWaveNameTable
//
//		 class std::list<unsigned long,
// std::allocator<unsigned long> > m_exAidList
//
//		 class std::list<std::string,
// std::allocator<std::string > > m_exNameList
//
//		 class std::vector<std::pair<char const *,
// bool>,  std::allocator<std::pair<char const *, bool> > >
// m_enableObjLightMapList
//
//		 class std::vector<std::pair<char const *, enum
// TALKTYPE>, std::allocator<std::pair<char const *, enum TALKTYPE> > >
// m_cmdOnOffTable
//
//		 class std::vector<std::pair<char const *, enum
// TALKTYPE>, std::allocator<std::pair<char const *, enum TALKTYPE> > >
// m_cmdExeTable
//
//		 class std::vector<std::pair<int, enum
// TALKTYPE>,  std::allocator<std::pair<int, enum TALKTYPE> > > m_cmdOnOffSet
//
//		 class std::vector<std::pair<char const *,
// unsigned long>, std::allocator<std::pair<char const *, unsigned long> > >
// m_cmdWinTable
//
//		 class std::vector<char const *,
// std::allocator<char const *> > m_keyWinTable
//
//		 class std::vector<MAIL_LIST,
// std::allocator<MAIL_LIST> > m_mailList
//
//		 struct MAIL_OPEN m_mailOpen
//
//		 struct MAIL_LIST m_mailNew
//
//		 struct ITEM_INFO m_mailItem
//
//		 int m_mailItemCnt
//		 unsigned char m_waitForSendMail
//		 class std::vector<AUCTION_ITEM_SEARCH_INFO,
// std::allocator<AUCTION_ITEM_SEARCH_INFO> > m_auctionList
//
//		 unsigned char m_waitForAddAuction
//		 int m_auctionSeachOption
//		 int m_auctionSeachOption2
//		 class std::map<std::string, MapPosInfo,
// std::less<std::string >, std::allocator<MapPosInfo> > m_mapPosTable
//
//		 class std::map<std::string, MapPosInfo,
// std::less<std::string >, std::allocator<MapPosInfo> > * m_divisionMapPosTable
//		 class std::map<int, MapPosInfo,
// std::less<int>,  std::allocator<MapPosInfo> > m_divisionMapPosIndexTable
//
//		 int m_initMapPos
//		 int m_maxNum
//		 int m_hpIndex
//		 int m_spIndex
//		 int m_xorIndex
//		 int m_maxhpIndex
//		 int m_maxspIndex
//		 int[0xc] m_xorValue
//		 int[0xc] m_maxhp
//		 int[0xc] m_maxsp
//		 int[0xc] m_hp
//		 int[0xc] m_sp
//		 struct CommonObject m_objParser
//
//		 int m_fogOn
//		 int m_isAura
//		 int m_isNoShift
//		 int m_isNoCtrl
//		 int m_isWindow
//		 int m_isSkillFail
//		 int m_isLogInOut
//		 int m_isShopping
//		 int m_isQuickSpell
//		 int m_isQuickSpell2
//		 int m_isMiniGame
//		 int m_isQ2begin
//		 int m_isNoTalkMsg
//		 int m_isNoTalkMsg2
//		 int m_isNoTrade
//		 int m_isEffectOn
//		 int m_isDA_illusionON
//		 int m_bgmIsPaused
//		 int m_isMinEffect
//		 int m_isMinEffectOld
//		 int m_isPropertyDisableLockOn
//		 int m_isPropertyCountPK
//		 int m_isPropertyNoParty
//		 int m_amIPartyMaster
//		 int m_amIParent
//		 int m_isAttrIndicator
//		 int m_bMakeMissEffect
//		 int m_isLowSystemMemory
//		 int m_bAutoOpenDetailWindowIfLowMemory
//		 unsigned char m_isShowNameTypeOld
//		 unsigned char RandomScreenFlag
//		 unsigned char m_isCheckToPcbang
//		 int m_SelectAccountNumber
//		 int m_isBattle
//		 int m_isBattleChat
//		 int m_isBmChat
//		 int m_isStartBmChat
//		 unsigned int m_timeCheckValue
//		 unsigned long m_dwOldTime
//		 int m_talkType
//		 int m_langType
//		 int m_expDivType
//		 int m_itemCollectType
//		 int m_itemDivType
//		 class std::string m_partyRequestName
//
//		 class std::string m_partyName
//
//		 class std::string m_accountAddress
//
//		 class std::string m_registrationUrl
//
//		 class std::string m_myShopName
//
//		 class std::string m_accountPort
//
//		 class std::string m_lastServerName
//
//		 unsigned char m_emblemState
//		 int m_isSaveChat
//		 int m_sexCheck
//		 int m_cNameCheck
//		 unsigned long m_playingTime
//		 short m_MightyGauge
//		 char m_GaugePacket
//		 class std::string killName
//
//		 class std::string killedName
//
//		 int m_winPoint
//		 int m_losePoint
//		 struct _SYSTEMTIME expireTime
//
//		 unsigned long m_homunGID
//		 char[0x20] m_homunName
//		 int m_homunAtk
//		 int m_homunMatk
//		 int m_homunHit
//		 int m_homunCritical
//		 int m_homunDef
//		 int m_homunMdef
//		 int m_homunFlee
//		 int m_homunAspd
//		 int m_homunJob
//		 int m_homunLevel
//		 int m_homunHP
//		 int m_homunMaxHP
//		 int m_homunSP
//		 int m_homunMaxSP
//		 int m_homunFriendly
//		 int m_homunAcc
//		 int m_homunExp
//		 int m_homunNextExp
//		 int m_homunHungry
//		 int m_homunMaxHungry
//		 int m_isHomunNameModified
//		 unsigned long m_homunEnemyGID
//		 int m_homunEnemyX
//		 int m_homunEnemyY
//		 int m_moveHomunEnemy
//		 int m_selectHomunEnemy
//		 int m_attackHomunEnemy
//		 int m_homunAlive
//		 int m_onTraceAI
//		 int m_onHoUserAI
//		 int m_homunStateId
//		 int m_oldHomunHungry
//		 int m_homunATKRange
//		 unsigned long m_merGID
//		 char[0x20] m_merName
//		 int m_merAtk
//		 int m_merMatk
//		 int m_merHit
//		 int m_merCritical
//		 int m_merDef
//		 int m_merMdef
//		 int m_merFlee
//		 int m_merAspd
//		 int m_merHP
//		 int m_merMaxHP
//		 int m_merJob
//		 int m_merLevel
//		 int m_merSP
//		 int m_merMaxSP
//		 int m_merFaith
//		 int m_merCallNum
//		 int m_merKillCounter
//		 int m_merATKRange
//		 long m_merExpireDate
//		 unsigned long m_merEnemyGID
//		 int m_merEnemyX
//		 int m_merEnemyY
//		 int m_moveMerEnemy
//		 int m_onMerUserAI
//		 int m_selectMerEnemy
//		 int m_attackMerEnemy
//		 int m_merAlive
//		 int m_merStateId
//		 unsigned char m_onAutoMSG
//		 class std::string m_strAutoMSG
//
//		 unsigned long m_changeNameGID
//		 char[0x18] m_changeCharName
//		 int m_cashPoint
//		 int m_freePoint
//		 unsigned char[0xd] m_battleMsgOnOffSet
//		 unsigned char m_bRefuseInviteParty
//		 int m_onDunInfoWnd
//		 int dunInfoWndX
//		 int dunInfoWndY
//		 int m_dunState
//		 int m_tmpDunState
//		 class std::string m_dunName
//
//		 int m_priority
//		 long m_destroyTime
//		 long m_enterTimeOut
//		 int m_bOpenEquipedItem
//		 int m_otherUserJob
//		 int m_otherUserSex
//		 int m_otherUserHead
//		 int m_otherUserAccessory
//		 int m_otherUserAccessory2
//		 int m_otherUserAccessory3
//		 int m_otherUserBodyPalette
//		 int m_otherUserHeadPalette
//		 char[0x18] m_otherUserName
//		 unsigned char m_bIsUAE
//		public class CSession & operator=(const class CSession &)
//		public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_CORE_SESSION_H_
