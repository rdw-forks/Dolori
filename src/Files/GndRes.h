#ifndef DOLORI_RENDER_GNDRES_H_
#define DOLORI_RENDER_GNDRES_H_

#include <string>
#include <vector>

#include "Files/Res.h"

#pragma pack(push)
#pragma pack(1)

typedef struct _LightmapInfo {
  uint8_t idata[0x8][0x8];
  uint8_t sdata[0x8][0x8][0x3];
} LightmapInfo;

typedef struct _TileColor {
  uint8_t b;
  uint8_t g;
  uint8_t r;
  uint8_t a;
} TileColor;

typedef struct _GndSurfaceFmt {
  float u[0x4];
  float v[0x4];
  uint16_t texture_id;
  uint16_t lightmap_id;
  TileColor bgra;
} GndSurfaceFmt;

typedef struct _GndCellFmt {
  float height[4];
  int32_t top_surface_id;
  int32_t front_surface_id;
  int32_t right_surface_id;
} GndCellFmt;

struct COLOR_CHANNEL {
  uint8_t m_buffer[0x28];
};

#pragma pack(pop)

class CGndRes : public CRes {
 public:
  CGndRes();
  ~CGndRes();

  CRes *Clone() override;
  bool Load(const std::string &) override;

  float GetZoom() const;
  int32_t GetWidth() const;
  int32_t GetHeight() const;
  size_t GetSurfaceCount() const;
  const std::vector<LightmapInfo> &GetLightmaps() const;
  const GndSurfaceFmt &GetSurface(size_t index);
  const GndCellFmt &GetCell(unsigned int x, unsigned int y);
  const std::string &GetTextureName(size_t texture_id);
  const std::vector<std::string> &GetTextureNameTable() const;

 protected:
  void Reset() override;

 private:
  int32_t m_width;
  int32_t m_height;
  float m_zoom;
  std::vector<std::string> m_tex_name_table;
  std::vector<LightmapInfo> m_lightmaps;
  std::vector<GndSurfaceFmt> m_surfaces;
  std::vector<GndCellFmt> m_cells;
  COLOR_CHANNEL *m_colorchannel;
};

// class CGndRes {
//  CRes, offset = 0x0
//
//    public void CGndRes(const class CGndRes &)
//    public void CGndRes::CGndRes(class Exemplar, const char *, const char *)
//    public void CGndRes::CGndRes()
//    public class CRes * CGndRes::Clone()
//    public unsigned char CGndRes::Load(const char *)
//    public void CGndRes::Reset()
//    public unsigned char CGndRes::LoadGnd()
//    public void CGndRes::GetLMInfo(int, struct CLMInfo *)
//    public const char * GetTextureName(int)
//    public struct GndSurfaceFmt * GetSurface(int)
//    public const struct GndCellFmt17 & GetCells(int)
//   int m_newVer
//   unsigned char m_verMajor
//   unsigned char m_verMinor
//   int m_width
//   int m_height
//   float m_zoom
//   int m_numTexture
//   int m_numSurface
//   int m_numLightmap
//   class std::vector<char const *, std::allocator<char const *> >
//   m_texNameTable
//
//   struct CLMInfo * m_lminfo
//   struct LMIndex * m_lmindex
//   struct ColorChannel * m_colorchannel
//   struct GndSurfaceFmt * m_surface
//   struct GndCellFmt17 * m_V17cells
//   class CFile m_fp
//
//    public class CGndRes & operator=(const class CGndRes &)
//    public void CGndRes::~CGndRes()
//    public void __local_vftable_ctor_closure()
//    public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_RENDER_GNDRES_H_
