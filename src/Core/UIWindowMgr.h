#ifndef DOLORI_CORE_UIWINDOWMGR_H_
#define DOLORI_CORE_UIWINDOWMGR_H_

#include <list>
#include <string>

#include "Files/BitmapRes.h"
#include "Modes/Mode.h"
#include "Render/Surface.h"
#include "UI/UIFrameWnd.h"
#include "UI/UILoginWnd.h"
#include "UI/UISelectCharWnd.h"
#include "UI/UIWindow.h"

typedef enum WINDOWID {
  WID_BASICINFOWND = 0x0,
  WID_CHATWND = 0x1,
  WID_SELECTSERVERWND = 0x2,
  WID_LOGINWND = 0x3,
  WID_MAKECHARWND = 0x4,
  WID_SELECTCHARWND = 0x5,
  WID_WAITWND = 0x6,
  WID_LOADINGWND = 0x7,
  WID_ITEMWND = 0x8,
  WID_TOOLTIPWND = 0x9,
  WID_EQUIPWND = 0xa,
  WID_STATUSWND = 0xb,
  WID_ITEMCOLLECTIONWND = 0xc,
  WID_OPTIONWND = 0xd,
  WID_MINIMAPZOOMWND = 0xe,
  WID_ITEMDROPCNTWND = 0xf,
  WID_SAYDIALOGWND = 0x10,
  WID_CHOOSEWND = 0x11,
  WID_MENUWND = 0x12,
  WID_RESTARTWND = 0x13,
  WID_NOTICECONFIRMWND = 0x14,
  WID_NOTIFYLEVELUPWND = 0x15,
  WID_ITEMSHOPWND = 0x16,
  WID_ITEMPURCHASEWND = 0x17,
  WID_ITEMSELLWND = 0x18,
  WID_CHOOSESELLBUYWND = 0x19,
  WID_COMBOBOXWND = 0x1a,
  WID_CHATROOMMAKEWND = 0x1b,
  WID_CHATROOMWND = 0x1c,
  WID_PASSWORDWND = 0x1d,
  WID_CHATROOMCHANGEWND = 0x1e,
  WID_EXCHANGEWND = 0x1f,
  WID_EXCHANGEACCEPTWND = 0x20,
  WID_ITEMSTOREWND = 0x21,
  WID_MESSENGERGROUPWND = 0x22,
  WID_JOINPARTYACCEPTWND = 0x23,
  WID_SHORTCUTWND = 0x24,
  WID_SKILLLISTWND = 0x25,
  WID_TIPOFTHEDAYWND = 0x26,
  WID_CHOOSEWARPWND = 0x27,
  WID_MERCHANTITEMWND = 0x28,
  WID_MERCHANTSHOPMAKEWND = 0x29,
  WID_MERCHANTMIRRORITEMWND = 0x2a,
  WID_MERCHANTITEMSHOPWND = 0x2b,
  WID_MERCHANTITEMPURCHASEWND = 0x2c,
  WID_MERCHANTITEMMYSHOPWND = 0x2d,
  WID_SKILLDESCRIBEWND = 0x2e,
  WID_CARDITEMILLUSTWND = 0x2f,
  WID_QUITWND = 0x30,
  WID_NOTIFYJOBLEVELUPWND = 0x31,
  WID_ITEMPARAMCHANGEDISPLAYWND = 0x32,
  WID_CANDIDATEWND = 0x33,
  WID_COMPOSITIONWND = 0x34,
  WID_PARTYSETTINGWND = 0x35,
  WID_EMAILADDRESSWND = 0x36,
  WID_SKILLNAMECHANGEWND = 0x37,
  WID_NPCEDITDIALOGWND = 0x38,
  WID_DETAILLEVELWND = 0x39,
  WID_NOTIFYITEMOBTAINWND = 0x3a,
  WID_GUILDWND = 0x3b,
  WID_GUILDINFOMANAGEWND = 0x3c,
  WID_GUILDMEMBERMANAGEWND = 0x3d,
  WID_GUILDPOSITIONMANAGEWND = 0x3e,
  WID_GUILDSKILLWND = 0x3f,
  WID_GUILDBANISHEDMEMBERWND = 0x40,
  WID_GUILDNOTICEWND = 0x41,
  WID_GUILDTOTALINFOWND = 0x42,
  WID_WHISPERLISTWND = 0x43,
  WID_FRIENDOPTIONWND = 0x44,
  WID_MESSENGERWND = 0x45,
  WID_JOINGUILDACCEPTWND = 0x46,
  WID_WEBBROWSERWND = 0x47,
  WID_ALLYGUILDACCEPTWND = 0x48,
  WID_ITEMIDENTIFYWND = 0x49,
  WID_ITEMCOMPOSITIONWND = 0x4a,
  WID_GUILDLEAVEREASONDESCWND = 0x4b,
  WID_GUILDBANREASONDESCWND = 0x4c,
  WID_MONSTERINFOWND = 0x4d,
  WID_ILLUSTWND = 0x4e,
  WID_MAKETARGETLISTWND = 0x4f,
  WID_MAKETARGETPROCESSWND = 0x50,
  WID_MAKETARGETRESULTWND = 0x51,
  WID_COMBINEDCARDITEMCOLLECTIONWND = 0x52,
  WID_CALCULATORWND = 0x53,
  WID_TALKBOXTRAPINPUTWND = 0x54,
  WID_KEYSTROKEWND = 0x55,
  WID_EMOTIONWND = 0x56,
  WID_EMOTIONLISTWND = 0x57,
  WID_PETINFOWND = 0x58,
  WID_TOPRANKWND = 0x59,
  WID_SELECTPETEGGWND = 0x5a,
  WID_PETTAMINGDECEIVEWND = 0x5b,
  WID_CNTWND = 0x5c,
  WID_NOTICEWND = 0x5d,
  WID_MAKINGARROWLISTWND = 0x5e,
  WID_SELECTCARTWND = 0x5f,
  WID_MINIGAMEWND = 0x60,
  WID_SELECTMINIGAMEWND = 0x61,
  WID_MINIGAMESCOREWND = 0x62,
  WID_SPELLLISTWND = 0x63,
  WID_NPCTEXTEDITDIALOGWND = 0x64,
  WID_GRAFFISTRBOXWND = 0x65,
  WID_SHOWNEEDITEMLISTWND = 0x66,
  WID_PROHIBITLISTWND = 0x67,
  WID_COUPLEACCEPTWND = 0x68,
  WID_BABYACCEPTWND = 0x69,
  WID_BOOKWND = 0x6a,
  WID_ITEMREPAIRWND = 0x6b,
  WID_SYSCHECKWND = 0x6c,
  WID_JOINFRIENDACCEPTWND = 0x6d,
  WID_BABYACCEPTWND2 = 0x6e,
  WID_WEAPONREFINEWND = 0x6f,
  WID_COMMANDLISTWND = 0x70,
  WID_HOMUNINFOWND = 0x71,
  WID_HOMUNSKILLLISTWND = 0x72,
  WID_STOREPASSWORDINPUTWND = 0x73,
  WID_AUTOMESSAGEWND = 0x74,
  WID_MAILLISTWND = 0x75,
  WID_MAILVIEWWND = 0x76,
  WID_STARPLACE_ACCEPTWND = 0x77,
  WID_AUCTIONWND = 0x78,
  WID_AUCTIONMSGWND = 0x79,
  WID_IMGMENUWND = 0x7a,
  WID_GRON_MESSENGERWND = 0x7b,
  WID_GRON_OPTIONWND = 0x7c,
  WID_GRON_ALERTWND = 0x7d,
  WID_GRON_MESSAGEWND = 0x7e,
  WID_GRON_SETTINGWND = 0x7f,
  WID_GRON_MEMOWND = 0x80,
  WID_GRON_BARWND = 0x81,
  WID_PTNUMWND = 0x82,
  WID_PTACINFOWND = 0x83,
  WID_MERINFOWND = 0x84,
  WID_MERSKILLLISTWND = 0x85,
  WID_SELCHARFORUSERVERWND = 0x86,
  WID_CHANGENAMEWND = 0x87,
  WID_REBIRTHWND = 0x88,
  WID_SUBCHATWND_ST = 0x89,
  WID_SUBCHATWND_BT = 0x8a,
  WID_BATTLEMSG_OPTIONWND = 0x8b,
  WID_SUBCHAT_MINIWND = 0x8c,
  WID_QUESTWND = 0x8d,
  WID_QUEST_DETAIL_WND = 0x8e,
  WID_ROSHOPWND = 0x8f,
  WID_MEMORIAL_DUN_WND = 0x90,
  WID_YOURITEMWND = 0x91,
  WID_OTHERUSER_EQUIPWND = 0x92,
  WID_ROMAPWND = 0x93,
  WID_ADMINTOOLWND = 0x94,
  WID_ADMINTOOL_MINIWND = 0x95,
  WID_NOTIFYQUESTWND = 0x96,
  WID_LAST = 0x97,
} WINDOWID;

class CUIWindowMgr {
 public:
  CUIWindowMgr();
  ~CUIWindowMgr();

  void SetSize(int, int);
  void SetWallpaper(CBitmapRes *);
  void RenderWallPaper();
  void Render(CMode *);
  CUIFrameWnd *MakeWindow(WINDOWID windowId);
  void PostQuit(CUIWindow *wnd);
  void AddWindow(CUIWindow *);
  void RemoveWindow(CUIWindow *);
  void RemoveAllWindows();
  void InvalidateUpdateNeededUI();
  CUIWindow *GetCapture();
  void SetCapture(CUIWindow *);
  void ReleaseCapture();
  void SetFocusEdit(CUIWindow *window);
  CUIWindow *GetFocusEdit();
  int ProcessInput();
  int ErrorMsg(const char *msg, int type, int isDefYes, int changeMsg,
               unsigned int autoReturnTime);

 private:
  int m_chatWndX;
  int m_chatWndY;
  int m_chatWndHeight;
  int m_chatWndShow;
  int m_gronMsnWndShow;
  int m_gronMsgWndShow;
  int m_chatWndStatus;
  float m_miniMapZoomFactor;
  unsigned long m_miniMapArgb;
  int m_isDrawCompass;
  int m_isDragAll;
  int m_conversionMode;
  std::list<CUIWindow *> m_children;
  std::list<CUIWindow *> m_quit_window;
  std::list<CUIWindow *> m_nameWaitingList;
  // std::map<CUIWindow *, CSnapInfo, std::less<CUIWindow *>> m_snapInfo;
  CUIWindow *m_captureWindow;
  CUIWindow *m_editWindow;
  CUIWindow *m_modalWindow;
  CUIWindow *m_last_hit_window;
  bool m_isInvalidatedByForce;
  class UILoadingWnd *m_loadingWnd;
  class UIMinimapZoomWnd *m_minimapZoomWnd;
  class UIStatusWnd *m_statusWnd;
  class UINewChatWnd *m_chatWnd;
  CUILoginWnd *m_loginWnd;
  class UIItemWnd *m_itemWnd;
  class UIQuestWnd *m_questWnd;
  class UIBasicInfoWnd *m_basicInfoWnd;
  class UIEquipWnd *m_equipWnd;
  class UIOptionWnd *m_optionWnd;
  class UIShortCutWnd *m_shortCutWnd;
  class UIItemDropCntWnd *m_itemDropCntWnd;
  class UISayDialogWnd *m_sayDialogWnd;
  class UIChooseWnd *m_chooseWnd;
  class UIItemIdentifyWnd *m_itemIdentifyWnd;
  class UIItemRepairWnd *m_itemRepairWnd;
  class UIWeaponRefineWnd *m_weaponRefineWnd;
  class UIItemCompositionWnd *m_itemCompositionWnd;
  class UIChooseWarpWnd *m_chooseWarpWnd;
  class UIMenuWnd *m_menu;
  class UIComboBoxWnd *m_comboBoxWnd;
  class UIItemCollectionWnd *m_itemCollectionWnd;
  class UICombinedCardItemCollectionWnd *m_combinedCardItemCollectionWnd;
  class UIItemParamChangeDisplayWnd *m_itemParamChangeDisplayWnd;
  class UISkillDescribeWnd *m_skillDescribeWnd;
  class UIQuestDetailWnd *m_questDetailWnd;
  class UIQuitWnd *m_quitWnd;
  class UIRestartWnd *m_restartWnd;
  class UICardItemIllustWnd *m_cardItemIllustWnd;
  class UINotifyLevelUpWnd *m_notifyLevelUpWnd;
  class UINotifyJobLevelUpWnd *m_notifyJobLevelUpWnd;
  class UINotifyQuestWnd *m_notifyQuestWnd;
  class UIItemShopWnd *m_itemShopWnd;
  class UIItemPurchaseWnd *m_itemPurchaseWnd;
  class UIItemSellWnd *m_itemSellWnd;
  class UIChooseSellBuyWnd *m_chooseSellBuyWnd;
  class UIChatRoomMakeWnd *m_chatRoomMakeWnd;
  class UIChatRoomChangeWnd *m_chatRoomChangeWnd;
  class UIChatRoomWnd *m_chatRoomWnd;
  class UIPasswordWnd *m_passwordWnd;
  class UIExchangeWnd *m_exchangeWnd;
  class UIExchangeAcceptWnd *m_exchangeAcceptWnd;
  class UIItemStoreWnd *m_itemStoreWnd;
  class UISkillListWnd *m_skillListWnd;
  class UIMessengerGroupWnd *m_messengerGroupWnd;
  class UIJoinPartyAcceptWnd *m_joinPartyAcceptWnd;
  class UICoupleAcceptWnd *m_CoupleAcceptWnd;
  class UIStarPlaceAcceptWnd *m_StarPlaceAcceptWnd;
  class UIYourItemWnd *m_YourItemWnd;
  class UIBabyAcceptWnd *m_BabyAcceptWnd;
  class UIBabyAcceptWnd2 *m_BabyAcceptWnd2;
  class UIJoinGuildAcceptWnd *m_joinGuildAcceptWnd;
  class UIAllyGuildAcceptWnd *m_allyGuildAcceptWnd;
  class UITipOfTheDayWnd *m_tipOfTheDayWnd;
  class UIMerchantItemWnd *m_merchantItemWnd;
  class UIMerchantMirrorItemWnd *m_merchantMirrorItemWnd;
  class UIMerchantShopMakeWnd *m_merchantShopMakeWnd;
  class UIMerchantItemShopWnd *m_merchantItemShopWnd;
  class UIMerchantItemMyShopWnd *m_merchantItemMyShopWnd;
  class UIMerchantItemPurchaseWnd *m_merchantItemPurchaseWnd;
  class UIPartySettingWnd *m_partySettingWnd;
  class UISkillNameChangeWnd *m_skillNameChangeWnd;
  class UINpcEditDialogWnd *m_npcEditDialogWnd;
  class UINpcTextEditDialogWnd *m_npcTextEditDialogWnd;
  class UIDetailLevelWnd *m_detailLevelWnd;
  class UINotifyItemObtainWnd *m_notifyItemObtainWnd;
  class UIGuildInfoManageWnd *m_guildInfoManageWnd;
  class UIGuildMemberManageWnd *m_guildMemberManageWnd;
  class UIGuildPositionManageWnd *m_guildPositionManageWnd;
  class UIGuildSkillWnd *m_guildSkillWnd;
  class UIGuildBanishedMemberWnd *m_guildBanishedMemberWnd;
  class UIGuildNoticeWnd *m_guildNoticeWnd;
  class UIGuildTotalInfoWnd *m_guildTotalInfoWnd;
  class UIFriendOptionWnd *m_friendOptionWnd;
  class UIGuildLeaveReasonDescWnd *m_guildLeaveReasonDescWnd;
  class UIGuildBanReasonDescWnd *m_guildBanReasonDescWnd;
  class UIIllustWnd *m_illustWnd;
  class UIMakeTargetListWnd *m_metalListWnd;
  class UIMakeTargetProcessWnd *m_metalProcessWnd;
  class UIMakeTargetResultWnd *m_metalResultWnd;
  class UIEmotionWnd *m_emotionWnd;
  class UIEmotionListWnd *m_emotionListWnd;
  class UIProhibitListWnd *m_prohibitListWnd;
  class UIPetInfoWnd *m_petInfoWnd;
  class UIPetEggListWnd *m_selectPetEggWnd;
  class UIPetTamingDeceiveWnd *m_petTamingDeceiveWnd;
  class UIMakingArrowListWnd *m_makingArrowListWnd;
  class UISelectCartWnd *m_selectCartWnd;
  class UISpellListWnd *m_spellListWnd;
  class UICandidateWnd *m_candidateWnd;
  class UICompositionWnd *m_compositionWnd;
  class UIKeyStrokeWnd *m_keyStrokeWnd;
  class UIBookWnd *m_bookWnd;
  class UIJoinFriendAcceptWnd *m_joinFriendAcceptWnd;
  class UICommandListWnd *m_commandListWnd;
  class UIHomunInfoWnd *m_homunInfoWnd;
  class UISkillListWnd *m_homunSkillListWnd;
  class UIMerInfoWnd *m_merInfoWnd;
  class UISkillListWnd *m_merSkillListWnd;
  class UIAutoMessageWnd *m_autoMessageWnd;
  class UIMailListWnd *m_mailListWnd;
  class UIMailViewWnd *m_mailViewWnd;
  class UIAuctionWnd *m_auctionWnd;
  class UIAuctionMsgWnd *m_auctionMsgWnd;
  class UIImgMenuWnd *m_imgMenuWnd;
  CUISelectCharWnd *m_selectCharWnd;
  class UISelCharForUServerWnd *m_selCharForUServerWnd;
  class UIChangeNameWnd *m_changeNameWnd;
  class UIRebirthWnd *m_rebirthWnd;
  class UISubChatHisWnd *m_subChatWndST;
  class UISubChatHisWnd *m_subChatWndBT;
  class UIBattleMsgOptionWnd *m_battleMsgOpionWnd;
  class UISubChatMiniWnd *m_subChatMiniWnd;
  unsigned char m_chatWndStickOn;
  unsigned char m_onStSubChat;
  unsigned char m_onBtSubChat;
  class UIMemorialDunWnd *m_memorialDunWnd;
  class UIEquipWnd *m_otherUserEquipWnd;
  class UIRoMapWnd *m_roMapWnd;
  int m_last_mouse_x;
  int m_last_mouse_y;
  int m_modalResult;
  CSurface *m_wallpaperSurface;
  int m_w;
  int m_h;
  std::string m_wallPaperBmpName;
  short T_Logo_X;
  short T_Logo_Y;
  short T_Char_X;
  short T_Char_Y;
  short T_Tape_Y;
  short T_12Age_X;
  short T_12Age_Y;
  short T_Grav_X;
  short T_Grav_Y;
  short T_Intel_X;
  short T_Intel_Y;
  char T_CLICK;
};

#endif  // DOLORI_CORE_UIWINDOWMGR_H_
