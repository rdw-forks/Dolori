#ifndef DOLORI_FILES_3DNODERES_H_
#define DOLORI_FILES_3DNODERES_H_

#include <list>

#include "Render/Texture.h"

struct C3dNodeRes {
  char name[0x28];
  char parentname[0x28];
  class C3dModelRes *scene;
  C3dNodeRes *parent;
  std::list<C3dNodeRes *> children;
  class C3dMesh *mesh;
  std::vector<CTexture *> m_textures;
  float position[0x3];
  float rotaxis[0x3];
  float rotangle;
  float scale[0x3];
  unsigned char alpha;
  // class C3dPosAnim posanim;
  // class C3dRotAnim rotanim;
};

//    struct C3dNodeRes {
//     public void C3dNodeRes(const struct C3dNodeRes &)
//  public void C3dNodeRes::C3dNodeRes()
//  public void C3dNodeRes::~C3dNodeRes()
//  public void C3dNodeRes::Release()
//  /* this+0x0 */ char[0x80] name
//  /* this+0x80 */ char[0x80] parentname
//  /* this+0x100 */ class C3dModelRes * scene
//  /* this+0x104 */ struct C3dNodeRes * parent
//  /* this+0x108 */ class std::list<C3dNodeRes *,std::allocator<C3dNodeRes *> >
//  child

//  /* this+0x114 */ class C3dMesh * mesh
//  /* this+0x118 */ int numTexture
//  /* this+0x11c */ class CTexture * * texture
//  /* this+0x120 */ float[0x3] pos
//  /* this+0x12c */ float[0x3] rotaxis
//  /* this+0x138 */ float rotangle
//  /* this+0x13c */ float[0x3] scale
//  /* this+0x148 */ unsigned char alpha
//  /* this+0x14c */ class C3dPosAnim posanim

//  /* this+0x15c */ class C3dRotAnim rotanim

//  public struct C3dNodeRes & operator=(const struct C3dNodeRes &)
//  public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_FILES_3DNODERES_H_
