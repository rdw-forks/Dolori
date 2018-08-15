#ifndef DOLORI_COMMON_GLOBALS_H_
#define DOLORI_COMMON_GLOBALS_H_

#include <vector>

#include "Common/MsgStrMgr.h"
#include "Common/character_info.h"
#include "Common/server_type.h"
#include "Common/service_type.h"
#include "Core/FileMgr.h"
#include "Core/ModeMgr.h"
#include "Core/ResMgr.h"
#include "Core/Session.h"
#include "Core/UIWindowMgr.h"
#include "Input/Language.h"
#include "Input/Mouse.h"
#include "Network/RagConnection.h"
#include "Render/3dDevice.h"
#include "Render/FontMgr.h"
#include "Render/Renderer.h"
#include "Render/TexMgr.h"

extern CModeMgr* g_ModeMgr;
extern CSession* g_Session;
extern CRagConnection* g_RagConnection;
extern C3dDevice* g_3dDevice;
extern CRenderer* g_Renderer;
extern CFileMgr* g_FileMgr;
extern CTexMgr* g_TexMgr;
extern CUIWindowMgr* g_WindowMgr;
extern CResMgr* g_ResMgr;
extern CFontMgr* g_FontMgr;
extern CMouse* g_Mouse;
extern CMsgStrMgr* g_MsgStrMgr;
extern CLanguage* g_Language;
extern char TITLE_FILE[256];
extern ServiceType g_serviceType;
extern ServerType g_serverType;
extern unsigned int g_version;
extern char g_clientType;
extern bool g_hideAccountList;
extern bool g_passwordEncrypt;
extern bool g_passwordEncrypt2;
extern bool g_readFolderFirst;
extern bool g_extendedSlot;
extern std::vector<std::string> s_loadingScreenList;
extern bool g_isGravityID;
extern unsigned short g_loginStartMode;
extern char g_accountAddr[64];
extern char g_accountPort[64];
extern SERVER_ADDRESS g_charServerAddr;
extern SERVER_ADDRESS g_zoneServerAddr;
extern bool g_sys_quit;
extern char g_current_map[16];
extern bool g_bUseCommand;
extern bool g_mustPumpOutReceiveQueue;
extern bool g_NameBalloonShorten;
extern bool g_NameBalloonfontBold;
extern bool g_passwordWrong;
extern std::vector<unsigned long> s_dwAdminAID;

// Used for communication between objects, not a good design
extern CHARACTER_INFO g_charInfo;
extern uint8_t g_selected_char_num;

#endif  // DOLORI_COMMON_GLOBALS_H_
