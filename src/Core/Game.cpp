#define _CRT_SECURE_NO_WARNINGS
#define SDL_MAIN_HANDLED

#include "Core/Game.h"

#include <SDL.h>
#ifndef WIN32
#include <strings.h>
#define _strcmpi strcasecmp
#endif
#include "Common/ErrorMsg.h"
#include "Common/Globals.h"
#include "Core/ModeMgr.h"
#include "Core/Session.h"
#include "Files/ClientInfo.h"
#include "Files/File.h"
#include "Modes/modetype.h"
#include "Render/3dDevice.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

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

  ClientInfo client_info("clientinfo.xml");
  if (!client_info.Load()) {
    ErrorMsg("Cannot load clientinfo.xml.");
    return false;
  }

  g_Session->Init();
  if (!g_Session->Create()) {
    ErrorMsg("Cannot create session");
    return false;
  }

  g_ResMgr->ReadResNameTable("resNameTable.txt");
  if (g_3dDevice->Init(SCREEN_WIDTH, SCREEN_HEIGHT, 0) < 0) {
    ErrorMsg("Cannot init SDL or OpenGL.");
    return false;
  }

  g_Renderer = g_3dDevice->CreateRenderer(0);
  if (g_Renderer == nullptr) {
    return false;
  }

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

void Game::Run() {
  // g_ModeMgr->Run(ModeType::kLogin, "login.rsw");
  g_ModeMgr->Run(ModeType::kGame, "aldebaran.rsw");
}
