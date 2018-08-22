#include "Core/GameClient.h"

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <nlohmann/json.hpp>

#include "Common/ErrorMsg.h"
#include "Common/Globals.h"
#include "Common/debug.h"
#include "Core/ModeMgr.h"
#include "Core/Session.h"
#include "Files/ClientInfo.h"
#include "Files/File.h"
#include "Modes/modetype.h"
#include "Render/3dDevice.h"

GameClient::~GameClient() {
  g_RagConnection->Disconnect();
  CConnection::Cleanup();
  g_ResMgr->Reset();
  g_3dDevice->DestroyRenderer(g_Renderer);
  g_3dDevice->DestroyObjects();
}

bool GameClient::Initialize() {
  if (!g_FileMgr->AddPak("data.grf")) {
    ErrorMsg("Cannot open data.grf.");
    return false;
  }

  ClientInfo client_info("clientinfo.xml");
  if (!client_info.Load()) {
    ErrorMsg("Cannot load clientinfo.xml.");
    return false;
  }

  if (!LoadConfiguration("dolori.json")) {
    ErrorMsg("Cannot load dolori.json");
    return false;
  }

  g_Session->Init();
  if (!g_Session->Create()) {
    ErrorMsg("Cannot create session");
    return false;
  }

  g_ResMgr->ReadResNameTable("resNameTable.txt");

  const uint32_t flags = full_screen_ ? 1 : 0;
  if (g_3dDevice->Init(window_width_, window_height_, flags) < 0) {
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

void GameClient::Run() {
  g_ModeMgr->Run(ModeType::kLogin, "login.rsw");
  // g_ModeMgr->Run(ModeType::kGame, "izlu2dun.rsw");
}

bool GameClient::LoadConfiguration(const std::string& file_name) {
  using json = nlohmann::json;

  json json_config;

  std::ifstream json_file(file_name);
  if (!json_file.is_open()) {
    LOG(error, "Failed to open {}", file_name);
    return false;
  }

  json_file >> json_config;
  json_file.close();

  try {
    auto graphics_config = json_config.at("graphics");
    full_screen_ = graphics_config.value("fullscreen", false);
    window_width_ = graphics_config.value("window_width", 640);
    window_height_ = graphics_config.value("window_height", 480);
  } catch (const std::exception& ex) {
    LOG(error, "Failed to parse {} ({})", file_name, ex.what());
    return false;
  }

  LOG(debug, "Fullscreen: {}", full_screen_);
  LOG(debug, "Resolution: {}x{}", window_width_, window_height_);

  return true;
}
