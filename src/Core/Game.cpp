#define _CRT_SECURE_NO_WARNINGS
#define SDL_MAIN_HANDLED

#include "Game.h"
#include <SDL.h>
#include <tinyxml2.h>
#include "Common/ErrorMsg.h"
#include "Common/Globals.h"
#include "Common/modetype.h"
#include "Common/server_type.h"
#include "Common/service_type.h"
#include "Core/ModeMgr.h"
#include "Core/Session.h"
#include "Files/File.h"
#include "Render/3dDevice.h"
#ifndef WIN32
#include <strings.h>
#define _strcmpi strcasecmp
#endif

void SetLoginStartMode() {
  switch (g_serviceType) {
    case ServiceType::Korea:
    case ServiceType::America:
      g_loginStartMode = 0;
      break;
    case ServiceType::Japan:
    case ServiceType::China:
    case ServiceType::Thai:
      g_loginStartMode = 2;
      break;
    case ServiceType::Taiwan:
    case ServiceType::Indonesia:
    case ServiceType::Malaysia:
    case ServiceType::Singapore:
    case ServiceType::Brazil:
    case ServiceType::Russia:
      g_loginStartMode = 1;
  };
}

void SetOption(tinyxml2::XMLDocument* document) {
  using namespace tinyxml2;

  XMLElement* clientinfo = document->FirstChildElement("clientinfo");
  if (!clientinfo) return;

  XMLElement* servicetype = clientinfo->FirstChildElement("servicetype");
  if (servicetype) {
    const char* servicetype_str = servicetype->GetText();
    if (!_strcmpi(servicetype_str, "korea"))
      g_serviceType = ServiceType::Korea;
    else if (!_strcmpi(servicetype_str, "america"))
      g_serviceType = ServiceType::America;
    else if (!_strcmpi(servicetype_str, "japan"))
      g_serviceType = ServiceType::Japan;
    else if (!_strcmpi(servicetype_str, "china"))
      g_serviceType = ServiceType::China;
    else if (!_strcmpi(servicetype_str, "taiwan"))
      g_serviceType = ServiceType::Taiwan;
    else if (!_strcmpi(servicetype_str, "thai"))
      g_serviceType = ServiceType::Thai;
    else if (!_strcmpi(servicetype_str, "indonesia"))
      g_serviceType = ServiceType::Indonesia;
    else if (!_strcmpi(servicetype_str, "philippine"))
      g_serviceType = ServiceType::Philippine;
    else if (!_strcmpi(servicetype_str, "malaysia"))
      g_serviceType = ServiceType::Malaysia;
    else if (!_strcmpi(servicetype_str, "singapore"))
      g_serviceType = ServiceType::Singapore;
    else if (!_strcmpi(servicetype_str, "germany"))
      g_serviceType = ServiceType::Germany;
    else if (!_strcmpi(servicetype_str, "india"))
      g_serviceType = ServiceType::India;
    else if (!_strcmpi(servicetype_str, "brazil"))
      g_serviceType = ServiceType::Brazil;
    else if (!_strcmpi(servicetype_str, "autralia"))
      g_serviceType = ServiceType::Australia;
    else if (!_strcmpi(servicetype_str, "russia"))
      g_serviceType = ServiceType::Russia;
    else if (!_strcmpi(servicetype_str, "vietnam"))
      g_serviceType = ServiceType::Vietnam;
    else if (!_strcmpi(servicetype_str, "chile"))
      g_serviceType = ServiceType::Chile;
    else if (!_strcmpi(servicetype_str, "france"))
      g_serviceType = ServiceType::France;
    else
      ErrorMsg("No ServiceType !");
    SetLoginStartMode();
  }

  XMLElement* servertype = clientinfo->FirstChildElement("servertype");
  if (servertype) {
    const char* servertype_str = servertype->GetText();
    if (!_strcmpi(servertype_str, "primary"))
      g_serverType = ServerPrimary;
    else if (!_strcmpi(servertype_str, "sakray"))
      g_serverType = ServerSakray;
    else if (!_strcmpi(servertype_str, "local"))
      g_serverType = ServerLocal;
    else if (!_strcmpi(servertype_str, "pk"))
      g_serverType = ServerPK;
    else
      ErrorMsg("No ServerType !");
  }

  if (clientinfo->FirstChildElement("hideaccountlist"))
    g_hideAccountList = true;
  if (clientinfo->FirstChildElement("passwordencrypt"))
    g_passwordEncrypt = true;
  if (clientinfo->FirstChildElement("passwordencrypt2")) {
    g_passwordEncrypt = true;
    g_passwordEncrypt2 = true;
  }
  if (clientinfo->FirstChildElement("extendedslot")) g_extendedSlot = true;
  if (clientinfo->FirstChildElement("readfolder")) g_readFolderFirst = true;

  // Loading screens
  XMLElement* loading = clientinfo->FirstChildElement("loading");
  if (loading) {
    for (XMLElement* e = loading->FirstChildElement("image"); e != NULL;
         e = e->NextSiblingElement("image")) {
      std::string name = e->GetText();
      s_loadingScreenList.push_back(name);
    }
  }

  // TODO: Iterate through connections
  XMLElement* connection = clientinfo->FirstChildElement("connection");
  if (connection) {
    XMLElement* address = connection->FirstChildElement("address");
    if (address)
      strncpy(g_accountAddr, address->GetText(), sizeof(g_accountAddr));

    XMLElement* port = connection->FirstChildElement("port");
    if (port) strncpy(g_accountPort, port->GetText(), sizeof(g_accountPort));
  }
}

void InitClientInfo(const char* filename) {
  using namespace tinyxml2;
  CFile fp;

  if (fp.Open(filename, 0)) {
    tinyxml2::XMLDocument document;
    if (document.Parse((char*)fp.GetBuf(), fp.GetLength()) == XML_SUCCESS) {
      SetOption(&document);
    }
    fp.Close();
  }
}

Game::~Game() {
  g_RagConnection->Disconnect();
  CConnection::Cleanup();
  // g_ResMgr->Reset();
  g_3dDevice->DestroyRenderer(g_Renderer);
  g_3dDevice->DestroyObjects();
}

bool Game::Initialize() {
  if (!g_FileMgr->AddPak("data.grf")) {
    ErrorMsg("Cannot open data.grf.");
    return false;
  }
  InitClientInfo("clientinfo.xml");
  g_Session->Init();
  g_Session->Create();
  g_ResMgr->ReadResNameTable("resNameTable.txt");
  if (g_3dDevice->Init(0) < 0) {
    ErrorMsg("Cannot init SDL or OpenGL.");
    return false;
  }
  g_Renderer = g_3dDevice->CreateRenderer(0);
  if (!CConnection::Startup()) {
    return false;
  }

  g_Mouse->Init();
  g_WindowMgr->SetSize(g_Renderer->GetWidth(), g_Renderer->GetHeight());
  g_Session->SetCharName("noname");
  g_WindowMgr->InvalidateUpdateNeededUI();
  g_Session->InvalidateBasicWnd();

  return true;
}

void Game::Run() { g_ModeMgr->Run(MT_LOGIN, "login.rsw"); }
