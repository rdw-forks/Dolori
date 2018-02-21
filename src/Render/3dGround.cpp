#include "3dGround.h"
#include "Common/Globals.h"
#include "rect.h"

C3dGround::C3dGround() {
  m_zoom = 10.0f;
  m_water_level = 0;
  m_tex_anim_cycle = 3;
  m_wave_pitch = 50;
  m_wave_speed = 2;
  m_wave_height = 1.0f;
  m_water_set = 0;
  // m_water_tex = nullptr;
  m_attr = nullptr;
  // m_p_bump_map = nullptr;
  // m_is_new_ver = 0;
}

C3dGround::~C3dGround() {}

void C3dGround::AssignGnd(CGndRes *gnd, glm::vec3 *light,
                          glm::vec3 *diffuse_col, glm::vec3 *ambient_col) {
  using namespace glm;

  m_width = gnd->GetWidth();
  m_height = gnd->GetHeight();
  m_zoom = gnd->GetZoom();
  m_num_surfaces = gnd->GetSurfaceCount();

  m_cells.resize(m_width * m_height);
  m_surfaces.resize(m_num_surfaces);
  for (unsigned int y = 0; y < m_height; y++) {
    for (unsigned int x = 0; x < m_width; x++) {
      const GND_CELL_FMT cell_fmt = gnd->GetCell(x, y);
      unsigned int index = x + y * m_width;
      GND_CELL *cell = &m_cells[index];

      cell->h[0] = cell_fmt.height[0];
      cell->h[1] = cell_fmt.height[1];
      cell->h[2] = cell_fmt.height[2];
      cell->h[3] = cell_fmt.height[3];

      int coord_x = x - m_width / 2;
      int coord_y = y - m_height / 2;
      cell->water_vert[0] = vec3(coord_x * m_zoom, 0, coord_y * m_zoom);
      cell->water_vert[1] = vec3((coord_x + 1) * m_zoom, 0, coord_y * m_zoom);
      cell->water_vert[2] = vec3(coord_x * m_zoom, 0, (coord_y + 1) * m_zoom);
      cell->water_vert[3] =
          vec3((coord_x + 1) * m_zoom, 0, (coord_y + 1) * m_zoom);

      int surface_id = cell_fmt.top_surface_id;
      if (surface_id > 0 && surface_id < gnd->GetSurfaceCount()) {
        const GND_SURFACE_FMT surface_fmt = gnd->GetSurface(surface_id);
        GND_SURFACE *surface = &m_surfaces[surface_id];

        surface->argb = surface_fmt.argb;
        surface->tex = g_TexMgr->GetTexture(
            gnd->GetTextureName(surface_fmt.texture_id), false);
        if (surface->tex) {
          float r_width =
              (surface->tex->GetUpdateWidth() / surface->tex->GetWidth());
          float r_height =
              (surface->tex->GetUpdateHeight() / surface->tex->GetHeight());

          surface->vertex[0].texture_coords =
              vec2(r_width * surface_fmt.u[0], r_height * surface_fmt.v[0]);
          surface->vertex[1].texture_coords =
              vec2(r_width * surface_fmt.u[1], r_height * surface_fmt.v[1]);
          surface->vertex[2].texture_coords =
              vec2(r_width * surface_fmt.u[2], r_height * surface_fmt.v[2]);
          surface->vertex[3].texture_coords =
              vec2(r_width * surface_fmt.u[3], r_height * surface_fmt.v[3]);
        }

        surface->vertex[0].vertex =
            vec3(coord_x * m_zoom, cell->h[0], coord_y * m_zoom);
        surface->vertex[1].vertex =
            vec3((coord_x + 1) * m_zoom, cell->h[1], coord_y * m_zoom);
        surface->vertex[2].vertex =
            vec3(coord_x * m_zoom, cell->h[2], (coord_y + 1) * m_zoom);
        surface->vertex[3].vertex =
            vec3((coord_x + 1) * m_zoom, cell->h[3], (coord_y + 1) * m_zoom);

        // if (g_is_lightmap) {
        //}
        // else {
        surface->lmtex = NULL;
        //}

        cell->top = surface;
      }

      if (coord_y + 1 < gnd->GetHeight()) {
        GND_CELL *front_cell = &m_cells[x + (y + 1) * m_width];
        surface_id = cell_fmt.front_surface_id;
        if (surface_id > 0 && surface_id < gnd->GetSurfaceCount()) {
          const GND_SURFACE_FMT surface_fmt = gnd->GetSurface(surface_id);
          GND_SURFACE *surface = &m_surfaces[surface_id];

          surface->argb = surface_fmt.argb;
          surface->tex = g_TexMgr->GetTexture(
              gnd->GetTextureName(surface_fmt.texture_id), false);
          if (surface->tex) {
            float r_width =
                (surface->tex->GetUpdateWidth() / surface->tex->GetWidth());
            float r_height =
                (surface->tex->GetUpdateHeight() / surface->tex->GetHeight());

            surface->vertex[0].texture_coords =
                vec2(r_width * surface_fmt.u[0], r_height * surface_fmt.v[0]);
            surface->vertex[1].texture_coords =
                vec2(r_width * surface_fmt.u[1], r_height * surface_fmt.v[1]);
            surface->vertex[2].texture_coords =
                vec2(r_width * surface_fmt.u[2], r_height * surface_fmt.v[2]);
            surface->vertex[3].texture_coords =
                vec2(r_width * surface_fmt.u[3], r_height * surface_fmt.v[3]);
          }

          surface->vertex[0].vertex =
              vec3(coord_x * m_zoom, cell->h[2], (coord_y + 1) * m_zoom);
          surface->vertex[1].vertex =
              vec3((coord_x + 1) * m_zoom, cell->h[3], (coord_y + 1) * m_zoom);
          surface->vertex[2].vertex =
              vec3(coord_x * m_zoom, front_cell->h[0], (coord_y + 1) * m_zoom);
          surface->vertex[3].vertex = vec3(
              (coord_x + 1) * m_zoom, front_cell->h[1], (coord_y + 1) * m_zoom);

          // if (g_is_lightmap) {
          //}
          // else {
          surface->lmtex = NULL;
          //}

          cell->front = surface;
        }
      }

      if (coord_x + 1 < gnd->GetWidth()) {
        GND_CELL *right_cell = &m_cells[(x + 1) + y * m_width];
        surface_id = cell_fmt.right_surface_id;
        if (surface_id > 0 && surface_id < gnd->GetSurfaceCount()) {
          const GND_SURFACE_FMT surface_fmt = gnd->GetSurface(surface_id);
          GND_SURFACE *surface = &m_surfaces[surface_id];

          surface->argb = surface_fmt.argb;
          surface->tex = g_TexMgr->GetTexture(
              gnd->GetTextureName(surface_fmt.texture_id), false);
          if (surface->tex) {
            float r_width =
                (surface->tex->GetUpdateWidth() / surface->tex->GetWidth());
            float r_height =
                (surface->tex->GetUpdateHeight() / surface->tex->GetHeight());

            surface->vertex[0].texture_coords =
                vec2(r_width * surface_fmt.u[0], r_height * surface_fmt.v[0]);
            surface->vertex[1].texture_coords =
                vec2(r_width * surface_fmt.u[1], r_height * surface_fmt.v[1]);
            surface->vertex[2].texture_coords =
                vec2(r_width * surface_fmt.u[2], r_height * surface_fmt.v[2]);
            surface->vertex[3].texture_coords =
                vec2(r_width * surface_fmt.u[3], r_height * surface_fmt.v[3]);
          }

          surface->vertex[0].vertex =
              vec3((coord_x + 1) * m_zoom, cell->h[3], (coord_y + 1) * m_zoom);
          surface->vertex[1].vertex =
              vec3((coord_x + 1) * m_zoom, cell->h[1], coord_y * m_zoom);
          surface->vertex[2].vertex = vec3(
              (coord_x + 1) * m_zoom, right_cell->h[2], (coord_y + 1) * m_zoom);
          surface->vertex[3].vertex =
              vec3((coord_x + 1) * m_zoom, right_cell->h[0], coord_y * m_zoom);

          // if (g_is_lightmap) {
          //}
          // else {
          surface->lmtex = NULL;
          //}

          cell->right = surface;
        }
      }
    }
  }
}

void C3dGround::Render(glm::mat4 *wtm, RECT_ *area, bool need_clip) {
  for (uint32_t y = 0; y < m_height; y++) {
    for (uint32_t x = 0; x < m_width; x++) {
      // for (uint32_t y = area->bottom; y < area->top; y++) {
      //  for (uint32_t x = area->left; x < area->right; x++) {
      GND_CELL cell = m_cells[x + y * m_width];

      if (cell.top) {
        CRPQuadFace *rp = g_Renderer->BorrowQuadRP();
        for (int i = 0; i < 4; i++) {
          rp->SetGeomInfo(i, cell.top->vertex[i]);
        }
        rp->set_texture(cell.top->tex);
        g_Renderer->AddRP(rp, 1);
      }

      if (cell.front) {
        CRPQuadFace *rp = g_Renderer->BorrowQuadRP();
        for (int i = 0; i < 4; i++) {
          rp->SetGeomInfo(i, cell.front->vertex[i]);
        }
        rp->set_texture(cell.front->tex);
        g_Renderer->AddRP(rp, 1);
      }

      if (cell.right) {
        CRPQuadFace *rp = g_Renderer->BorrowQuadRP();
        for (int i = 0; i < 4; i++) {
          rp->SetGeomInfo(i, cell.right->vertex[i]);
        }
        rp->set_texture(cell.right->tex);
        g_Renderer->AddRP(rp, 1);
      }
    }
  }
}
