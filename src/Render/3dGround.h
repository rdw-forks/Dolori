#ifndef DOLORI_RENDER_3DGROUND_H_
#define DOLORI_RENDER_3DGROUND_H_

#include <memory>

#include <glm/glm.hpp>

#include "Files/GatRes.h"
#include "Files/GndRes.h"
#include "Render/GlProgram.h"
#include "Render/Texture.h"
#include "Render/TextureAtlas.h"
#include "Render/VBO.h"

typedef struct _GndSurface {
  int offset;
  std::shared_ptr<CTexture> tex;
  std::shared_ptr<CTexture> lmtex;
  TileColor bgra;
  unsigned long alpha;
  int mtl_id;
} GndSurface;

typedef struct _GndCell {
  float h[0x4];
  glm::vec3 water_vert[0x4];
  GndSurface* top;
  GndSurface* right;
  GndSurface* front;
  int render_signature;
  unsigned char cell_color[0x3];
} GndCell;

class C3dGround {
 public:
  C3dGround();
  ~C3dGround();

  bool Init();
  void AssignGnd(CGndRes* gnd, glm::vec3* light, glm::vec3* diffuse_col,
                 glm::vec3* ambient_col);
  void UpdateTextureAtlas(const std::vector<std::string>& texture_names);
  void UpdateLightmap(const std::vector<LightmapInfo>& lightmaps);
  void Render(glm::mat4* wtm, RECT* area, bool need_clip);

 private:
  CGlProgram m_program;
  CGlVBO m_vbo;
  std::unique_ptr<CTextureAtlas> m_texture_atlas;
  std::unique_ptr<CTexture> m_lightmap;
  CGatRes* m_attr;
  int32_t m_width;
  int32_t m_height;
  float m_zoom;
  float m_water_level;
  int m_tex_anim_cycle;
  int m_wave_pitch;
  int m_wave_speed;
  int m_water_set;
  float m_wave_height;
  CTexture* m_water_tex;
  CTexture* m_p_bump_map;
  int m_water_cnt;
  int m_water_offset;
  int m_is_new_ver;
  std::vector<GndSurface> m_surfaces;
  std::vector<GndCell> m_cells;
};

// class C3dGround {
//  *
//    public void C3dGround(const class C3dGround &)
//    public void C3dGround::C3dGround()
//    public void C3dGround::~C3dGround()
//    public void C3dGround::Create(int, int)
//    public void C3dGround::AssignGnd(class CGndRes *, struct vector3d &,
//    struct vector3d &, struct vector3d &) public void C3dGround::Reset()
//    public void C3dGround::FlushGround(const struct matrix &)
//    public void C3dGround::RenderLod(const struct matrix &, const struct
//    tagRECT &, unsigned char) public void C3dGround::Render(const struct
//    matrix &, const struct tagRECT &, unsigned char) public void
//    C3dGround::GetHeightMinMax(int, int, float &, float &) public void
//    C3dGround::GetHeightMinMax(const struct tagRECT &, float &, float &)
//    public void C3dGround::CheckAlpha(const struct ray3d &, int, int, float)
//    public unsigned char C3dGround::IsNewVer()
//    public void C3dGround::CalcLmIntensityFloatRGBAll()
//    public int C3dGround::GetLmIntensityFloatRGBByGatCoor(int, int, float &,
//    float &, float &) public void C3dGround::ConvertToCellCoor(float, float,
//    long &, long &) public void C3dGround::UpdateWater() public void
//    C3dGround::SetWaterInfo(float, int, int, int, int, float) public void
//    C3dGround::RenderAttrTile(const struct matrix &, int, int, unsigned long)
//    public void C3dGround::SetGndRiseAmount(float, int, int)
//    public void C3dGround::RenderGroundTile(const struct matrix &, int, int,
//    unsigned long, class CTexture *, struct vector2d *) public unsigned char
//    C3dGround::GetGroundVertics(struct vector3d *, int, int) public class
//    CTexture * C3dGround::GetWaterTexture()
// class C3dAttr * m_attr
// int m_width
// int m_height
// float m_zoom
// class CLightmapMgr m_lightmapMgr
//
// int m_numSurfaces
// float m_waterLevel
// int m_texAnimCycle
// int m_wavePitch
// int m_waveSpeed
// int m_waterSet
// float m_waveHeight
// class CTexture * m_waterTex
// class CTexture * m_pBumpMap
// int m_waterCnt
// int m_waterOffset
// int m_isNewVer
//    public class C3dGround & operator=(const class C3dGround &)
//    public void __local_vftable_ctor_closure()
//    public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_RENDER_3DGROUND_H_
