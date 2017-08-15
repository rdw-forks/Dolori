#include <iostream>
#include "Common/Globals.h"
#include "Common/service_type.h"
#include "Core/ModeMgr.h"
#include "Core/Session.h"

int GameMain() {
  g_Session = new CSession();
  g_ModeMgr = new CModeMgr();

  g_Session->Init();
  g_Session->Create();

  if (!CConnection::Startup()) return EXIT_FAILURE;

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
  g_Session->SetCharName("|");
  g_ModeMgr->Run(1, "World_HP.rsw");
  g_RagConnection->Disconnect();
  CConnection::Cleanup();

  return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
  return GameMain();
}
