#include "Render/3dGround.h"

#include <glm/gtc/round.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Common/Globals.h"
#include "Render/GlShader.h"
#include "Render/rect.h"

const std::string kVertexShader =
    "#version 140\n"

    "attribute vec3 aPosition;"
    "attribute vec2 aTextureCoord;"

    "uniform mat4 uModelViewMat;"
    "uniform mat4 uProjectionMat;"

    "varying vec2 vTextureCoord;"

    "void main() {"
    "  gl_Position = uProjectionMat * uModelViewMat * vec4(aPosition, 1.0);"
    "  vTextureCoord = aTextureCoord;"
    "}";

const std::string kFragmentShader =
    "#version 140\n"

    "varying vec2 vTextureCoord;"

    "uniform sampler2D uTexture;"

    "void main() {"
    "  gl_FragColor= texture2D(uTexture, vTextureCoord.st);"
    "}";

struct GndVertex {
  float position[3];
  float texture_coord[2];
};

C3dGround::C3dGround()
    : m_program(),
      m_vbo(),
      m_texture_atlas(nullptr),
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
  using namespace glm;

  std::vector<GndVertex> gnd_vertices;

  m_width = gnd->GetWidth();
  m_height = gnd->GetHeight();
  m_zoom = gnd->GetZoom();
  m_num_surfaces = gnd->GetSurfaceCount();

  UpdateTextureAtlas(gnd->GetTextureNameTable());

  const float atlas_texture_size = m_texture_atlas->texture_size();

  m_cells.resize(m_width * m_height);
  m_surfaces.resize(m_num_surfaces);
  for (int32_t y = 0; y < m_height; y++) {
    for (int32_t x = 0; x < m_width; x++) {
      const GND_CELL_FMT cell_fmt = gnd->GetCell(x, y);
      GND_CELL &cell = m_cells[x + y * m_width];

      cell.h[0] = cell_fmt.height[0];
      cell.h[1] = cell_fmt.height[1];
      cell.h[2] = cell_fmt.height[2];
      cell.h[3] = cell_fmt.height[3];

      // TODO: Get rid of this once the camera is moveable
      const int32_t coord_x = x - m_width / 2;
      const int32_t coord_y = y - m_height / 2;

      cell.water_vert[0] = vec3(coord_x * m_zoom, 0, coord_y * m_zoom);
      cell.water_vert[1] = vec3((coord_x + 1) * m_zoom, 0, coord_y * m_zoom);
      cell.water_vert[2] = vec3(coord_x * m_zoom, 0, (coord_y + 1) * m_zoom);
      cell.water_vert[3] =
          vec3((coord_x + 1) * m_zoom, 0, (coord_y + 1) * m_zoom);

      auto surface_id = cell_fmt.top_surface_id;
      if (surface_id >= 0 && surface_id < gnd->GetSurfaceCount() - 1) {
        const GND_SURFACE_FMT surface_fmt = gnd->GetSurface(surface_id);
        GND_SURFACE *surface = &m_surfaces[surface_id];

        surface->argb = surface_fmt.argb;
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

        gnd_vertices.push_back(
            {coord_x * m_zoom, cell.h[0], coord_y * m_zoom,
             r_width * surface_fmt.u[0] + texture_position.x,
             r_height * surface_fmt.v[0] + texture_position.y});  // 0
        gnd_vertices.push_back(
            {(coord_x + 1) * m_zoom, cell.h[1], coord_y * m_zoom,
             r_width * surface_fmt.u[1] + texture_position.x,
             r_height * surface_fmt.v[1] + texture_position.y});  // 1
        gnd_vertices.push_back(
            {(coord_x + 1) * m_zoom, cell.h[3], (coord_y + 1) * m_zoom,
             r_width * surface_fmt.u[3] + texture_position.x,
             r_height * surface_fmt.v[3] + texture_position.y});  // 3

        gnd_vertices.push_back(
            {(coord_x + 1) * m_zoom, cell.h[3], (coord_y + 1) * m_zoom,
             r_width * surface_fmt.u[3] + texture_position.x,
             r_height * surface_fmt.v[3] + texture_position.y});  // 3
        gnd_vertices.push_back(
            {coord_x * m_zoom, cell.h[2], (coord_y + 1) * m_zoom,
             r_width * surface_fmt.u[2] + texture_position.x,
             r_height * surface_fmt.v[2] + texture_position.y});  // 2
        gnd_vertices.push_back(
            {coord_x * m_zoom, cell.h[0], coord_y * m_zoom,
             r_width * surface_fmt.u[0] + texture_position.x,
             r_height * surface_fmt.v[0] + texture_position.y});  // 0

        // if (g_is_lightmap) {
        //}
        // else {
        surface->lmtex = nullptr;
        //}

        cell.top = surface;
      }

      surface_id = cell_fmt.front_surface_id;
      if (surface_id >= 0 && surface_id < gnd->GetSurfaceCount() - 1 &&
          y + 1 < gnd->GetHeight()) {
        const GND_SURFACE_FMT surface_fmt = gnd->GetSurface(surface_id);
        const GND_CELL_FMT front_cell_fmt = gnd->GetCell(x, y + 1);
        GND_SURFACE *surface = &m_surfaces[surface_id];

        surface->argb = surface_fmt.argb;
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

        gnd_vertices.push_back(
            {(coord_x + 1) * m_zoom, cell.h[3], (coord_y + 1) * m_zoom,
             r_width * surface_fmt.u[1] + texture_position.x,
             r_height * surface_fmt.v[1] + texture_position.y});  // 1
        gnd_vertices.push_back(
            {(coord_x + 1) * m_zoom, front_cell_fmt.height[1],
             (coord_y + 1) * m_zoom,
             r_width * surface_fmt.u[3] + texture_position.x,
             r_height * surface_fmt.v[3] + texture_position.y});  // 3
        gnd_vertices.push_back(
            {coord_x * m_zoom, front_cell_fmt.height[0], (coord_y + 1) * m_zoom,
             r_width * surface_fmt.u[2] + texture_position.x,
             r_height * surface_fmt.v[2] + texture_position.y});  // 2

        gnd_vertices.push_back(
            {coord_x * m_zoom, front_cell_fmt.height[0], (coord_y + 1) * m_zoom,
             r_width * surface_fmt.u[2] + texture_position.x,
             r_height * surface_fmt.v[2] + texture_position.y});  // 2
        gnd_vertices.push_back(
            {coord_x * m_zoom, cell.h[2], (coord_y + 1) * m_zoom,
             r_width * surface_fmt.u[0] + texture_position.x,
             r_height * surface_fmt.v[0] + texture_position.y});  // 0
        gnd_vertices.push_back(
            {(coord_x + 1) * m_zoom, cell.h[3], (coord_y + 1) * m_zoom,
             r_width * surface_fmt.u[1] + texture_position.x,
             r_height * surface_fmt.v[1] + texture_position.y});  // 1

        // if (g_is_lightmap) {
        //}
        // else {
        surface->lmtex = nullptr;
        //}

        cell.front = surface;
      }

      surface_id = cell_fmt.right_surface_id;
      if (surface_id >= 0 && surface_id < gnd->GetSurfaceCount() - 1 &&
          x + 1 < gnd->GetWidth()) {
        const GND_SURFACE_FMT surface_fmt = gnd->GetSurface(surface_id);
        const GND_CELL_FMT right_cell_fmt = gnd->GetCell(x + 1, y);
        GND_SURFACE *surface = &m_surfaces[surface_id];

        surface->argb = surface_fmt.argb;
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

        gnd_vertices.push_back(
            {(coord_x + 1) * m_zoom, cell.h[3], (coord_y + 1) * m_zoom,
             r_width * surface_fmt.u[0] + texture_position.x,
             r_height * surface_fmt.v[0] + texture_position.y});  // 0
        gnd_vertices.push_back(
            {(coord_x + 1) * m_zoom, cell.h[1], coord_y * m_zoom,
             r_width * surface_fmt.u[1] + texture_position.x,
             r_height * surface_fmt.v[1] + texture_position.y});  // 1
        gnd_vertices.push_back(
            {(coord_x + 1) * m_zoom, right_cell_fmt.height[0], coord_y * m_zoom,
             r_width * surface_fmt.u[3] + texture_position.x,
             r_height * surface_fmt.v[3] + texture_position.y});  // 3

        gnd_vertices.push_back(
            {(coord_x + 1) * m_zoom, right_cell_fmt.height[0], coord_y * m_zoom,
             r_width * surface_fmt.u[3] + texture_position.x,
             r_height * surface_fmt.v[3] + texture_position.y});  // 3
        gnd_vertices.push_back(
            {(coord_x + 1) * m_zoom, right_cell_fmt.height[2],
             (coord_y + 1) * m_zoom,
             r_width * surface_fmt.u[2] + texture_position.x,
             r_height * surface_fmt.v[2] + texture_position.y});  // 2
        gnd_vertices.push_back(
            {(coord_x + 1) * m_zoom, cell.h[3], (coord_y + 1) * m_zoom,
             r_width * surface_fmt.u[0] + texture_position.x,
             r_height * surface_fmt.v[0] + texture_position.y});  // 0

        // if (g_is_lightmap) {
        //}
        // else {
        surface->lmtex = nullptr;
        //}

        cell.right = surface;
      }
    }
  }

  m_vbo.SetData(gnd_vertices.data(), gnd_vertices.size());
}

void C3dGround::UpdateTextureAtlas(
    const std::vector<char const *> &texture_names) {
  if (m_texture_atlas != nullptr) {
    // Destroy previous texture atlas
    m_texture_atlas.reset();
  }

  m_texture_atlas = std::make_unique<CTextureAtlas>();
  m_texture_atlas->Create(256, texture_names);
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

  const auto view_matrix = g_Renderer->view_matrix();
  location_id = m_program.GetUniformLocation("uModelViewMat");
  glUniformMatrix4fv(location_id, 1, GL_FALSE, glm::value_ptr(view_matrix));

  // Bind our vertex attributes buffer
  m_vbo.Bind();

  const GLuint position_attrib = m_program.GetAttributeLocation("aPosition");
  const GLuint tex_coord_attrib =
      m_program.GetAttributeLocation("aTextureCoord");

  glEnableVertexAttribArray(position_attrib);
  glEnableVertexAttribArray(tex_coord_attrib);

  glVertexAttribPointer(position_attrib, 3, GL_FLOAT, GL_FALSE, 5 * 4, 0);
  glVertexAttribPointer(tex_coord_attrib, 2, GL_FLOAT, GL_FALSE, 5 * 4,
                        reinterpret_cast<void *>(3 * 4));

  // Bind the texture
  glActiveTexture(GL_TEXTURE0);
  m_texture_atlas->Bind(GL_TEXTURE_2D);

  glDrawArrays(GL_TRIANGLES, 0, m_vbo.size());

  m_program.Unbind();
}
