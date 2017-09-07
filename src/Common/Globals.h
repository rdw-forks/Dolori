#ifndef DOLORI_COMMON_GLOBALS_H_
#define DOLORI_COMMON_GLOBALS_H_

#include <vector>
#include "../Common/character_info.h"
#include "../Core/FileMgr.h"
#include "../Core/ModeMgr.h"
#include "../Core/ResMgr.h"
#include "../Core/Session.h"
#include "../Core/UIWindowMgr.h"
#include "../Input/Mouse.h"
#include "../Network/RagConnection.h"
#include "../Render/3dDevice.h"
#include "../Render/Renderer.h"
#include "../Render/TexMgr.h"

extern CModeMgr* g_ModeMgr;
extern CSession* g_Session;
extern CRagConnection* g_RagConnection;
extern C3dDevice* g_3dDevice;
extern CRenderer* g_Renderer;
extern CFileMgr* g_FileMgr;
extern CTexMgr* g_TexMgr;
extern CUIWindowMgr* g_WindowMgr;
extern CResMgr* g_ResMgr;
extern CMouse* g_Mouse;

extern char TITLE_FILE[256];
extern unsigned short g_serviceType;
extern unsigned short g_serverType;
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
extern char* g_accountAddr;
extern char* g_accountPort;
extern ServerAddress g_charServerAddr;
extern ServerAddress g_zoneServerAddr;
extern bool g_sysQuit;
extern char g_currentMap[16];
extern bool g_bUseCommand;
extern bool g_mustPumpOutReceiveQueue;
extern bool g_NameBalloonShorten;
extern bool g_NameBalloonfontBold;
extern bool g_passwordWrong;
extern std::vector<unsigned long> s_dwAdminAID;

// Used for communication between objects, not a good design
extern CHARACTER_INFO g_charInfo;
extern unsigned char g_selectedCharNum;

#endif  // DOLORI_COMMON_GLOBALS_H_
