#ifndef DOLORI_COMMON_GLOBALS_H_
#define DOLORI_COMMON_GLOBALS_H_

#include <vector>
#include "../Common/character_info.h"
#include "../Core/ModeMgr.h"
#include "../Core/Session.h"
#include "../Network/RagConnection.h"

extern CModeMgr* g_ModeMgr;
extern CSession* g_Session;
extern CRagConnection* g_RagConnection;

extern unsigned short g_serviceType;
extern unsigned int g_version;
extern char g_clientType;
extern bool g_passwordEncrypt;
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
