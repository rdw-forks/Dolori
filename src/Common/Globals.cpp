#include "Globals.h"
#include "service_type.h"

CRagConnection* g_RagConnection = new CRagConnection();
CUIWindowMgr* g_WindowMgr = new CUIWindowMgr();
C3dDevice* g_3dDevice = new C3dDevice();
CModeMgr* g_ModeMgr = new CModeMgr();
CSession* g_Session = new CSession();
CFileMgr* g_FileMgr = new CFileMgr();
CTexMgr* g_TexMgr = new CTexMgr();
CResMgr* g_ResMgr = new CResMgr();
CRenderer* g_Renderer;

char TITLE_FILE[256];
unsigned short g_serviceType = ServiceAmerica;
unsigned int g_version = 3;
char g_clientType = 22;
bool g_passwordEncrypt;
bool g_readFolderFirst = true;
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
