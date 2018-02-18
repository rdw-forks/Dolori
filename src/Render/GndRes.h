#ifndef DOLORI_RENDER_GNDRES_H_
#define DOLORI_RENDER_GNDRES_H_

#include <vector>
#include "Files/File.h"
#include "Res.h"
#include "color.h"

#pragma pack(push)
#pragma pack(1)

typedef struct GND_HEADER {
  uint32_t magic;
  uint16_t version;
} GND_HEADER;

struct LM_INFO {
  uint8_t idata[0x8][0x8];
  uint8_t sdata[0x3][0x8][0x8];
};

struct LM_INDEX {
  uint32_t a;
  uint32_t r;
  uint32_t g;
  uint32_t b;
};

struct GND_SURFACE_FMT {
  float u[0x4];
  float v[0x4];
  uint16_t texture_id;
  uint16_t lightmap_id;
  COLOR argb;
};

struct GND_CELL_FMT {
  float height[4];
  int top_surface_id;
  int front_surface_id;
  int right_surface_id;
};

struct COLOR_CHANNEL {
  unsigned char m_buffer[0x28];
};

#pragma pack(pop)

class CGndRes : public CRes {
 public:
  CGndRes();
  ~CGndRes();

  CRes *Clone();
  bool Load(const char *);
  void Reset();
  float GetZoom();
  int GetWidth();
  int GetHeight();
  uint32_t GetSurfaceCount();
  const GND_SURFACE_FMT &GetSurface(unsigned int index);
  const GND_CELL_FMT &GetCell(unsigned int x, unsigned int y);
  const char * GetTextureName(int texture_id);

  static GND_SURFACE_FMT s_empty_surface;
  static GND_CELL_FMT s_empty_cell;

 private:
  // int m_new_ver;
  // unsigned char m_ver_major;
  // unsigned char m_ver_minor;
  int m_width;
  int m_height;
  float m_zoom;
  uint32_t m_num_textures;
  uint32_t m_num_lightmaps;
  uint32_t m_num_surfaces;
  uint32_t m_num_cells;
  std::vector<char const *> m_tex_name_table;
  struct LM_INFO *m_lminfo;
  struct LM_INDEX *m_lmindex;
  struct COLOR_CHANNEL *m_colorchannel;
  struct GND_SURFACE_FMT *m_surfaces;
  struct GND_CELL_FMT *m_cells;
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
