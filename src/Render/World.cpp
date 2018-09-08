#include "Render/World.h"

#include "Common/ErrorMsg.h"
#include "Common/Globals.h"
#include "Common/debug.h"
#include "Files/GndRes.h"
#include "Files/RsmRes.h"
#include "Files/RswRes.h"

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

  if (!m_ground.Init()) {
    LOG(error, "Failed to initialize ground renderer");
    return;
  }

  // Load RSW file
  const auto rsw_filename = static_cast<const char*>(
      g_ModeMgr->GetCurMode()->SendMsg(MM_QUERYRSWNAME));
  auto rsw_res = static_cast<CRswRes*>(g_ResMgr->Get(rsw_filename, false));
  if (rsw_res == nullptr) {
    LOG(error, "Cannot get resource: {}", rsw_filename);
    return;
  }

  m_diffuse_col = rsw_res->GetDiffuseColor();
  m_ambient_col = rsw_res->GetAmbientColor();
  m_light_opacity = rsw_res->GetLightOpacity();
  const auto light_longitude = rsw_res->GetLightLongitude();
  const auto light_latitude = rsw_res->GetLightLatitude();
  m_light_dir.x = -glm::cos(glm::radians((float)light_longitude)) *
                  glm::sin(glm::radians((float)light_latitude));
  m_light_dir.y = glm::cos(glm::radians((float)light_latitude));
  m_light_dir.z = glm::sin(glm::radians((float)light_longitude)) *
                  glm::sin(glm::radians((float)light_latitude));
  g_Renderer->SetLightInfo(
      {m_light_dir, m_diffuse_col, m_ambient_col, m_light_opacity});

  // Load GND file
  const auto gnd_filename = rsw_res->GetGnd();
  auto gnd_res = static_cast<CGndRes*>(g_ResMgr->Get(gnd_filename, false));
  if (gnd_res == nullptr) {
    LOG(error, "Cannot get resource: {}", gnd_filename);
    return;
  }

  m_ground.AssignGnd(gnd_res, &light_dir, &diffuse_color, &ambient_color);

  // Unload unneeded resources
  g_ResMgr->Unload(gnd_res);

  // Load GAT file
  //  const auto gat_filename = rsw_res->GetAttr();
  //  auto gat_res = static_cast<C3dAttr*>(g_ResMgr->Get(gat_filename, false));
  //  if (gat_res == nullptr) {
  //    LOG(error, "Failed to load resource: {}", gat_filename);
  //    return;
  //  }

  // Load RSM files
  for (const auto& model_info : rsw_res->GetModels()) {
    const auto rsm_filename = model_info->model_name;
    auto rsm_res = static_cast<CRsmRes*>(g_ResMgr->Get(rsm_filename, false));
    if (rsm_res == nullptr) {
      LOG(error, "Cannot get resource: {}", rsm_filename);
      return;
    }

    auto actor = std::make_unique<C3dActor>();
    actor->AssignModel(rsm_res);
    actor->SetPos(glm::vec3(model_info->position[0], model_info->position[1],
                            model_info->position[2]));
    actor->SetRot(glm::vec3(model_info->rotation[0], model_info->rotation[1],
                            model_info->rotation[2]));
    actor->SetScale(glm::vec3(model_info->scale[0], model_info->scale[1],
                              model_info->scale[2]));
    m_bg_obj_list.push_back(std::move(actor));
  }

  g_ResMgr->Unload(rsw_res);
}

void CWorld::Render() {
  RECT test;
  m_ground.Render(nullptr, &test, false);

  // Render 3D map models
  for (auto& actor : m_bg_obj_list) {
    actor->Render();
  }
}

const CPlayer& CWorld::GetPlayer() const { return m_player; }
