#include "Render/Renderer.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>

#include "Common/GetTick.h"
#include "Common/Globals.h"
#include "Common/debug.h"

const std::string kSurfaceVertexShader =
    "#version 140\n"

    "attribute vec2 aPosition;"
    "attribute vec2 aTextureCoord;"

    "uniform mat4 uProjectionMat;"

    "varying vec2 vTextureCoord;"

    "void main() {"
    "  gl_Position = uProjectionMat * vec4(aPosition, 0.0, 1.0);"
    "  vTextureCoord = aTextureCoord;"
    "}";

const std::string kSurfaceFragmentShader =
    "#version 140\n"

    "varying vec2 vTextureCoord;"

    "uniform sampler2D uTexture;"

    "void main() {"
    "  gl_FragColor = texture2D(uTexture,vTextureCoord.st);"
    "}";

struct SurfaceVertex {
  float position[2];
  float texture_coord[2];
};

CRenderer::CRenderer()
    : m_view_matrix(),
      m_surface_program(),
      m_surface_vbo(),
      m_surfaces_list(),
      m_fpsFrameCount() {}

bool CRenderer::Init() {
  CGlShader vertex_shader;
  CGlShader fragment_shader;

  // Setup the VBO to store GndVertex objects
  m_surface_vbo.SetVertexFormat<SurfaceVertex>();

  if (!vertex_shader.Init(kSurfaceVertexShader, GL_VERTEX_SHADER)) {
    return false;
  }

  if (!fragment_shader.Init(kSurfaceFragmentShader, GL_FRAGMENT_SHADER)) {
    return false;
  }

  return m_surface_program.Init({vertex_shader, fragment_shader});
}

void CRenderer::SetSize(int cx, int cy) {
  m_width = cx;
  m_height = cy;
  m_halfWidth = cx / 2;
  m_halfHeight = cy / 2;
  m_aspectRatio = cy / static_cast<float>(cx);
  m_hpc = static_cast<float>(cx / 2) / glm::tan(3.141592 * 15.0 * 0.0027777778);
  m_vpc = static_cast<float>(cy / 2) / glm::tan(3.141592 * 15.0 * 0.0027777778);
  m_hratio = glm::tan((90.0 - 15.0 * 0.5) * 3.141592 * 0.0055555557);
  m_xoffset = cx / 2;
  m_yoffset = cy / 2;
  m_vratio = glm::tan((90.0 - 15.0 * 0.5) * 3.141592 * 0.0055555557);
  m_hpc = m_aspectRatio * m_hpc;
  m_hratio = m_aspectRatio * m_hratio;
  m_screenXFactor = cx * 0.0015625;
  m_screenYFactor = cy * 0.0020833334;
  // g_avgPixelRatio = cy * 0.0017447917;
  // g_slope = g_gradient / m_screenYFactor;
  // g_shadowSlope = g_gradient / m_screenYFactor;
  m_nClearColor = 0xFF000000;
  m_projection_matrix =
      glm::perspective(70.f, cx / static_cast<float>(cy), 1.f, 2000.f);
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
  m_surfaces_list.clear();
}

void CRenderer::Clear(bool clearScreen) {
  if (clearScreen) {
    g_3dDevice->Clear(0xFF000000);
  } else {
    g_3dDevice->ClearZBuffer();
  }
}

void CRenderer::ClearBackground() { g_3dDevice->Clear(m_nClearColor); }

bool CRenderer::DrawScene() {
  /* Flush what needs to be drawn */
  FlushRenderList();
  /* Clear render list */
  DestroyAllRPList();

  return true;
}

void CRenderer::Flip() {
  g_3dDevice->ShowFrame();
  m_fpsFrameCount++;
  auto current_ticks = SDL_GetTicks();
  if (current_ticks > m_fpsStartTick + 1000) {
    // LOG(debug, "FPS: {}", m_fpsFrameCount);
    m_fpsFrameCount = 0;
    m_fpsStartTick = SDL_GetTicks();
  }
}

void CRenderer::FlushRenderList() {
  FlushFaceList();
  FlushAlphaNoDepthList();
  FlushEmissiveNoDepthList();
  FlushAlphaList();

  // Render 2D surfaces
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  FlushSurfacesList();

  glDisable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
}

void CRenderer::AddSurface(CSurface* surface, const RECT& position) {
  m_surfaces_list.push_back(std::make_pair(surface, position));
}

// 0x2 : Emissive
// 0x200 : NO_DEPTH
void CRenderer::AddRP(CRPFace* face, int renderFlags) {
  if (m_isVertexFog) {
  }

  if (renderFlags & 0x1) {
    float v0 = face->GetWCoord(0);
    float v1 = face->GetWCoord(1);
    float index = (v0 - v1) * 0.5 + v1;

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

  // TODO: Render unicolor surface
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

  if (img->width > 128) {
    id1 = 12;
  } else if (img->width > 64) {
    id1 = 8;
  } else if (img->width > 32) {
    id1 = 4;
  } else {
    id1 = 0;
  }

  if (img->height > 128) {
    id2 = 3;
  } else if (img->height > 64) {
    id2 = 2;
  } else if (img->height > 32) {
    id2 = 1;
  } else {
    id2 = 0;
  }

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
  } else {
    new_surface.tex = new CSurface(img->width, img->height);
  }

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

  if (img->width > 128) {
    id1 = 12;
  } else if (img->width > 64) {
    id1 = 8;
  } else if (img->width > 32) {
    id1 = 4;
  } else {
    id1 = 0;
  }

  if (img->height > 128) {
    id2 = 3;
  } else if (img->height > 64) {
    id2 = 2;
  } else if (img->height > 32) {
    id2 = 1;
  } else {
    id2 = 0;
  }

  surface_list = &m_cache_surfaces[id1 + id2];
  for (auto it = surface_list->begin(); it != surface_list->end(); ++it) {
    if (it->id == (size_t)img && it->pal_id == (size_t)pal) {
      it->last_time = GetTick();
      return it->tex;
    }
  }

  return nullptr;
}

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

const glm::mat4& CRenderer::projection_matrix() const {
  return m_projection_matrix;
}

const glm::mat4& CRenderer::view_matrix() const { return m_view_matrix; }

void CRenderer::SetViewMatrix(const glm::mat4& matrix) {
  m_view_matrix = matrix;
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

void CRenderer::FlushSurfacesList() {
  const auto projection_matrix =
      glm::ortho<float>(0.f, m_width, m_height, 0.f, -1.f, 1.f);

  m_surface_program.Bind();

  const GLuint position_attrib =
      m_surface_program.GetAttributeLocation("aPosition");
  const GLuint tex_coord_attrib =
      m_surface_program.GetAttributeLocation("aTextureCoord");
  glEnableVertexAttribArray(position_attrib);
  glEnableVertexAttribArray(tex_coord_attrib);

  glVertexAttribPointer(position_attrib, 2, GL_FLOAT, GL_FALSE, 4 * 4, 0);
  glVertexAttribPointer(tex_coord_attrib, 2, GL_FLOAT, GL_FALSE, 4 * 4,
                        reinterpret_cast<void*>(2 * 4));

  GLuint uniform_id = m_surface_program.GetUniformLocation("uProjectionMat");
  glUniformMatrix4fv(uniform_id, 1, GL_FALSE,
                     glm::value_ptr(projection_matrix));

  uniform_id = m_surface_program.GetUniformLocation("uTexture");
  glUniform1i(uniform_id, 0);

  glActiveTexture(GL_TEXTURE0);

  for (const auto& pair : m_surfaces_list) {
    const auto surface = pair.first;
    const auto position = pair.second;

    const SurfaceVertex vertices[6] = {
        {position.left + position.right, position.top + position.bottom, 1.f,
         1.f},
        {position.left + position.right, position.top, 1.f, 0.f},
        {position.left, position.top, 0.f, 0.f},
        {position.left, position.top, 0.f, 0.f},
        {position.left, position.top + position.bottom, 0.f, 1.f},
        {position.left + position.right, position.top + position.bottom, 1.f,
         1.f}};

    m_surface_vbo.SetData(vertices, 6);
    m_surface_vbo.Bind();

    surface->Bind(GL_TEXTURE_2D);

    glDrawArrays(GL_TRIANGLES, 0, m_surface_vbo.size());
  }

  m_surface_program.Unbind();
}
