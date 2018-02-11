#ifndef DOLORI_MODES_MODE_H_
#define DOLORI_MODES_MODE_H_

#include <stdlib.h>
#include "Common/Vector2d.h"

typedef enum MODE_MSG {
  MM_COMMAND = 0x0,
  MM_SOCKETERROR = 0x1,
  MM_QUIT = 0x2,
  MM_RECV = 0x3,
  MM_SHOWMOUSEPOINTER = 0x4,
  MM_HIDEMOUSEPOINTER = 0x5,
  MM_CHATMSG = 0x6,
  MM_BROADCASTMSG = 0x7,
  MM_QUERYCHARICTORINFO = 0x8,
  MM_QUERYRSWNAME = 0x9,
  MM_CONTACTNPC = 0xa,
  MM_WHISPERMSG = 0xb,
  MM_ADDREGISTERPOS = 0xc,
  MM_DELETEREGISTERPOS = 0xd,
  MM_DISCONNECT_CHARACTER = 0xe,
  MM_DISCONNECT_ALL_CHARACTER = 0xf,
  MM_ITEMTHROW = 0x10,
  MM_BEGIN_DRAG_FROM_ITEMWND = 0x11,
  MM_DROP = 0x12,
  MM_CANCEL_DRAG = 0x13,
  MM_WEAR_EQUIP = 0x14,
  MM_TAKE_OFF_EQUIP = 0x15,
  MM_BEGIN_DRAG_FROM_EQUIPMWND = 0x16,
  MM_ITEMTHROW_THROUGH_DROPCNTWND = 0x17,
  MM_REQ_NEXT_SCRIPT = 0x18,
  MM_CHOOSE_MENU = 0x19,
  MM_MENUSELECTED = 0x1a,
  MM_RESTART = 0x1b,
  MM_SETLOCKONMOUSE = 0x1c,
  MM_USEITEM = 0x1d,
  MM_GOTOIDENTRY = 0x1e,
  MM_REQ_STATUS = 0x1f,
  MM_STATUS_CHANGE = 0x20,
  MM_REQ_EMOTION = 0x21,
  MM_REQ_NUM_USER = 0x22,
  MM_PLAYER_EMOTION_END = 0x23,
  MM_BEGIN_DRAG_FROM_ITEMSHOPWND = 0x24,
  MM_REQ_PURCHASE = 0x25,
  MM_REQ_SELL = 0x26,
  MM_REQ_ITEM_EXPLANATION_BYNAME = 0x27,
  MM_ACK_SELL = 0x28,
  MM_ACK_BUY = 0x29,
  MM_REFRESH_SHOPWND = 0x2a,
  MM_RELEASE_QUEST = 0x2b,
  MM_BEGIN_DRAG_FROM_ITEMPURCHASEWND = 0x2c,
  MM_BEGIN_DRAG_FROM_ITEMSELLWND = 0x2d,
  MM_TOGGLE_PLAYERGAGE = 0x2e,
  MM_PROCESS_TALK_TYPE = 0x2f,
  MM_CREATE_CHATROOM = 0x30,
  MM_CHANGE_CHATROOM = 0x31,
  MM_REQ_ENTER_ROOM = 0x32,
  MM_REQ_ROLE_CHANGE = 0x33,
  MM_REQ_EXPEL_MEMBER = 0x34,
  MM_REQ_EXIT_ROOM = 0x35,
  MM_REQ_EXCHANGE_ITEM = 0x36,
  MM_ACK_EXCHANGE_ITEM = 0x37,
  MM_ADD_EXCHANGE_ITEM = 0x38,
  MM_CONCLUDE_EXCHANGE_ITEM = 0x39,
  MM_CANCEL_EXCHANGE_ITEM = 0x3a,
  MM_EXEC_EXCHANGE_ITEM = 0x3b,
  MM_BEGIN_DRAG_FROM_ITEMSTOREWND = 0x3c,
  MM_ADD_ITEM_TO_STORE = 0x3d,
  MM_MOVE_ITEM_FROM_STORE_TO_BODY = 0x3e,
  MM_CLOSE_STORE = 0x3f,
  MM_MAKE_GROUP = 0x40,
  MM_REQ_JOIN_GROUP = 0x41,
  MM_JOIN_GROUP = 0x42,
  MM_REQ_LEAVE_GROUP = 0x43,
  MM_REQ_EXPEL_GROUP_MEMBER = 0x44,
  MM_ADDPARTYPOS = 0x45,
  MM_DELETEPARTYPOS = 0x46,
  MM_DELETEPARTYPOSALL = 0x47,
  MM_CHAT_PARTY = 0x48,
  MM_BEGIN_DRAG_FROM_SHORTCUTWND = 0x49,
  MM_UPGRADE_SKILLLEVEL = 0x4a,
  MM_SCREENSHOT = 0x4b,
  MM_USE_SKILL = 0x4c,
  MM_USE_SKILL_TOGROUND = 0x4d,
  MM_CANCEL_USE_SKILL = 0x4e,
  MM_HANG_USE_SKILL = 0x4f,
  MM_CANCEL_LOCKON = 0x50,
  MM_BEGIN_DRAG_FROM_SKILLLISTWND = 0x51,
  MM_SELECT_WARPPOINT = 0x52,
  MM_REMEMBER_WARPPOINT = 0x53,
  MM_MOVE_ITEM_FROM_BODY_TO_CART = 0x54,
  MM_MOVE_ITEM_FROM_CART_TO_BODY = 0x55,
  MM_MOVE_ITEM_FROM_STORE_TO_CART = 0x56,
  MM_MOVE_ITEM_FROM_CART_TO_STORE = 0x57,
  MM_REQ_CARTOFF = 0x58,
  MM_BEGIN_DRAG_FROM_MERCHANTITEMWND = 0x59,
  MM_REQ_CLOSESTORE = 0x5a,
  MM_REQ_OPENSTORE = 0x5b,
  MM_PC_PURCHASE_ITEMLIST_FROMMC = 0x5c,
  MM_BEGIN_DRAG_FROM_MERCHANTMIRRORITEMWND = 0x5d,
  MM_BEGIN_DRAG_FROM_MERCHANTSHOPMAKEWND = 0x5e,
  MM_REQ_BUY_FROMMC = 0x5f,
  MM_BEGIN_DRAG_FROM_MERCHANTITEMSHOPWND = 0x60,
  MM_BEGIN_DRAG_FROM_MERCHANTITEMPURCHASEWND = 0x61,
  MM_PKMODE_CHANGE = 0x62,
  MM_MAKE_SKILL_USED_MSG = 0x63,
  MM_WEAR_EQUIP_ARROW = 0x64,
  MM_QUIT_GAME = 0x65,
  MM_CLOSE_DIALOG = 0x66,
  MM_REFRESH_MUSIC = 0x67,
  MM_ITEM_CREATE = 0x68,
  MM_MOVETO_MAP = 0x69,
  MM_USESKILL_LEVEL_PLUS = 0x6a,
  MM_USESKILL_LEVEL_MINUS = 0x6b,
  MM_GET_SKILL_USE_TYPE = 0x6c,
  MM_CHANGE_GROUPEXPOPTION = 0x6d,
  MM_GET_SKILL_USE_LEVEL = 0x6e,
  MM_CHANGE_SKILL_NAME = 0x6f,
  MM_SEND_NUMBER_TO_NPC = 0x70,
  MM_SHOW_IMAGE = 0x71,
  MM_INITWHISPERMENU = 0x72,
  MM_SEND_GUILD_EMBLEM = 0x73,
  MM_REQ_CHANGE_MEMBERPOS = 0x74,
  MM_REQ_CHANGE_GUILD_POSITIONINFO = 0x75,
  MM_REQ_GUILD_MENUINTERFACE = 0x76,
  MM_REQ_DISORGANIZE_GUILD = 0x77,
  MM_REQ_GUILD_MENU = 0x78,
  MM_REQ_GUILD_EMBLEM_IMG = 0x79,
  MM_REQ_OPEN_MEMBER_INFO = 0x7a,
  MM_REQ_LEAVE_GUILD = 0x7b,
  MM_REQ_BAN_GUILD = 0x7c,
  MM_REQ_MAKE_GUILD = 0x7d,
  MM_USING_SKILL = 0x7e,
  MM_JOIN_GUILD = 0x7f,
  MM_REQ_JOIN_GUILD = 0x80,
  MM_TESTPACKET = 0x81,
  MM_REQ_GIVE_MANNER_POINT = 0x82,
  MM_GUILD_NOTICE = 0x83,
  MM_REQ_ALLY_GUILD = 0x84,
  MM_ALLY_GUILD = 0x85,
  MM_REQ_ITEMIDENTIFY = 0x86,
  MM_QUAKE = 0x87,
  MM_REQ_ITEMCOMPOSITION_LIST = 0x88,
  MM_REQ_ITEMCOMPOSITION = 0x89,
  MM_REQ_HOSTILE_GUILD = 0x8a,
  MM_QUEUE_REQ_GUILD_EMBLEM_IMG = 0x8b,
  MM_REQ_DELETE_RELATED_GUILD = 0x8c,
  MM_REQ_DISCONNECT = 0x8d,
  MM_CHAT_GUILD = 0x8e,
  MM_REQ_MAKING_ITEM = 0x8f,
  MM_USE_SKILL_TOGROUND_WITH_TALKBOX = 0x90,
  MM_REQ_BIRDOFF = 0x91,
  MM_REQ_CHIKENOFF = 0x92,
  MM_BEGIN_DRAG_FROM_METALPROCESSWND = 0x93,
  MM_SETQUAKEINFO = 0x94,
  MM_ITEMPICKUP = 0x95,
  MM_REQUEST_ACT = 0x96,
  MM_REQUEST_MOVE = 0x97,
  MM_CHANGE_DIRECTION = 0x98,
  MM_GUILD_MEMBER_STATUS_CHANGE = 0x99,
  MM_QUIT_TO_IDENTRY = 0x9a,
  MM_RESET_PARAMETER = 0x9b,
  MM_REQ_CHANGE_MAPTYPE = 0x9c,
  MM_CHANGE_EFFECTSTATE = 0x9d,
  MM_PET_RENAME = 0x9e,
  MM_PETEGG_SELECT_FROM_LIST = 0x9f,
  MM_REQ_PETEGG_INFO = 0xa0,
  MM_PET_ACT = 0xa1,
  MM_PETDECEIVE_SHOOT = 0xa2,
  MM_COMMAND_PET = 0xa3,
  MM_REQ_GIVE_MANNER_POINT_PLUS = 0xa4,
  MM_REQ_GIVE_MANNER_POINT_MINUS = 0xa5,
  MM_ARROW_FROM_LIST = 0xa6,
  MM_SELECT_CART = 0xa7,
  MM_GUILD_MONEY = 0xa8,
  MM_REMOVE_TO_AID = 0xa9,
  MM_SHIFT_TO_GID = 0xaa,
  MM_RECALL_AID = 0xab,
  MM_RECALL_GID = 0xac,
  MM_FORCING_MOVE_AID = 0xad,
  MM_FORCING_MOVE_GID = 0xae,
  MM_BILLING_INFO = 0xaf,
  MM_MINI_GAME = 0xb0,
  MM_SELECT_SPELL = 0xb1,
  MM_SEND_TEXT_TO_NPC = 0xb2,
  MM_SONG_TALK = 0xb3,
  MM_REQ_ACCOUNT_NAME = 0xb4,
  MM_JOIN_COUPLE = 0xb5,
  MM_CONFORM_MAKEGROUP = 0xb6,
  MM_DORIDORI = 0xb7,
  MM_ADDGUILDPOS = 0xb8,
  MM_DELETEGUILDPOS = 0xb9,
  MM_DELETEGUILDPOSALL = 0xba,
  MM_JOIN_BABY = 0xbb,
  MM_REPAIRITEM_SELECT_FROM_LIST = 0xbc,
  MM_JOIN_FRIEND = 0xbd,
  MM_DELETE_FRIEND = 0xbe,
  MM_CHECK_ID = 0xbf,
  MM_RC_ID = 0xc0,
  MM_REQ_JOIN_BABY = 0xc1,
  MM_REQ_BLACKSMITH = 0xc2,
  MM_REQ_ALCHEMIST = 0xc3,
  MM_REFINEITEM_SELECT_FROM_LIST = 0xc4,
  MM_REQ_TAEKWON = 0xc5,
  MM_COMMAND_HOMUN = 0xc6,
  MM_MER_RENAME = 0xc7,
  MM_COMMAND_MER = 0xc8,
  MM_REQ_KILLER_RANK = 0xc9,
  MM_ACK_STORE_PASSWORD = 0xca,
  MM_BEGIN_DRAG_FROM_HOSKILLLISTWND = 0xcb,
  MM_HOMUN_WAIT = 0xcc,
  MM_STARPLACE_ACCEPT = 0xcd,
  MM_GET_MAIL_LIST = 0xce,
  MM_SEND_MAIL = 0xcf,
  MM_RESET_MAIL_ITEM = 0xd0,
  MM_OPEN_MAIL = 0xd1,
  MM_ADD_MAIL_ITEM = 0xd2,
  MM_DELETE_MAIL = 0xd3,
  MM_RETURN_MAIL = 0xd4,
  MM_GET_MAIL_ITEM = 0xd5,
  MM_BEGIN_DRAG_FROM_MAILWND = 0xd6,
  MM_RESET_AUCTION_ITEM = 0xd7,
  MM_ADD_AUCTION_ITEM = 0xd8,
  MM_ADD_AUCTION = 0xd9,
  MM_CANCEL_ADD_AUCTION = 0xda,
  MM_BUY_AUCTION = 0xdb,
  MM_SEARCH_AUCTION_ITEM = 0xdc,
  MM_AUCTION_REQ_MY_INFO = 0xdd,
  MM_AUCTION_MY_SELL_STOP = 0xde,
  MM_ITEM_FROM_LIST = 0xdf,
  MM_REQ_NS_IP = 0xe0,
  MM_GRON_LOGIN = 0xe1,
  MM_GRON_LOGOUT = 0xe2,
  MM_GRON_CHANGE_MY_CONDITION = 0xe3,
  MM_GRON_CHANGE_MY_NICK = 0xe4,
  MM_GRON_ADD_GROUP = 0xe5,
  MM_GRON_RENAME_GROUP = 0xe6,
  MM_GRON_DEL_GROUP = 0xe7,
  MM_REQ_DEPTH_GROUP = 0xe8,
  MM_GRON_ADD_FRIEND = 0xe9,
  MM_GRON_AGREE_FRIEND = 0xea,
  MM_GRON_BLOCK_FRIEND = 0xeb,
  MM_GRON_DEL_FRIEND = 0xec,
  MM_GRON_CHANGEGROUP_FRIEND = 0xed,
  MM_GRON_SEND_MEMO = 0xee,
  MM_GRON_READ_MEMO = 0xef,
  MM_GRON_DELETE_MEMO = 0xf0,
  MM_GRON_OPEN_MEMOWND = 0xf1,
  MM_CONFIRM_READ_MEMO = 0xf2,
  MM_GRON_PING = 0xf3,
  MM_REQ_LOG_START = 0xf4,
  MM_ACK_LOG_START = 0xf5,
  MM_REQ_LOG_END = 0xf6,
  MM_ACK_LOG_END = 0xf7,
  MM_REQ_CHATTING_ROOM = 0xf8,
  MM_REQ_CHAT_INVITE = 0xf9,
  MM_REQ_CHAT_CONNECT_FAIL = 0xfa,
  MM_REQ_CHATTING_FRIEND_INFO = 0xfb,
  MM_REQ_CHAT_ENTER = 0xfc,
  MM_REQ_CHAT_OPENWINDOW = 0xfd,
  MM_REQ_CHAT_CLOSE = 0xfe,
  MM_REQ_CHAT_BYE = 0xff,
  MM_REQ_CHAT_ADD_USER = 0x100,
  MM_REQ_CHAT_MSG_TICK = 0x101,
  MM_REQ_CHAT_MESSAGE = 0x102,
  MM_PT_PASSWORD = 0x103,
  MM_PT_ACCOUNT_INFO = 0x104,
  MM_RELEASE_QUEST_SH = 0x105,
  MM_REQ_HUNTING = 0x106,
  MM_REQ_MUNAK = 0x107,
  MM_REQ_DEATHKNIGHT = 0x108,
  MM_REQ_BUY_CASH_POINT = 0x109,
  MM_REBIRTH = 0x10a,
  MM_BEGIN_DRAG_FROM_MERSKILLLISTWND = 0x10b,
  MM_REQ_COLLECTOR = 0x10c,
  MM_SHORTCUT_KEY_CHANGE = 0x10d,
  MM_OPEN_EQUIPEDITEM_CHANGE = 0x10e,
  MM_CHAT_BATTLEFIELD = 0x10f,
  MM_LAST = 0x110,
} MODE_MSG;

class CMode {
 public:
  virtual ~CMode() = default;

  bool GetLoopCond();
  void SetLoopCond(bool);

  virtual void *SendMsg(size_t, void *, void *, void *);
  virtual void OnInit(const char *) = 0;
  virtual int OnRun() = 0;
  virtual void OnExit() = 0;

 protected:
  int m_sub_mode;
  int m_sub_mode_cnt;
  int m_next_sub_mode;
  int m_fadeInCount;
  bool m_loop_cond;
  int m_isConnected;
  class UITransBalloonText *m_helpBalloon;
  unsigned long m_helpBalloonTick;
  unsigned long m_mouseAnimStartTick;
  int m_isMouseLockOn;
  int m_screenShotNow;
  CVector2d m_mouseSnapDiff;
  int m_cursorActNum;
  int m_cursorMotNum;
};

// class CMode {
//	*
//		public void CMode(const class CMode &)
//		public void CMode::CMode()
//		public void CMode::~CMode()
//		public int CMode::OnRun()
//		public void CMode::OnInit(const char *)
//		public void CMode::OnExit()
//		public void CMode::OnUpdate()
//		public int CMode::SendMsg(int, int, int, int)
//		public void CMode::Initialize()
//		public void PostQuitMsg()
//		public void CMode::ScreenShot()
//		public void CMode::SetCursorAction(int)
//		public void CMode::RunFadeOut(int)
//		public void CMode::DrawSprite(int, int, class CActRes *, class
// CSprRes *, int, int, float, float, unsigned long) 		public void
// CMode::DrawTexture(struct tagRECT *, int, float, unsigned long, class
// CTexture
//*, struct UVRECT)
//		public void CMode::DrawBackGround2D(struct tagRECT *, int,
// float,  unsigned long, class CTexture *, struct UVRECT) 		public
// void  CMode::DrawMouseCursor() 		public void
// CMode::DrawBattleMode() 		public void CMode::MakeHelpBalloon(const
// char *, int, int,  unsigned long) 		public void
// CMode::ProcessHelpBalloon() 		public void CMode::ProcessFadeIn()
//		public void CMode::ProcessKeyBoard()
//		public int GetCursorAction()
//		public int GetCursorMotion()
//		public int GetSubMode()
//		public int GetLoopCond()
//		protected void CMode::OnChangeState(int)
//		protected void SetNextSubState(int)
//		protected void SetSubState(int)
//		int m_subMode
//		int m_subModeCnt
//		int m_nextSubMode
//		int m_fadeInCount
//		int m_loopCond
//		int m_isConnected
//		class UITransBalloonText * m_helpBalloon
//		unsigned long m_helpBalloonTick
//		unsigned long m_mouseAnimStartTick
//		int m_isMouseLockOn
//		int m_screenShotNow
//		struct vector2d m_mouseSnapDiff
//
//		int m_cursorActNum
//		int m_cursorMotNum
//		public class CMode & operator=(const class CMode &)
//		public void __local_vftable_ctor_closure()
//		public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_MODES_MODE_H_
