#include "World.h"
#include "../Common/ErrorMsg.h"
#include "../Common/Globals.h"
#include "3dWorldRes.h"
#include "GndRes.h"

CWorld::CWorld() {
  m_calculated = NULL;
  m_bgObjThread = 0;
  m_ground = NULL;
  // m_player = NULL;
  m_isPKZone = false;
  m_isSiegeMode = false;
  m_isBattleFieldMode = false;
  m_isEventPVPMode = false;
}

CWorld::~CWorld() {}

void CWorld::OnEnterFrame() {
  vec3 light_dir, diffuse_color, ambient_color;
  const char* rsw_filename;
  C3dWorldRes* rsw_res;
  CGndRes* gnd_res;

  rsw_filename =
      (const char*)g_ModeMgr->GetCurMode()->SendMsg(MM_QUERYRSWNAME, 0, 0, 0);
  rsw_res = (C3dWorldRes*)g_ResMgr->Get(rsw_filename, false);
  if (!rsw_res) {
    std::string error = "Cannot load file ";
    ErrorMsg((error + rsw_filename).c_str());
    return;
  }
  // g_ResMgr->Get(res->GetAttr(), false);
  gnd_res = (CGndRes*)g_ResMgr->Get(rsw_res->GetGnd(), false);
  m_ground = new C3dGround();
  m_ground->AssignGnd(gnd_res, &light_dir, &diffuse_color, &ambient_color);
  // g_ResMgr->Unload(gnd_res);
}
