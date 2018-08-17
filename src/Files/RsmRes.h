#ifndef DOLORI_RENDER_RSMRES_H_
#define DOLORI_RENDER_RSMRES_H_

#include <string>
#include <vector>

#include "Files/Res.h"

typedef enum _SHADING_TYPE {
  SHADING_TYPE_NONE = 0,
  SHADING_TYPE_FLAT,
  SHADING_TYPE_SMOOTH
} SHADING_TYPE;

class CRsmRes : public CRes {
 public:
  CRsmRes();

  bool Load(const std::string& file_name) override;
  CRes* Clone() override;

 private:
  std::vector<std::string> m_textures;
  char name[0x50];
  int32_t m_shade_type;
  int32_t m_anim_len;
  uint8_t m_alpha;
  //  struct MaterialInfo * m_material;
  //  std::list<C3dNodeRes *> m_objectList;
  //  std::list<std::string> m_rootObjList;
  //  std::map<std::string, C3dMesh *> m_meshList;
};

#endif  // DOLORI_RENDER_RSMRES_H_

// class C3dModelRes {
//  CRes, offset = 0x0

//  public void C3dModelRes(const class C3dModelRes &)
//  public void C3dModelRes::C3dModelRes(class Exemplar, const char *, const
//  char *)
//  public void C3dModelRes::C3dModelRes()
//  public class CRes * C3dModelRes::Clone()
//  public unsigned char C3dModelRes::Load(const char *)
//  public void C3dModelRes::Reset()
//  public struct C3dNodeRes * C3dModelRes::FindNode(const char *)
//  public struct C3dNodeRes * GetFirstNode()
//  public const char * GetMaterialName(int, int)
//  public const char * GetMaterialName(int)
//  public int GetSubMtlCount(int)
//  public class C3dMesh * GetMesh(const class
//  std::basic_string<char,std::char_traits<char>,std::allocator<char> > &)
//  /* this+0x110 */ int m_numMaterials
//  /* this+0x114 */ struct MaterialInfo * m_material
//  /* this+0x118 */ class std::list<C3dNodeRes *,std::allocator<C3dNodeRes *> >
//  m_objectList

//  /* this+0x124 */ class
//  std::list<std::basic_string<char,std::char_traits<char>,std::allocator<char>
//  >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char>
//  > > > m_rootObjList

//  /* this+0x130 */ class
//  std::map<std::basic_string<char,std::char_traits<char>,std::allocator<char>
//  >,C3dMesh
//  *,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char>
//  > >,std::allocator<C3dMesh *> > m_meshList

//  /* this+0x140 */ char[0x50] name
//  /* this+0x190 */ int m_shadeType
//  /* this+0x194 */ int m_animLen
//  /* this+0x198 */ class std::list<CVolumeBox *,std::allocator<CVolumeBox *> >
//  m_volumeBoxList

//  /* this+0x1a4 */ unsigned char m_alpha
//  public class C3dModelRes & operator=(const class C3dModelRes &)
//  public void C3dModelRes::~C3dModelRes()
//  public void __local_vftable_ctor_closure()
//  public void * __vecDelDtor(unsigned int)
//}
