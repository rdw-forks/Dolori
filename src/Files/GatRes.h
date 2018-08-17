#ifndef DOLORI_RENDER_GATRES_H_
#define DOLORI_RENDER_GATRES_H_

#include <string>
#include <vector>

#include "Files/Res.h"

typedef struct ATTR_CELL {
  /* this+0x0 */ float h1;
  /* this+0x4 */ float h2;
  /* this+0x8 */ float h3;
  /* this+0xc */ float h4;
  /* this+0x10 */ int flag;
} ATTR_CELL;

class CGatRes : public CRes {
 public:
  CGatRes();
  ~CGatRes();

  CRes* Clone() override { return nullptr; }
  bool Load(const std::string&) override { return false; }

 private:
  int m_width;
  int m_height;
  int m_zoom;
  std::vector<ATTR_CELL> m_cells;
};

// class C3dAttr {
//  CRes, offset = 0x0
//
//    public void C3dAttr(const class C3dAttr &)
//    public void C3dAttr::C3dAttr(class Exemplar, const char *, const char *)
//    public void C3dAttr::C3dAttr()
//    public class CRes * C3dAttr::Clone()
//    public void C3dAttr::Create(int, int)
//    public unsigned char C3dAttr::Load(const char *)
//    public void C3dAttr::Reset()
//    public float C3dAttr::GetHeight(float, float)
//    public int C3dAttr::GetAttr(float, float)
//    public struct CAttrCell * GetCell(int, int)
//    public float C3dAttr::RayTest(const struct ray3d &, int, int)
//    public void C3dAttr::SetCellInfo(int, int, int)
//    public void C3dAttr::GetWorldPos(float, float, struct vector2d &)
//    public void ConvertToCellCoor(float, float, long &, long &)
//    public void C3dAttr::GetHeightMinMax(const struct tagRECT &, float &,
//    float &)
//    /* this+0x110 */ int m_width
//    /* this+0x114 */ int m_height
//    /* this+0x118 */ int m_zoom
//    /* this+0x11c */ class std::vector<CAttrCell, std::allocator<CAttrCell> >
//    m_cells
//
//    public class C3dAttr & operator=(const class C3dAttr &)
//    public void C3dAttr::~C3dAttr()
//    public void __local_vftable_ctor_closure()
//    public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_RENDER_GATRES_H_
