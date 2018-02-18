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
  // m_water_tex = NULL;
  m_attr = NULL;
  // m_p_bump_map = NULL;
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

      if (cell_fmt.top_surface_id > 0 &&
          cell_fmt.top_surface_id < gnd->GetSurfaceCount()) {
        const GND_SURFACE_FMT surface_fmt =
            gnd->GetSurface(cell_fmt.top_surface_id);
        GND_SURFACE *surface = &m_surfaces[cell_fmt.top_surface_id];

        surface->argb = surface_fmt.argb;
        surface->tex = g_TexMgr->GetTexture(
            gnd->GetTextureName(surface_fmt.texture_id), false);
        if (surface->tex) {
          unsigned long tex_width = surface->tex->GetWidth();
          unsigned long tex_height = surface->tex->GetHeight();
          unsigned long tex_uwidth = surface->tex->GetUpdateWidth();
          unsigned long tex_uheight = surface->tex->GetUpdateHeight();
          float r_width = (tex_uwidth / tex_width);
          float r_height = (tex_uheight / tex_height);

          surface->vertex[0].uv =
              vec2(r_width * surface_fmt.u[0], r_height * surface_fmt.v[0]);
          surface->vertex[1].uv =
              vec2(r_width * surface_fmt.u[1], r_height * surface_fmt.v[1]);
          surface->vertex[2].uv =
              vec2(r_width * surface_fmt.u[2], r_height * surface_fmt.v[2]);
          surface->vertex[3].uv =
              vec2(r_width * surface_fmt.u[3], r_height * surface_fmt.v[3]);
        }

        surface->vertex[0].vert =
            vec3(coord_x * m_zoom, cell->h[0], coord_y * m_zoom);
        surface->vertex[1].vert =
            vec3((coord_x + 1) * m_zoom, cell->h[1], coord_y * m_zoom);
        surface->vertex[2].vert =
            vec3(coord_x * m_zoom, cell->h[2], (coord_y + 1) * m_zoom);
        surface->vertex[3].vert =
            vec3((coord_x + 1) * m_zoom, cell->h[3], (coord_y + 1) * m_zoom);

        // if (g_is_lightmap) {
        //}
        // else {
        surface->lmtex = NULL;
        //}

        cell->top = surface;
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
        tlvertex3d vtex[4];

        vtex[0].x = cell.top->vertex[0].vert.x;
        vtex[0].y = cell.top->vertex[0].vert.y;
        vtex[0].z = cell.top->vertex[0].vert.z;
        vtex[0].texcoord.u = cell.top->vertex[0].uv.x;
        vtex[0].texcoord.v = cell.top->vertex[0].uv.y;

        vtex[1].x = cell.top->vertex[1].vert.x;
        vtex[1].y = cell.top->vertex[1].vert.y;
        vtex[1].z = cell.top->vertex[1].vert.z;
        vtex[1].texcoord.u = cell.top->vertex[1].uv.x;
        vtex[1].texcoord.v = cell.top->vertex[1].uv.y;

        vtex[2].x = cell.top->vertex[2].vert.x;
        vtex[2].y = cell.top->vertex[2].vert.y;
        vtex[2].z = cell.top->vertex[2].vert.z;
        vtex[2].texcoord.u = cell.top->vertex[2].uv.x;
        vtex[2].texcoord.v = cell.top->vertex[2].uv.y;

        vtex[3].x = cell.top->vertex[3].vert.x;
        vtex[3].y = cell.top->vertex[3].vert.y;
        vtex[3].z = cell.top->vertex[3].vert.z;
        vtex[3].texcoord.u = cell.top->vertex[3].uv.x;
        vtex[3].texcoord.v = cell.top->vertex[3].uv.y;

        CRPQuadFace *rp = g_Renderer->BorrowQuadRP();
        rp->SetGeomInfo(0, vtex[0]);
        rp->SetColorInfo(0, 0xFFFFFFFF);
        rp->SetGeomInfo(1, vtex[1]);
        rp->SetColorInfo(1, 0xFFFFFFFF);
        rp->SetGeomInfo(2, vtex[2]);
        rp->SetColorInfo(2, 0xFFFFFFFF);
        rp->SetGeomInfo(3, vtex[3]);
        rp->SetColorInfo(3, 0xFFFFFFFF);
        rp->set_texture(cell.top->tex);
        g_Renderer->AddRP(rp, 1);
      }
    }
  }
}
