#include "Globals.h"
#include "service_type.h"

CModeMgr* g_ModeMgr;
CSession* g_Session;
CRagConnection* g_RagConnection;

unsigned short g_serviceType = ServiceKorea;
unsigned int g_version = 3;
char g_clientType = 22;

bool g_passwordEncrypt;
bool g_isGravityID;
unsigned short g_loginStartMode;
char* g_accountAddr;
char* g_accountPort;
ServerAddress g_charServerAddr;
ServerAddress g_zoneServerAddr;
bool g_sysQuit = false;
char g_currentMap[16];
bool g_bUseCommand;
bool g_mustPumpOutReceiveQueue;
bool g_NameBalloonShorten;
bool g_NameBalloonfontBold;
bool g_passwordWrong;
std::vector<unsigned long> s_dwAdminAID;

CHARACTER_INFO g_charInfo;
unsigned char g_selectedCharNum;