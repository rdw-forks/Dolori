#define _CRT_SECURE_NO_WARNINGS
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "Common/Globals.h"
#include "Common/modetype.h"
#include "Common/service_type.h"
#include "Core/ModeMgr.h"
#include "Core/Session.h"
#include "Files/File.h"
#include "Files/tinyxml2/tinyxml2.h"
#include "Render/3dDevice.h"

void InitClientInfo(const char* filename) {
  CFile* fp = new CFile();

  if (fp->Open(filename, 0)) {
    tinyxml2::XMLDocument client_info;

    client_info.Parse((char*)fp->GetBuf(), fp->GetLength());
    fp->Close();
  }
  if (g_serviceType != ServiceKorea) {
    strncpy(TITLE_FILE, "+�+�+++-�S+�+�\bgi_temp.bmp", sizeof(TITLE_FILE));
  }
}

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

int GameMain() {
  if (g_serviceType != ServiceKorea) g_FileMgr->AddPak("data.grf");

  InitClientInfo("clientinfo.xml");

  g_Session->Init();
  g_Session->Create();
  g_ResMgr->ReadResNameTable("resNameTable.txt");
  if (g_3dDevice->Init(0) < 0) {
    return EXIT_FAILURE;
  }
  g_Renderer = g_3dDevice->CreateRenderer(0);

  if (!CConnection::Startup()) return EXIT_FAILURE;

  g_WindowMgr->SetSize(g_Renderer->GetWidth(), g_Renderer->GetHeight());
  SetLoginStartMode();
  g_Session->SetCharName("noname");
  g_ModeMgr->Run(MT_LOGIN, "login.rsw");

  g_RagConnection->Disconnect();
  CConnection::Cleanup();
  g_3dDevice->DestroyRenderer(g_Renderer);
  g_3dDevice->DestroyObjects();

  return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) { return GameMain(); }
