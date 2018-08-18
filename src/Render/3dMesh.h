#ifndef DOLORI_RENDER_3DMESH_H_
#define DOLORI_RENDER_3DMESH_H_

#include <vector>

#include <glm/vec3.hpp>

typedef struct _MeshVertex {
  float position[3];
  float normal[3];
  float face_normal[3];
  uint32_t color;
  float tex_coord[2];
} MeshVertex;

class C3dMesh {
 private:
  std::vector<MeshVertex> m_vertices;
  C3dMesh* m_parent;
  std::vector<int> m_shadeGroup[0x20];
};

// class C3dMesh {
//  public void C3dMesh(const class C3dMesh &)
//  public void C3dMesh::C3dMesh()
//  public void C3dMesh::~C3dMesh()
//  public void SetParent(class C3dMesh *)
//  public void C3dMesh::UpdateNormal()
//  public void C3dMesh::Release()
//  public void SortFace()
//  /* this+0x0 */ int m_numVert
//  /* this+0x4 */ int m_numFace
//  /* this+0x8 */ int m_numTVert
//  /* this+0xc */ struct vector3d * m_vert
//  /* this+0x10 */ struct vector3d * m_faceNormal
//  /* this+0x14 */ struct vector3d * m_vertNormal
//  /* this+0x18 */ struct tvertex3d * m_tvert
//  /* this+0x1c */ struct face3d * m_face
//  /* this+0x20 */ class C3dMesh * m_parent
//  /* this+0x24 */ class std::vector<int,std::allocator<int> >[0x20]
//  m_shadeGroup
//  /* this+0x224 */ class CDynamicVB m_vb

//  public class C3dMesh & operator=(const class C3dMesh &)
//  public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_RENDER_3DMESH_H_
