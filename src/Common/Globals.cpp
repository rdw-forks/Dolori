#include "Common/Globals.h"

CRagConnection* g_RagConnection = new CRagConnection();
CUIWindowMgr* g_WindowMgr = new CUIWindowMgr();
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
unsigned short g_loginStartMode;
char g_accountAddr[64];
char g_accountPort[64];
SERVER_ADDRESS g_charServerAddr;
SERVER_ADDRESS g_zoneServerAddr;
bool g_sys_quit = false;
char g_current_map[16];
bool g_bUseCommand;
bool g_mustPumpOutReceiveQueue;
bool g_NameBalloonShorten;
bool g_NameBalloonfontBold;
bool g_passwordWrong;
std::vector<unsigned long> s_dwAdminAID;

CHARACTER_INFO g_charInfo;
uint8_t g_selected_char_num;
