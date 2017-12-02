#include "3dGround.h"
#include "../Common/Globals.h"
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

void C3dGround::AssignGnd(CGndRes *gnd, vec3 *light, vec3 *diffuse_col,
                          vec3 *ambient_col) {
  m_width = gnd->GetWidth();
  m_height = gnd->GetHeight();
  m_zoom = gnd->GetZoom();

  m_cells.resize(m_width * m_height);
  for (unsigned int y = 0; y < m_height; y++) {
    for (unsigned int x = 0; x < m_width; x++) {
      const GND_CELL_FMT *cell_fmt = gnd->GetCell(x, y);
      unsigned int index = x + y * m_width;
      GND_CELL *cell = &m_cells[index];

      cell->h[0] = cell_fmt->height[0];
      cell->h[1] = cell_fmt->height[1];
      cell->h[2] = cell_fmt->height[2];
      cell->h[3] = cell_fmt->height[3];

      int coord_x = x - m_width / 2;
      int coord_y = y - m_height / 2;
      cell->water_vert[0] = vec3(coord_x * m_zoom, 0, coord_y * m_zoom);
      cell->water_vert[1] = vec3((coord_x + 1) * m_zoom, 0, coord_y * m_zoom);
      cell->water_vert[2] = vec3(coord_x * m_zoom, 0, (coord_y + 1) * m_zoom);
      cell->water_vert[3] =
          vec3((coord_x + 1) * m_zoom, 0, (coord_y + 1) * m_zoom);

      if (cell_fmt->top_surface_id > 0 &&
          cell_fmt->top_surface_id < gnd->GetSurfaceCount()) {
        const GND_SURFACE_FMT *surface_fmt =
            gnd->GetSurface(cell_fmt->top_surface_id);
        GND_SURFACE *surface = &m_surfaces[cell_fmt->top_surface_id];

        surface->argb.color = surface_fmt->argb.color;
        // surface->tex = g_TexMgr->GetTexture();
        unsigned long tex_width = surface->tex->GetWidth();
        unsigned long tex_height = surface->tex->GetHeight();
        unsigned long tex_uwidth = surface->tex->GetUpdateWidth();
        unsigned long tex_uheight = surface->tex->GetUpdateHeight();
        float r_width = (tex_uwidth / tex_width);
        float r_height = (tex_uheight / tex_height);

        surface->vertex[0].vert =
            vec3(coord_x * m_zoom, cell->h[0], coord_y * m_zoom);
        surface->vertex[1].vert =
            vec3((coord_x + 1) * m_zoom, cell->h[1], coord_y * m_zoom);
        surface->vertex[2].vert =
            vec3(coord_x * m_zoom, cell->h[2], (coord_y + 1) * m_zoom);
        surface->vertex[3].vert =
            vec3((coord_x + 1) * m_zoom, cell->h[3], (coord_y + 1) * m_zoom);

        surface->vertex[0].uv =
            vec2(r_width * surface_fmt->u[0], r_height * surface_fmt->v[0]);
        surface->vertex[1].uv =
            vec2(r_width * surface_fmt->u[1], r_height * surface_fmt->v[1]);
        surface->vertex[2].uv =
            vec2(r_width * surface_fmt->u[2], r_height * surface_fmt->v[2]);
        surface->vertex[3].uv =
            vec2(r_width * surface_fmt->u[3], r_height * surface_fmt->v[3]);

        // if (g_is_lightmap) {
        //}
        // else {
        surface->lmtex = NULL;
        //}
      }
    }
  }
}

void C3dGround::Render(mat4 *wtm, RECT_ *area, bool need_clip) {
  for (uint32_t y = area->bottom; y < area->top; y++) {
    for (uint32_t x = area->left; x < area->right; x++) {
      GND_CELL *cell = &m_cells[x + y * m_width];
      CRPFace rp;
      // rp.SetGeomInfo(0, NULL);
      g_Renderer->AddRP(&rp, 1);
    }
  }
}
