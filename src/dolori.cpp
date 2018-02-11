#define _CRT_SECURE_NO_WARNINGS
#define SDL_MAIN_HANDLED
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
    case ServiceKorea:
    case ServiceAmerica:
      g_loginStartMode = 0;
      break;
    case ServiceJapan:
    case ServiceChina:
    case ServiceThai:
      g_loginStartMode = 2;
      break;
    case ServiceTaiwan:
    case ServiceIndonesia:
    case ServiceMalaysia:
    case ServiceSingapore:
    case ServiceBrazil:
    case ServiceRussia:
      g_loginStartMode = 1;
  };
}

void SetOption(tinyxml2::XMLDocument* document) {
  using namespace tinyxml2;

  XMLElement* clientinfo = document->FirstChildElement("clientinfo");
  if (clientinfo) {
    XMLElement* servicetype = clientinfo->FirstChildElement("servicetype");
    if (servicetype) {
      const char* servicetype_str = servicetype->GetText();
      if (!_strcmpi(servicetype_str, "korea"))
        g_serviceType = ServiceKorea;
      else if (!_strcmpi(servicetype_str, "america"))
        g_serviceType = ServiceAmerica;
      else if (!_strcmpi(servicetype_str, "japan"))
        g_serviceType = ServiceJapan;
      else if (!_strcmpi(servicetype_str, "china"))
        g_serviceType = ServiceChina;
      else if (!_strcmpi(servicetype_str, "taiwan"))
        g_serviceType = ServiceTaiwan;
      else if (!_strcmpi(servicetype_str, "thai"))
        g_serviceType = ServiceThai;
      else if (!_strcmpi(servicetype_str, "indonesia"))
        g_serviceType = ServiceIndonesia;
      else if (!_strcmpi(servicetype_str, "philippine"))
        g_serviceType = ServicePhilippine;
      else if (!_strcmpi(servicetype_str, "malaysia"))
        g_serviceType = ServiceMalaysia;
      else if (!_strcmpi(servicetype_str, "singapore"))
        g_serviceType = ServiceSingapore;
      else if (!_strcmpi(servicetype_str, "germany"))
        g_serviceType = ServiceGermany;
      else if (!_strcmpi(servicetype_str, "india"))
        g_serviceType = ServiceIndia;
      else if (!_strcmpi(servicetype_str, "brazil"))
        g_serviceType = ServiceBrazil;
      else if (!_strcmpi(servicetype_str, "autralia"))
        g_serviceType = ServiceAustralia;
      else if (!_strcmpi(servicetype_str, "russia"))
        g_serviceType = ServiceRussia;
      else if (!_strcmpi(servicetype_str, "vietnam"))
        g_serviceType = ServiceVietnam;
      else if (!_strcmpi(servicetype_str, "chile"))
        g_serviceType = ServiceChile;
      else if (!_strcmpi(servicetype_str, "france"))
        g_serviceType = ServiceFrance;
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

int main(int argc, char* argv[]) {
  if (!g_FileMgr->AddPak("data.grf")) {
    ErrorMsg("Cannot open data.grf.");
    return EXIT_FAILURE;
  }
  InitClientInfo("clientinfo.xml");
  g_Session->Init();
  g_Session->Create();
  g_ResMgr->ReadResNameTable("resNameTable.txt");
  if (g_3dDevice->Init(0) < 0) {
    ErrorMsg("Cannot init SDL or OpenGL.");
    return EXIT_FAILURE;
  }
  g_Renderer = g_3dDevice->CreateRenderer(0);
  if (!CConnection::Startup()) return EXIT_FAILURE;

  g_Mouse->Init();
  g_WindowMgr->SetSize(g_Renderer->GetWidth(), g_Renderer->GetHeight());
  g_Session->SetCharName("noname");
  g_WindowMgr->InvalidateUpdateNeededUI();
  g_Session->InvalidateBasicWnd();
  // Let's go
  g_ModeMgr->Run(MT_LOGIN, "login.rsw");
  g_RagConnection->Disconnect();
  CConnection::Cleanup();
  // g_ResMgr->Reset();
  g_3dDevice->DestroyRenderer(g_Renderer);
  g_3dDevice->DestroyObjects();

  return EXIT_SUCCESS;
}
