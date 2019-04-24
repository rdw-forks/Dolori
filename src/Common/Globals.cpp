#include "Common/Globals.h"

C3dDevice* g_3dDevice = new C3dDevice();
CModeMgr* g_ModeMgr = new CModeMgr();
CSession* g_Session = new CSession();
CFileMgr* g_FileMgr = new CFileMgr();
CTexMgr* g_TexMgr = new CTexMgr();
CResMgr* g_ResMgr = new CResMgr();
CFontMgr* g_FontMgr = new CFontMgr();
CMouse* g_Mouse = new CMouse();
CRenderer* g_Renderer;
CMsgStrMgr* g_MsgStrMgr = new CMsgStrMgr();
CLanguage* g_Language = new CLanguage();

char TITLE_FILE[256];
ServiceType g_serviceType;
ServerType g_serverType;
unsigned int g_version = 23;
char g_clientType = 23;
bool g_hideAccountList;
bool g_passwordEncrypt;
bool g_passwordEncrypt2;
bool g_readFolderFirst = true;
bool g_extendedSlot;
std::vector<std::string> s_loadingScreenList;
bool g_isGravityID;
uint16_t g_loginStartMode;
char g_accountAddr[64];
char g_accountPort[64];
ServerAddress g_charServerAddr;
ServerAddress g_zoneServerAddr;
bool g_sys_quit = false;
bool g_bUseCommand;
bool g_mustPumpOutReceiveQueue;
bool g_NameBalloonShorten;
bool g_NameBalloonfontBold;
bool g_passwordWrong;
std::vector<uint32_t> s_dwAdminAID;
