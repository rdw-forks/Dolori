#include "Render/World.h"

#include "Common/ErrorMsg.h"
#include "Common/Globals.h"
#include "Common/debug.h"
#include "Render/3dWorldRes.h"
#include "Render/GndRes.h"

CWorld::CWorld()
    : m_calculated(),
      m_bgObjThread(),
      m_ground(),
      m_player(),
      m_attr(),
      m_isPKZone(false),
      m_isSiegeMode(false),
      m_isBattleFieldMode(false),
      m_isEventPVPMode(false) {}

CWorld::~CWorld() {}

void CWorld::OnEnterFrame() {
  glm::vec3 light_dir, diffuse_color, ambient_color;
  const char* rsw_filename;
  C3dWorldRes* rsw_res;
  CGndRes* gnd_res;

  if (!m_ground.Init()) {
    LOG(error, "Failed to initialize ground resource");
    return;
  }

  rsw_filename = static_cast<const char*>(
      g_ModeMgr->GetCurMode()->SendMsg(MM_QUERYRSWNAME));
  rsw_res = static_cast<C3dWorldRes*>(g_ResMgr->Get(rsw_filename, false));
  if (!rsw_res) {
    std::string error = "Cannot load file ";
    ErrorMsg((error + rsw_filename).c_str());
    return;
  }
  // g_ResMgr->Get(res->GetAttr(), false);
  gnd_res = static_cast<CGndRes*>(g_ResMgr->Get(rsw_res->GetGnd(), false));
  m_ground.AssignGnd(gnd_res, &light_dir, &diffuse_color, &ambient_color);
  // g_ResMgr->Unload(gnd_res);
}

void CWorld::Render() {
  RECT_ test;
  m_ground.Render(nullptr, &test, false);
}

const CPlayer& CWorld::GetPlayer() const { return m_player; }
