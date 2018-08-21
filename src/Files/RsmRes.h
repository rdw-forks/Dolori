#ifndef DOLORI_RENDER_RSMRES_H_
#define DOLORI_RENDER_RSMRES_H_

#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Files/3dNodeRes.h"
#include "Files/File.h"
#include "Files/Res.h"
#include "Render/3dMesh.h"

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

 protected:
  void Reset() override;

 private:
  void LoadNode(CFile& file, std::shared_ptr<C3dNodeRes> node);

 private:
  uint16_t m_version;
  char m_name[0x50];
  int32_t m_shading_type;
  int32_t m_anim_len;
  uint8_t m_alpha;
  std::vector<std::string> m_textures;
  //  struct MaterialInfo * m_material;
  std::list<std::shared_ptr<C3dNodeRes>> m_object_list;
  std::list<std::string> m_root_obj_list;
  std::map<std::string, C3dMesh*> m_mesh_list;
};

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

#endif  // DOLORI_RENDER_RSMRES_H_
