#include "Render/3dGround.h"

#include <glm/gtc/round.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Common/Globals.h"
#include "Common/debug.h"
#include "Render/GlShader.h"
#include "Render/rect.h"

const std::string kVertexShader =
    R"(#version 140

    attribute vec3 aPosition;
    attribute vec2 aTextureCoord;
	attribute vec2 aLightmapCoord;

    uniform mat4 uModelViewMat;
    uniform mat4 uProjectionMat;

    varying vec2 vTextureCoord;
    varying vec2 vLightmapCoord;

    void main() {
      gl_Position = uProjectionMat * uModelViewMat * vec4(aPosition, 1.0);
      vTextureCoord = aTextureCoord;
      vLightmapCoord = aLightmapCoord;
    })";

const std::string kFragmentShader =
    R"(#version 140

    varying vec2 vTextureCoord;
	varying vec2 vLightmapCoord;

    uniform sampler2D uTexture;
    uniform sampler2D uLightmap;

    void main() {
      vec4 color = texture2D(uTexture, vTextureCoord);
      color *= texture2D(uLightmap, vLightmapCoord).a;
      color += clamp(vec4(texture2D(uLightmap, vLightmapCoord).rgb, 1.0), 0.0, 1.0);

      gl_FragColor = color;
    })";

struct GndVertex {
  float position[3];
  float texture_coord[2];
  float lightmap_coord[2];
};

C3dGround::C3dGround()
    : m_program(),
      m_vbo(),
      m_texture_atlas(nullptr),
      m_lightmap(nullptr),
      m_attr(),
      m_width(),
      m_height(),
      m_zoom(10.0f),
      m_water_level(),
      m_tex_anim_cycle(3),
      m_wave_pitch(50),
      m_wave_speed(2),
      m_water_set(),
      m_wave_height(1.0f),
      m_water_tex(),
      m_p_bump_map(),
      m_water_cnt(),
      m_water_offset(),
      m_is_new_ver() {}

C3dGround::~C3dGround() {}

bool C3dGround::Init() {
  CGlShader vertex_shader;
  CGlShader fragment_shader;

  // Setup the VBO to store GndVertex objects
  m_vbo.SetVertexFormat<GndVertex>();

  if (!vertex_shader.Init(kVertexShader, GL_VERTEX_SHADER)) {
    return false;
  }

  if (!fragment_shader.Init(kFragmentShader, GL_FRAGMENT_SHADER)) {
    return false;
  }

  return m_program.Init({vertex_shader, fragment_shader});
}

void C3dGround::AssignGnd(CGndRes *gnd, glm::vec3 *light,
                          glm::vec3 *diffuse_col, glm::vec3 *ambient_col) {
  std::vector<GndVertex> gnd_vertices;

  m_width = gnd->GetWidth();
  m_height = gnd->GetHeight();
  m_zoom = gnd->GetZoom();

  UpdateTextureAtlas(gnd->GetTextureNameTable());
  UpdateLightmap(gnd->GetLightmaps());

  const float atlas_texture_size = m_texture_atlas->texture_size();

  m_cells.resize(m_width * m_height);
  m_surfaces.resize(gnd->GetSurfaceCount());
  for (int32_t y = 0; y < m_height; y++) {
    for (int32_t x = 0; x < m_width; x++) {
      const GndCellFmt &cell_fmt = gnd->GetCell(x, y);
      GndCell &cell = m_cells[x + y * m_width];

      cell.h[0] = cell_fmt.height[0];
      cell.h[1] = cell_fmt.height[1];
      cell.h[2] = cell_fmt.height[2];
      cell.h[3] = cell_fmt.height[3];

      // TODO: Get rid of this once the camera is moveable
      const int32_t coord_x = x - m_width / 2;
      const int32_t coord_y = y - m_height / 2;

      cell.water_vert[0] = glm::vec3(coord_x * m_zoom, 0, coord_y * m_zoom);
      cell.water_vert[1] =
          glm::vec3((coord_x + 1) * m_zoom, 0, coord_y * m_zoom);
      cell.water_vert[2] =
          glm::vec3(coord_x * m_zoom, 0, (coord_y + 1) * m_zoom);
      cell.water_vert[3] =
          glm::vec3((coord_x + 1) * m_zoom, 0, (coord_y + 1) * m_zoom);

      auto surface_id = cell_fmt.top_surface_id;
      if (surface_id >= 0 && surface_id < gnd->GetSurfaceCount() - 1) {
        const GndSurfaceFmt &surface_fmt = gnd->GetSurface(surface_id);
        GndSurface *surface = &m_surfaces[surface_id];

        surface->bgra = surface_fmt.bgra;
        auto texture_name = gnd->GetTextureName(surface_fmt.texture_id);
        surface->tex = g_TexMgr->GetTexture(texture_name, false);

        float r_width = 0;
        float r_height = 0;
        glm::vec2 texture_position = {};
        if (surface->tex) {
          r_width =
              (surface->tex->GetUpdateWidth() / surface->tex->GetWidth()) *
              (atlas_texture_size / m_texture_atlas->GetWidth());
          r_height =
              (surface->tex->GetUpdateHeight() / surface->tex->GetHeight()) *
              (atlas_texture_size / m_texture_atlas->GetHeight());
          texture_position = m_texture_atlas->GetTexturePosition(texture_name);
        }

        const glm::vec2 lm1(
            (surface_fmt.lightmap_id % 256) * (8.0f / 2048.0f) + 1.0f / 2048.0f,
            (surface_fmt.lightmap_id / 256) * (8.0f / 2048.0f) +
                1.0f / 2048.0f);
        const glm::vec2 lm2 = lm1 + glm::vec2(6.0f / 2048.0f, 6.0f / 2048.0f);

        gnd_vertices.push_back(
            {coord_x * m_zoom, cell.h[0], coord_y * m_zoom,
             r_width * surface_fmt.u[0] + texture_position.x,
             r_height * surface_fmt.v[0] + texture_position.y, lm1.x,
             lm1.y});  // 0
        gnd_vertices.push_back(
            {(coord_x + 1) * m_zoom, cell.h[1], coord_y * m_zoom,
             r_width * surface_fmt.u[1] + texture_position.x,
             r_height * surface_fmt.v[1] + texture_position.y, lm2.x,
             lm1.y});  // 1
        gnd_vertices.push_back(
            {(coord_x + 1) * m_zoom, cell.h[3], (coord_y + 1) * m_zoom,
             r_width * surface_fmt.u[3] + texture_position.x,
             r_height * surface_fmt.v[3] + texture_position.y, lm2.x,
             lm2.y});  // 3

        gnd_vertices.push_back(
            {(coord_x + 1) * m_zoom, cell.h[3], (coord_y + 1) * m_zoom,
             r_width * surface_fmt.u[3] + texture_position.x,
             r_height * surface_fmt.v[3] + texture_position.y, lm2.x,
             lm2.y});  // 3
        gnd_vertices.push_back(
            {coord_x * m_zoom, cell.h[2], (coord_y + 1) * m_zoom,
             r_width * surface_fmt.u[2] + texture_position.x,
             r_height * surface_fmt.v[2] + texture_position.y, lm1.x,
             lm2.y});  // 2
        gnd_vertices.push_back(
            {coord_x * m_zoom, cell.h[0], coord_y * m_zoom,
             r_width * surface_fmt.u[0] + texture_position.x,
             r_height * surface_fmt.v[0] + texture_position.y, lm1.x,
             lm1.y});  // 0

        cell.top = surface;
      }

      surface_id = cell_fmt.front_surface_id;
      if (surface_id >= 0 && surface_id < gnd->GetSurfaceCount() - 1 &&
          y + 1 < gnd->GetHeight()) {
        const GndSurfaceFmt &surface_fmt = gnd->GetSurface(surface_id);
        const GndCellFmt &front_cell_fmt = gnd->GetCell(x, y + 1);
        GndSurface *surface = &m_surfaces[surface_id];

        surface->bgra = surface_fmt.bgra;
        auto texture_name = gnd->GetTextureName(surface_fmt.texture_id);
        surface->tex = g_TexMgr->GetTexture(texture_name, false);

        float r_width = 0;
        float r_height = 0;
        glm::vec2 texture_position = {};
        if (surface->tex) {
          r_width =
              (surface->tex->GetUpdateWidth() / surface->tex->GetWidth()) *
              (atlas_texture_size / m_texture_atlas->GetWidth());
          r_height =
              (surface->tex->GetUpdateHeight() / surface->tex->GetHeight()) *
              (atlas_texture_size / m_texture_atlas->GetHeight());
          texture_position = m_texture_atlas->GetTexturePosition(texture_name);
        }

        const glm::vec2 lm1(
            (surface_fmt.lightmap_id % 256) * (8.0f / 2048.0f) + 1.0f / 2048.0f,
            (surface_fmt.lightmap_id / 256) * (8.0f / 2048.0f) +
                1.0f / 2048.0f);
        const glm::vec2 lm2 = lm1 + glm::vec2(6.0f / 2048.0f, 6.0f / 2048.0f);

        gnd_vertices.push_back(
            {(coord_x + 1) * m_zoom, cell.h[3], (coord_y + 1) * m_zoom,
             r_width * surface_fmt.u[1] + texture_position.x,
             r_height * surface_fmt.v[1] + texture_position.y, lm2.x,
             lm1.y});  // 1
        gnd_vertices.push_back(
            {(coord_x + 1) * m_zoom, front_cell_fmt.height[1],
             (coord_y + 1) * m_zoom,
             r_width * surface_fmt.u[3] + texture_position.x,
             r_height * surface_fmt.v[3] + texture_position.y, lm2.x,
             lm2.y});  // 3
        gnd_vertices.push_back(
            {coord_x * m_zoom, front_cell_fmt.height[0], (coord_y + 1) * m_zoom,
             r_width * surface_fmt.u[2] + texture_position.x,
             r_height * surface_fmt.v[2] + texture_position.y, lm1.x,
             lm2.y});  // 2

        gnd_vertices.push_back(
            {coord_x * m_zoom, front_cell_fmt.height[0], (coord_y + 1) * m_zoom,
             r_width * surface_fmt.u[2] + texture_position.x,
             r_height * surface_fmt.v[2] + texture_position.y, lm1.x,
             lm2.y});  // 2
        gnd_vertices.push_back(
            {coord_x * m_zoom, cell.h[2], (coord_y + 1) * m_zoom,
             r_width * surface_fmt.u[0] + texture_position.x,
             r_height * surface_fmt.v[0] + texture_position.y, lm1.x,
             lm1.y});  // 0
        gnd_vertices.push_back(
            {(coord_x + 1) * m_zoom, cell.h[3], (coord_y + 1) * m_zoom,
             r_width * surface_fmt.u[1] + texture_position.x,
             r_height * surface_fmt.v[1] + texture_position.y, lm2.x,
             lm1.y});  // 1

        cell.front = surface;
      }

      surface_id = cell_fmt.right_surface_id;
      if (surface_id >= 0 && surface_id < gnd->GetSurfaceCount() - 1 &&
          x + 1 < gnd->GetWidth()) {
        const GndSurfaceFmt &surface_fmt = gnd->GetSurface(surface_id);
        const GndCellFmt &right_cell_fmt = gnd->GetCell(x + 1, y);
        GndSurface *surface = &m_surfaces[surface_id];

        surface->bgra = surface_fmt.bgra;
        auto texture_name = gnd->GetTextureName(surface_fmt.texture_id);
        surface->tex = g_TexMgr->GetTexture(texture_name, false);

        float r_width = 0;
        float r_height = 0;
        glm::vec2 texture_position = {};
        if (surface->tex) {
          r_width =
              (surface->tex->GetUpdateWidth() / surface->tex->GetWidth()) *
              (atlas_texture_size / m_texture_atlas->GetWidth());
          r_height =
              (surface->tex->GetUpdateHeight() / surface->tex->GetHeight()) *
              (atlas_texture_size / m_texture_atlas->GetHeight());
          texture_position = m_texture_atlas->GetTexturePosition(texture_name);
        }

        const glm::vec2 lm1(
            (surface_fmt.lightmap_id % 256) * (8.0f / 2048.0f) + 1.0f / 2048.0f,
            (surface_fmt.lightmap_id / 256) * (8.0f / 2048.0f) +
                1.0f / 2048.0f);
        const glm::vec2 lm2 = lm1 + glm::vec2(6.0f / 2048.0f, 6.0f / 2048.0f);

        gnd_vertices.push_back(
            {(coord_x + 1) * m_zoom, cell.h[3], (coord_y + 1) * m_zoom,
             r_width * surface_fmt.u[0] + texture_position.x,
             r_height * surface_fmt.v[0] + texture_position.y, lm1.x,
             lm1.y});  // 0
        gnd_vertices.push_back(
            {(coord_x + 1) * m_zoom, cell.h[1], coord_y * m_zoom,
             r_width * surface_fmt.u[1] + texture_position.x,
             r_height * surface_fmt.v[1] + texture_position.y, lm2.x,
             lm1.y});  // 1
        gnd_vertices.push_back(
            {(coord_x + 1) * m_zoom, right_cell_fmt.height[0], coord_y * m_zoom,
             r_width * surface_fmt.u[3] + texture_position.x,
             r_height * surface_fmt.v[3] + texture_position.y, lm2.x,
             lm2.y});  // 3

        gnd_vertices.push_back(
            {(coord_x + 1) * m_zoom, right_cell_fmt.height[0], coord_y * m_zoom,
             r_width * surface_fmt.u[3] + texture_position.x,
             r_height * surface_fmt.v[3] + texture_position.y, lm2.x,
             lm2.y});  // 3
        gnd_vertices.push_back(
            {(coord_x + 1) * m_zoom, right_cell_fmt.height[2],
             (coord_y + 1) * m_zoom,
             r_width * surface_fmt.u[2] + texture_position.x,
             r_height * surface_fmt.v[2] + texture_position.y, lm1.x,
             lm2.y});  // 2
        gnd_vertices.push_back(
            {(coord_x + 1) * m_zoom, cell.h[3], (coord_y + 1) * m_zoom,
             r_width * surface_fmt.u[0] + texture_position.x,
             r_height * surface_fmt.v[0] + texture_position.y, lm1.x,
             lm1.y});  // 0

        cell.right = surface;
      }
    }
  }

  m_vbo.SetData(gnd_vertices.data(), gnd_vertices.size());
}

void C3dGround::UpdateTextureAtlas(
    const std::vector<std::string> &texture_names) {
  if (m_texture_atlas != nullptr) {
    // Destroy previous texture atlas
    m_texture_atlas.reset();
  }

  m_texture_atlas = std::make_unique<CTextureAtlas>();
  m_texture_atlas->Create(256, texture_names);
}

void C3dGround::UpdateLightmap(const std::vector<LightmapInfo> &lightmaps) {
  if (m_lightmap != nullptr) {
    // Destroy previous lightmap
    m_lightmap.reset();
  }

  m_lightmap = std::make_unique<CTexture>(2048, 2048, PF_A8R8G8B8);

  ILubyte *data = new ILubyte[2048 * 2048 * 4];
  int x = 0;
  int y = 0;

  for (const auto &lightmap : lightmaps) {
    for (int yy = 0; yy < 8; yy++) {
      for (int xx = 0; xx < 8; xx++) {
        const int xxx = 8 * x + xx;
        const int yyy = 8 * y + yy;

        data[4 * (xxx + 2048 * yyy) + 0] = lightmap.sdata[yy][xx][0] & 0xF0;
        data[4 * (xxx + 2048 * yyy) + 1] = lightmap.sdata[yy][xx][1] & 0xF0;
        data[4 * (xxx + 2048 * yyy) + 2] = lightmap.sdata[yy][xx][2] & 0xF0;
        data[4 * (xxx + 2048 * yyy) + 3] = lightmap.idata[yy][xx];
      }
    }

    x++;
    if (x >= 256) {
      x = 0;
      y++;
      if (y >= 256) {
        LOG(error, "Lightmap is too big!");
      }
    }
  }

  m_lightmap->Update(0, 0, 2048, 2048, data, 0);

  delete[] data;
}

void C3dGround::Render(glm::mat4 *wtm, RECT *area, bool need_clip) {
  GLuint location_id;

  m_program.Bind();

  const auto projection_matrix = g_Renderer->projection_matrix();
  location_id = m_program.GetUniformLocation("uProjectionMat");
  glUniformMatrix4fv(location_id, 1, GL_FALSE,
                     glm::value_ptr(projection_matrix));

  location_id = m_program.GetUniformLocation("uTexture");
  glUniform1i(location_id, 0);

  location_id = m_program.GetUniformLocation("uLightmap");
  glUniform1i(location_id, 1);

  const auto view_matrix = g_Renderer->view_matrix();
  location_id = m_program.GetUniformLocation("uModelViewMat");
  glUniformMatrix4fv(location_id, 1, GL_FALSE, glm::value_ptr(view_matrix));

  m_vbo.Bind();

  const GLuint position_attrib = m_program.GetAttributeLocation("aPosition");
  const GLuint tex_coord_attrib =
      m_program.GetAttributeLocation("aTextureCoord");
  const GLuint lm_coord_attrib =
      m_program.GetAttributeLocation("aLightmapCoord");

  glEnableVertexAttribArray(position_attrib);
  glEnableVertexAttribArray(tex_coord_attrib);
  glEnableVertexAttribArray(lm_coord_attrib);

  glVertexAttribPointer(position_attrib, 3, GL_FLOAT, GL_FALSE, 7 * 4, nullptr);
  glVertexAttribPointer(tex_coord_attrib, 2, GL_FLOAT, GL_FALSE, 7 * 4,
                        reinterpret_cast<void *>(3 * 4));
  glVertexAttribPointer(lm_coord_attrib, 2, GL_FLOAT, GL_FALSE, 7 * 4,
                        reinterpret_cast<void *>(5 * 4));

  glActiveTexture(GL_TEXTURE0);
  m_texture_atlas->Bind(GL_TEXTURE_2D);

  glActiveTexture(GL_TEXTURE1);
  m_lightmap->Bind(GL_TEXTURE_2D);

  glDrawArrays(GL_TRIANGLES, 0, m_vbo.size());

  m_program.Unbind();
}
