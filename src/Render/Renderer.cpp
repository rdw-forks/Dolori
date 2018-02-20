#include "Renderer.h"

#include <math.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include "Common/GetTick.h"
#include "Common/Globals.h"

CRenderer::CRenderer() : m_projection() {}

void CRenderer::SetSize(int cx, int cy) {
  m_width = cx;
  m_height = cy;
  m_halfWidth = cx / 2;
  m_halfHeight = cy / 2;
  m_aspectRatio = cy / static_cast<float>(cx);
  m_hpc = static_cast<float>(cx / 2) / tan(3.141592 * 15.0 * 0.0027777778);
  m_vpc = static_cast<float>(cy / 2) / tan(3.141592 * 15.0 * 0.0027777778);
  m_hratio = tan((90.0 - 15.0 * 0.5) * 3.141592 * 0.0055555557);
  m_xoffset = cx / 2;
  m_yoffset = cy / 2;
  m_vratio = tan((90.0 - 15.0 * 0.5) * 3.141592 * 0.0055555557);
  m_hpc = m_aspectRatio * m_hpc;
  m_hratio = m_aspectRatio * m_hratio;
  m_screenXFactor = cx * 0.0015625;
  m_screenYFactor = cy * 0.0020833334;
  // g_avgPixelRatio = cy * 0.0017447917;
  // g_slope = g_gradient / m_screenYFactor;
  // g_shadowSlope = g_gradient / m_screenYFactor;
  m_nClearColor = 0xFF000000;
  m_projection = glm::perspective(70., 640.0 / 480.0, 1.0, 2000.0);

  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(glm::value_ptr(m_projection));
}

int CRenderer::GetWidth() { return m_width; }

int CRenderer::GetHeight() { return m_height; }

float CRenderer::GetHorizontalRatio() { return m_hratio; }

float CRenderer::GetVerticalRatio() { return m_vratio; }

void CRenderer::SetPixelFormat(PIXEL_FORMAT pf) { m_pf = pf; }

void CRenderer::DestroyAllRPList() {
  m_rpFaceList.clear();
  m_rpLMGroundList.clear();
  m_rpLMLightList.clear();
  m_rpAlphaDepthList.clear();
  m_rpAlphaList.clear();
  m_rpAlphaNoDepthList.clear();
  m_rpEmissiveDepthList.clear();
  m_rpEmissiveNoDepthList.clear();
  // m_rpRawAlphaList.clear();
  // m_rpRawEmissiveList.clear();
  m_rpAlphaOPList.clear();
  // m_rpLmList.clear();
  // m_rpBumpFaceList.clear();
  m_rpQuadFacePoolIter = m_rpQuadFacePool.begin();
}

void CRenderer::Clear(bool clearScreen) {
  if (clearScreen)
    g_3dDevice->Clear(0xFF000000);
  else
    g_3dDevice->ClearZBuffer();
}

void CRenderer::ClearBackground() { g_3dDevice->Clear(m_nClearColor); }

bool CRenderer::DrawScene() {
  /* Flush what needs to be drawn */
  FlushRenderList();
  /* Clear render list */
  DestroyAllRPList();

  return true;
}

void CRenderer::Flip() { g_3dDevice->ShowFrame(); }

void CRenderer::FlushRenderList() {
  FlushFaceList();
  FlushAlphaNoDepthList();
  FlushEmissiveNoDepthList();
  FlushAlphaList();
}

// 0x2 : Emissive
// 0x200 : NO_DEPTH
void CRenderer::AddRP(CRPFace* face, int renderFlags) {
  if (m_isVertexFog) {
  }

  if (renderFlags & 0x1) {
    tlvertex3d v0 = face->GetVertex(0);
    tlvertex3d v1 = face->GetVertex(1);
    float index = (v0.oow - v1.oow) * 0.5 + v1.oow;

    if (renderFlags & 0x4) {
      m_rpAlphaOPList.push_back(face);
    } else if (renderFlags & 0x2) {
      if (renderFlags & 0x100) {
        m_rpEmissiveDepthList.push_back(std::make_pair(index, face));
      } else if (renderFlags & 0x200) {
        m_rpEmissiveNoDepthList.push_back(std::make_pair(index, face));
      } else {
        m_rpEmissiveList.push_back(std::make_pair(index, face));
      }
    } else if (renderFlags & 0x100) {
      m_rpAlphaDepthList.push_back(std::make_pair(index, face));
    } else if (renderFlags & 0x200) {
      m_rpAlphaNoDepthList.push_back(std::make_pair(index, face));
    } else {
      m_rpAlphaList.push_back(std::make_pair(index, face));
    }
  } else if (renderFlags & 0x800) {
    m_rpLMGroundList.push_back(face);
  } else if (renderFlags & 0x10) {
    m_rpLMLightList.push_back(face);
  } else {
    m_rpFaceList.push_back(face);
  }
}

void CRenderer::DrawBoxScreen(int x, int y, int cx, int cy,
                              unsigned int color) {
  if (!(color & 0xFF000000)) {
    return;
  }

  CRPQuadFace* face = g_Renderer->BorrowQuadRP();
  tlvertex3d v[4];

  v[0].x = x;
  v[0].y = y;
  v[0].z = 1e-006;
  v[0].oow = 0.999999f;

  v[1].x = x + cx;
  v[1].y = y;
  v[1].z = 1e-006;
  v[1].oow = 0.999999f;

  v[2].x = x + cx;
  v[2].y = y + cy;
  v[2].z = 1e-006;
  v[2].oow = 0.999999f;

  v[3].x = x;
  v[3].y = y + cy;
  v[3].z = 1e-006;
  v[3].oow = 0.999999f;

  face->SetGeomInfo(0, v[0]);
  face->SetColorInfo(0, color);
  face->SetGeomInfo(1, v[1]);
  face->SetColorInfo(1, color);
  face->SetGeomInfo(2, v[2]);
  face->SetColorInfo(2, color);
  face->SetGeomInfo(3, v[3]);
  face->SetColorInfo(3, color);
  AddRP(face, 0x201);
}

// CTexture* CRenderer::AddSpriteIndex(SPR_IMG* img, uint32_t* pal,
//                                    CACHE_INFO* info) {
//  int id1, id2;
//
//  if (img->width > 128)
//    id1 = 12;
//  else if (img->width > 64)
//    id1 = 8;
//  else if (img->width > 32)
//    id1 = 4;
//  else
//    id1 = 0;
//
//  if (img->height > 128)
//    id2 = 3;
//  else if (img->height > 64)
//    id2 = 2;
//  else if (img->height > 32)
//    id2 = 1;
//  else
//    id2 = 0;
//
//  unsigned int cur_time = GetTick();
//  auto surface_list = m_cache_surfaces[id1 + id2];
//  if (!surface_list.empty()) {
//    for (auto surface_it = surface_list.begin();
//         surface_it != surface_list.end(); ++surface_it) {
//      if (!surface_it->info.empty()) {
//        for (auto info_it = surface_it->info.begin();
//             info_it != surface_it->info.end(); ++info_it) {
//          if (info_it->last_time + 3750 < cur_time) {
//            info_it->id = (size_t)img;
//            info_it->pal_id = (size_t)pal;
//            info_it->tu1 = (info_it->x + img->width) * 0.00390625;
//            info_it->tv1 = (info_it->y + img->height) * 0.00390625;
//            surface_it->tex->UpdateSprite(info_it->x, info_it->y,
//            info_it->tu1,
//                                          info_it->tv1, img, pal);
//            info_it->last_time = cur_time;
//            surface_it->last_time = cur_time;
//            info->tu = info_it->tu;
//            info->tv = info_it->tv;
//            info->tu1 = info_it->tu1;
//            info->tv1 = info_it->tv1;
//
//            return surface_it->tex;
//          }
//        }
//      }
//    }
//  }
//  CACHE_SURFACE new_surface;
//  if (!m_unused_cache_surfaces.empty()) {
//    new_surface.tex = m_unused_cache_surfaces.back();
//    m_unused_cache_surfaces.pop_back();
//  } else {
//    new_surface.tex = new CTexture(256, 256, PF_A8R8G8B8);
//  }
//  new_surface.tex->ClearSurface(NULL, 0);
//  new_surface.tex_width = 256;
//  new_surface.tex_height = 256;
//  //new_surface.info
//
//  for (int y = 0; y < new_surface.tex_height; y++) {
//    for (int x = 0; x < new_surface.tex_width; x++) {
//    }
//  }
//
//  surface_list.push_back(new_surface);
//}

// CTexture* CRenderer::GetSpriteIndex(SPR_IMG* img, uint32_t* pal_id,
//                                    CACHE_INFO* info) {
//  std::list<CACHE_SURFACE>* surface_list = NULL;
//  std::vector<CACHE_INFO>* info_list = NULL;
//  CACHE_SURFACE* cache_surface = NULL;
//  CACHE_INFO* cache_info = NULL;
//  int id1, id2;
//
//  if (img->width > 128)
//    id1 = 12;
//  else if (img->width > 64)
//    id1 = 8;
//  else if (img->width > 32)
//    id1 = 4;
//  else
//    id1 = 0;
//
//  if (img->height > 128)
//    id2 = 3;
//  else if (img->height > 64)
//    id2 = 2;
//  else if (img->height > 32)
//    id2 = 1;
//  else
//    id2 = 0;
//
//  surface_list = &m_cache_surfaces[id1 + id2];
//  for (auto it = surface_list->begin(); it != surface_list->end(); ++it) {
//    if (!it->info.empty()) {
//      info_list = &it->info;
//      cache_surface = &(*it);
//      break;
//    }
//  }
//  if (!info_list) return NULL;
//
//  for (auto it = info_list->begin(); it != info_list->end(); ++it) {
//    if (it->pal_id == (size_t)pal_id && it->id == (size_t)img) {
//      cache_info = &(*it);
//      break;
//    }
//  }
//  if (!cache_info) return NULL;
//
//  unsigned int cur_time = GetTick();
//  cache_info->last_time = cur_time;
//  cache_surface->last_time = cur_time;
//  info->tu = cache_info->tu;
//  info->tv = cache_info->tv;
//  info->tu1 = cache_info->tu1;
//  info->tv1 = cache_info->tv1;
//
//  return cache_surface->tex;
//}

CSurface* CRenderer::AddSpriteIndex(SPR_IMG* img, const uint32_t* pal) {
  std::list<CACHE_SURFACE>* surface_list = nullptr;
  unsigned long cur_time = GetTick();
  int id1, id2;

  if (img->width > 128)
    id1 = 12;
  else if (img->width > 64)
    id1 = 8;
  else if (img->width > 32)
    id1 = 4;
  else
    id1 = 0;

  if (img->height > 128)
    id2 = 3;
  else if (img->height > 64)
    id2 = 2;
  else if (img->height > 32)
    id2 = 1;
  else
    id2 = 0;

  surface_list = &m_cache_surfaces[id1 + id2];
  // Try to find a recyclable surface
  for (auto it = surface_list->begin(); it != surface_list->end(); ++it) {
    if (it->last_time + 3750 < cur_time) {
      it->id = (size_t)img;
      it->pal_id = (size_t)pal;
      it->tex->UpdateSprite(0, 0, img->width, img->height, img, pal);
      it->last_time = GetTick();
      return it->tex;
    }
  }

  CACHE_SURFACE new_surface;
  if (!m_unused_cache_surfaces.empty()) {
    new_surface.tex = m_unused_cache_surfaces.back();
    m_unused_cache_surfaces.pop_back();
  } else
    new_surface.tex = new CSurface(img->width, img->height);

  new_surface.id = (size_t)img;
  new_surface.pal_id = (size_t)pal;
  new_surface.tex->UpdateSprite(0, 0, img->width, img->height, img, pal);
  new_surface.last_time = GetTick();
  surface_list->push_back(new_surface);

  return new_surface.tex;
}

CSurface* CRenderer::GetSpriteIndex(SPR_IMG* img, const uint32_t* pal) {
  std::list<CACHE_SURFACE>* surface_list = nullptr;
  int id1, id2;

  if (img->width > 128)
    id1 = 12;
  else if (img->width > 64)
    id1 = 8;
  else if (img->width > 32)
    id1 = 4;
  else
    id1 = 0;

  if (img->height > 128)
    id2 = 3;
  else if (img->height > 64)
    id2 = 2;
  else if (img->height > 32)
    id2 = 1;
  else
    id2 = 0;

  surface_list = &m_cache_surfaces[id1 + id2];
  for (auto it = surface_list->begin(); it != surface_list->end(); ++it) {
    if (it->id == (size_t)img && it->pal_id == (size_t)pal) {
      it->last_time = GetTick();
      return it->tex;
    }
  }

  return nullptr;
}

// CRenderer::BorrowQuadRP
// Regarde si le QuadListIter fait partie de la liste QuadFace non vide
// Si tel est le cas, on retourne le QuadFace corresepondant
// Sinon on créer un nouveau QuadFace qu'on insère dans la liste des QuadFace
// Puis on retourne le QuadFace nouvellement créé
CRPQuadFace* CRenderer::BorrowQuadRP() {
  if (m_rpQuadFacePoolIter == m_rpQuadFacePool.end()) {
    CRPQuadFace* rp = new CRPQuadFace();
    m_rpQuadFacePool.push_back(rp);
    m_rpQuadFacePoolIter = m_rpQuadFacePool.end();
    return rp;
  } else {
    return *m_rpQuadFacePoolIter++;
  }
}

void CRenderer::SetViewMatrix(const glm::mat4& matrix) {
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixf(glm::value_ptr(matrix));
}

void CRenderer::SetLookAt(const glm::vec3& from, const glm::vec3& at,
                          const glm::vec3& up) {
  gluLookAt(from.x, from.y, from.z, at.x, at.y, at.z, up.x, up.y, up.z);
}

void CRenderer::FlushAlphaNoDepthList() {
  for (const auto& pair : m_rpAlphaNoDepthList) {
    pair.second->Draw();
  }
}

void CRenderer::FlushEmissiveNoDepthList() {
  for (const auto& pair : m_rpEmissiveNoDepthList) {
    pair.second->Draw();
  }
}

void CRenderer::FlushFaceList() {
  for (const auto& rpface : m_rpFaceList) {
    rpface->Draw();
  }
}

void CRenderer::FlushAlphaList() {
  for (const auto& pair : m_rpAlphaList) {
    pair.second->Draw();
  }
}
