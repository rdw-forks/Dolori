#include "Render/Renderer.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>

#include "Common/GetTick.h"
#include "Common/Globals.h"
#include "Common/debug.h"

const std::string kSurfaceVertexShader =
    R"(#version 140

    attribute vec2 aPosition;
    attribute vec2 aTextureCoord;

    uniform mat4 uProjectionMat;

    varying vec2 vTextureCoord;

    void main() {
      gl_Position = uProjectionMat * vec4(aPosition, 0.0, 1.0);
      vTextureCoord = aTextureCoord;
    })";

const std::string kSurfaceFragmentShader =
    R"(#version 140

    varying vec2 vTextureCoord;

    uniform sampler2D uTexture;

    void main() {
      gl_FragColor = texture2D(uTexture,vTextureCoord.st);
    })";

const std::string kWorldVertexShader =
    R"(#version 140

    attribute vec3 aPosition;
    attribute vec2 aTextureCoord;
    attribute vec3 aNormal;

    uniform mat4 uModelViewMat;
    uniform mat4 uNodeViewMat;
    uniform mat4 uViewMat;
    uniform mat4 uProjectionMat;
    uniform vec3 uLightDirection;

    varying vec2 vTextureCoord;
    varying vec3 normal;
    varying float vLightWeighting;

    void main() {
      mat4 modelViewMat = uModelViewMat * uNodeViewMat;
      gl_Position = uProjectionMat * uViewMat * modelViewMat * vec4(aPosition, 1.0);

      mat3 normalMatrix = transpose(inverse(mat3(modelViewMat)));
	  normal = normalize(normalMatrix * aNormal);

   
      float dotLight = dot(normal, uLightDirection);
      vLightWeighting = clamp(dotLight, 0.0, 1.0);
      vTextureCoord = aTextureCoord;
    })";

const std::string kWorldFragmentShader =
    R"(#version 140

    varying vec2 vTextureCoord;

    uniform sampler2D uTexture;
    uniform vec3 uLightDiffuse;
    uniform vec3 uLightAmbient;
    uniform float uLightIntensity;

    varying vec3 normal;
    varying float vLightWeighting;

    void main() {
      vec4 color = texture2D(uTexture, vTextureCoord);
      if(color.a == 0.0) {
        discard;
      }

      color.rgb *= uLightIntensity * vLightWeighting * uLightDiffuse + uLightAmbient;
      gl_FragColor = color;
    })";

CRenderer::CRenderer()
    : m_projection_matrix(),
      m_view_matrix(),
      m_surface_program(),
      m_surface_vbo(),
      m_world_light_info(),
      m_hpc(),
      m_vpc(),
      m_hratio(),
      m_vratio(),
      m_aspectRatio(),
      m_screenXFactor(),
      m_screenYFactor(),
      m_xoffset(),
      m_yoffset(),
      m_width(),
      m_height(),
      m_halfWidth(),
      m_halfHeight(),
      m_curFrame(),
      m_bRGBBitCount(),
      m_fpsFrameCount(),
      m_fpsStartTick(),
      m_isFoggy(),
      m_fogChanged(),
      m_isVertexFog(),
      m_oldTexture(),
      m_oldLmapTexture(),
      m_guardBandLeft(),
      m_guardBandRight(),
      m_guardBandTop(),
      m_guardBandBottom(),
      m_isShowInfo(),
      m_eyeVector(),
      m_nClearColor(),
      m_dwScreenWidth(),
      m_dwScreenHeight(),
      m_pf(),
      m_lpSurfacePtr(),
      m_lPitch(),
      m_surfaces_list(),
      m_render_blocks_pool(),
      m_world_render_list() {
  m_render_blocks_cursor = std::begin(m_render_blocks_pool);
}

bool CRenderer::Init() {
  CGlShader surface_vertex_shader;
  CGlShader surface_fragment_shader;

  // Setup the VBO to store GndVertex objects
  m_surface_vbo.SetVertexFormat<VertexP2T2>();

  if (!surface_vertex_shader.Init(kSurfaceVertexShader, GL_VERTEX_SHADER)) {
    return false;
  }

  if (!surface_fragment_shader.Init(kSurfaceFragmentShader,
                                    GL_FRAGMENT_SHADER)) {
    return false;
  }

  if (!m_surface_program.Init(
          {surface_vertex_shader, surface_fragment_shader})) {
    return false;
  }

  CGlShader world_vertex_shader;
  CGlShader world_fragment_shader;

  if (!world_vertex_shader.Init(kWorldVertexShader, GL_VERTEX_SHADER)) {
    return false;
  }

  if (!world_fragment_shader.Init(kWorldFragmentShader, GL_FRAGMENT_SHADER)) {
    return false;
  }

  if (!m_world_program.Init({world_vertex_shader, world_fragment_shader})) {
    return false;
  }

  return true;
}

void CRenderer::SetSize(int cx, int cy) {
  m_width = cx;
  m_height = cy;
  m_halfWidth = cx / 2;
  m_halfHeight = cy / 2;
  m_aspectRatio = cy / static_cast<float>(cx);
  m_hpc = (static_cast<float>(cx) / 2.f) /
          glm::tan(3.141592f * 15.f * 0.0027777778f);
  m_vpc = (static_cast<float>(cy) / 2.f) /
          glm::tan(3.141592f * 15.f * 0.0027777778f);
  m_hratio = glm::tan((90.f - 15.f * 0.5) * 3.141592f * 0.0055555557f);
  m_xoffset = cx / 2.f;
  m_yoffset = cy / 2.f;
  m_vratio = glm::tan((90.f - 15.f * 0.5f) * 3.141592f * 0.0055555557f);
  m_hpc = m_aspectRatio * m_hpc;
  m_hratio = m_aspectRatio * m_hratio;
  m_screenXFactor = cx * 0.0015625f;
  m_screenYFactor = cy * 0.0020833334f;
  // g_avgPixelRatio = cy * 0.0017447917;
  // g_slope = g_gradient / m_screenYFactor;
  // g_shadowSlope = g_gradient / m_screenYFactor;
  m_nClearColor = 0xFF000000;
  m_projection_matrix = glm::perspective(
      70.f, m_width / static_cast<float>(m_height), 1.f, 2000.f);
  m_2d_projection_matrix =
      glm::ortho(0.f, static_cast<float>(m_width), static_cast<float>(m_height),
                 0.f, -1.f, 1.f);
}

int CRenderer::GetWidth() const { return m_width; }

int CRenderer::GetHeight() const { return m_height; }

float CRenderer::GetHorizontalRatio() const { return m_hratio; }

float CRenderer::GetVerticalRatio() const { return m_vratio; }

void CRenderer::SetPixelFormat(PIXEL_FORMAT pf) { m_pf = pf; }

void CRenderer::DestroyAllRPList() {
  m_surfaces_list.clear();
  m_world_render_list.clear();

  m_render_blocks_cursor = std::begin(m_render_blocks_pool);
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
    LOG(debug, "FPS: {}", m_fpsFrameCount);
    m_fpsFrameCount = 0;
    m_fpsStartTick = SDL_GetTicks();
  }
}

void CRenderer::FlushRenderList() {
  // TODO(LinkZ): Separate render of opaque and transparent faces to fix
  // blending / depth issue
  FlushWorldRenderList();

  // Render 2D surfaces
  FlushSurfacesList();
}

void CRenderer::AddSurface(const RenderBlock2d& render_block) {
  m_surfaces_list.push_back(render_block);
}

void CRenderer::AddWorldRenderBlock(RenderBlock3d* render_block) {
  m_world_render_list.push_back(render_block);
}

void CRenderer::DrawBoxScreen(int x, int y, int cx, int cy,
                              unsigned int color) {
  if ((color & 0xFF000000) == 0u) {
    return;
  }

  // TODO(LinkZ): Render unicolor surface
}

// CTexture* CRenderer::AddSpriteIndex(SprImg* img, uint32_t* pal,
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
//  SurfaceCache new_surface;
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

// CTexture* CRenderer::GetSpriteIndex(SprImg* img, uint32_t* pal_id,
//                                    CACHE_INFO* info) {
//  std::list<SurfaceCache>* surface_list = NULL;
//  std::vector<CACHE_INFO>* info_list = NULL;
//  SurfaceCache* cache_surface = NULL;
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

CSurface* CRenderer::AddSpriteIndex(const SprImg* img, const uint32_t* pal) {
  uint32_t cur_time = GetTick();
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

  // Try to find a recyclable surface
  for (auto& surface_cache : m_cache_surfaces[id1 + id2]) {
    if (surface_cache.last_time + 3750 < cur_time) {
      surface_cache.id = img;
      surface_cache.pal_id = pal;
      surface_cache.tex->UpdateSprite(0, 0, img->width, img->height, img, pal);
      surface_cache.last_time = GetTick();

      return surface_cache.tex;
    }
  }

  SurfaceCache new_surface;
  if (!m_unused_cache_surfaces.empty()) {
    new_surface.tex = m_unused_cache_surfaces.back();
    m_unused_cache_surfaces.pop_back();
  } else {
    new_surface.tex = new CSurface(img->width, img->height);
  }

  new_surface.id = img;
  new_surface.pal_id = pal;
  new_surface.tex->UpdateSprite(0, 0, img->width, img->height, img, pal);
  new_surface.last_time = GetTick();
  m_cache_surfaces[id1 + id2].push_back(new_surface);

  return new_surface.tex;
}

CSurface* CRenderer::GetSpriteIndex(const SprImg* img, const uint32_t* pal) {
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

  for (auto& surface_cache : m_cache_surfaces[id1 + id2]) {
    if (surface_cache.id == img && surface_cache.pal_id == pal) {
      surface_cache.last_time = GetTick();
      return surface_cache.tex;
    }
  }

  return nullptr;
}

const glm::mat4& CRenderer::projection_matrix() const {
  return m_projection_matrix;
}

const glm::mat4& CRenderer::view_matrix() const { return m_view_matrix; }

void CRenderer::SetViewMatrix(const glm::mat4& matrix) {
  m_view_matrix = matrix;
}

// Returns a non owning pointer to a 3d render block that's in the pool. This
// avoids repeated memory allocations when rendering
RenderBlock3d* CRenderer::BorrowRenderBlock() {
  if (m_render_blocks_cursor != std::cend(m_render_blocks_pool)) {
    auto result = m_render_blocks_cursor->get();
    m_render_blocks_cursor = std::next(m_render_blocks_cursor);

    return result;
  }

  // No render blocks left in the pool. Allocate a new one, add it to the pool
  // and return a pointer to it
  auto new_block = std::make_unique<RenderBlock3d>();
  auto result = new_block.get();
  m_render_blocks_pool.push_back(std::move(new_block));
  m_render_blocks_cursor = std::end(m_render_blocks_pool);

  return result;
}

void CRenderer::SetLightInfo(const WorldLightInfo& world_light_info) {
  m_world_light_info = world_light_info;
}

void CRenderer::FlushWorldRenderList() {
  if (m_world_render_list.empty()) {
    return;
  }

  m_world_program.Bind();

  GLuint uniform_id = m_world_program.GetUniformLocation("uProjectionMat");
  glUniformMatrix4fv(uniform_id, 1, GL_FALSE,
                     glm::value_ptr(m_projection_matrix));

  uniform_id = m_world_program.GetUniformLocation("uViewMat");
  glUniformMatrix4fv(uniform_id, 1, GL_FALSE, glm::value_ptr(m_view_matrix));

  uniform_id = m_world_program.GetUniformLocation("uLightDiffuse");
  glUniform3fv(uniform_id, 1, glm::value_ptr(m_world_light_info.diffuse_col));

  uniform_id = m_world_program.GetUniformLocation("uLightAmbient");
  glUniform3fv(uniform_id, 1, glm::value_ptr(m_world_light_info.ambient_col));

  uniform_id = m_world_program.GetUniformLocation("uLightDirection");
  glUniform3fv(uniform_id, 1, glm::value_ptr(m_world_light_info.light_dir));

  uniform_id = m_world_program.GetUniformLocation("uLightIntensity");
  glUniform1fv(uniform_id, 1,
               static_cast<GLfloat*>(&m_world_light_info.light_opacity));

  // Uniform IDs
  const GLuint modelview_id =
      m_world_program.GetUniformLocation("uModelViewMat");
  const GLuint nodeview_id = m_world_program.GetUniformLocation("uNodeViewMat");

  // Attributes IDs
  const GLuint position_attrib =
      m_world_program.GetAttributeLocation("aPosition");
  const GLuint tex_coords_attrib =
      m_world_program.GetAttributeLocation("aTextureCoord");
  const GLuint normal_attrib = m_world_program.GetAttributeLocation("aNormal");

  // Setup the VAO
  glEnableVertexAttribArray(position_attrib);
  glEnableVertexAttribArray(tex_coords_attrib);
  glEnableVertexAttribArray(normal_attrib);

  glActiveTexture(GL_TEXTURE0);

  for (const auto& render_block : m_world_render_list) {
    render_block->vbo->Bind();

    glUniformMatrix4fv(modelview_id, 1, GL_FALSE,
                       render_block->modelview_matrix);

    glUniformMatrix4fv(nodeview_id, 1, GL_FALSE, render_block->nodeview_matrix);

    glVertexAttribPointer(position_attrib, 3, GL_FLOAT, GL_FALSE, 8 * 4,
                          nullptr);
    glVertexAttribPointer(tex_coords_attrib, 2, GL_FLOAT, GL_FALSE, 8 * 4,
                          reinterpret_cast<void*>(3 * 4));
    glVertexAttribPointer(normal_attrib, 3, GL_FLOAT, GL_FALSE, 8 * 4,
                          reinterpret_cast<void*>(5 * 4));

    glBindTexture(GL_TEXTURE_2D, render_block->gl_texture_id);
    glDrawArrays(GL_TRIANGLES, render_block->vbo_first_item,
                 render_block->vbo_item_count);
  }

  glDisableVertexAttribArray(position_attrib);
  glDisableVertexAttribArray(tex_coords_attrib);
  glDisableVertexAttribArray(normal_attrib);

  m_world_program.Unbind();
}

void CRenderer::FlushSurfacesList() {
  if (m_surfaces_list.empty()) {
    return;
  }

  glDisable(GL_DEPTH_TEST);

  m_surface_program.Bind();
  m_surface_vbo.Bind();

  const GLuint position_attrib =
      m_surface_program.GetAttributeLocation("aPosition");
  const GLuint tex_coord_attrib =
      m_surface_program.GetAttributeLocation("aTextureCoord");
  glEnableVertexAttribArray(position_attrib);
  glEnableVertexAttribArray(tex_coord_attrib);

  glVertexAttribPointer(position_attrib, 2, GL_FLOAT, GL_FALSE, 4 * 4, nullptr);
  glVertexAttribPointer(tex_coord_attrib, 2, GL_FLOAT, GL_FALSE, 4 * 4,
                        reinterpret_cast<void*>(2 * 4));

  GLuint uniform_id = m_surface_program.GetUniformLocation("uProjectionMat");
  glUniformMatrix4fv(uniform_id, 1, GL_FALSE,
                     glm::value_ptr(m_2d_projection_matrix));

  uniform_id = m_surface_program.GetUniformLocation("uTexture");
  glUniform1i(uniform_id, 0);

  glActiveTexture(GL_TEXTURE0);

  for (const auto& render_block : m_surfaces_list) {
    const float x = render_block.position.x;
    const float y = render_block.position.y;
    const VertexP2T2 vertices[6] = {
        {x + render_block.width, y + render_block.height, 1.f, 1.f},
        {x + render_block.width, y, 1.f, 0.f},
        {x, y, 0.f, 0.f},
        {x, y, 0.f, 0.f},
        {x, y + render_block.height, 0.f, 1.f},
        {x + render_block.width, y + render_block.height, 1.f, 1.f}};

    m_surface_vbo.SetData(vertices, 6);
    render_block.surface->Bind(GL_TEXTURE_2D);

    glDrawArrays(GL_TRIANGLES, 0, m_surface_vbo.size());
  }

  glDisableVertexAttribArray(position_attrib);
  glDisableVertexAttribArray(tex_coord_attrib);

  m_surface_program.Unbind();

  glEnable(GL_DEPTH_TEST);
}
