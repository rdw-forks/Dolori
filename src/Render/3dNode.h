#ifndef DOLORI_RENDER_3DNODE_H_
#define DOLORI_RENDER_3DNODE_H_

#include <list>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "Files/3dNodeRes.h"
#include "Render/3dMesh.h"
#include "Render/Texture.h"

// Forward declaration
class C3dActor;

class C3dNode {
 public:
  void AssignModel(C3dNodeRes* p_node_res);
  void Render(const glm::mat4*, int, unsigned char);

 private:
  C3dActor* m_master;
  std::string m_name;
  std::vector<CTexture*> m_textures;
  std::list<C3dNode*> m_children;
  C3dMesh* m_mesh;
  float m_opacity;
};

// class C3dNode {
//    *
//  public void C3dNode::Render(const struct matrix &, int, unsigned char)
//  public void C3dNode::AssignModel(struct C3dNodeRes *)
//  public void C3dNode::UpdateVertexColor(const struct matrix &, const struct
//  vector3d &, const struct vector3d &, const struct vector3d &, int)
//  protected void C3dNode(const class C3dNode &)
//  protected void C3dNode::C3dNode()
//  protected void C3dNode::~C3dNode()
//  protected void C3dNode::Reset()
//  protected void C3dNode::SetFrame(int)
//  protected void C3dNode::UpdateBound(struct C3dAABB *, const struct matrix &)
//  protected void C3dNode::UpdateAABB(const struct matrix &, const struct
//  matrix &)
//  protected void C3dNode::CheckAABB(const class CRayPicker &)
//  protected void C3dNode::UpdateDestVertColor(class CRenderer *, const struct
//  matrix &, class C3dGround15 *)
//  protected class C3dNode * C3dNode::FindNode(const char *)
//  protected void C3dNode::SetToAlpha()
//  /* this+0x4 */ class C3dActor * m_master
//  /* this+0x8 */ char[0x80] m_name
//  /* this+0x88 */ int m_numTexture
//  /* this+0x8c */ class std::vector<CTexture *,std::allocator<CTexture *> >
//  m_texture

//  /* this+0x9c */ class C3dMesh * m_mesh
//  /* this+0xa0 */ float m_opacity
//  /* this+0xa4 */ class C3dNode * m_parent
//  /* this+0xa8 */ class std::list<C3dNode *,std::allocator<C3dNode *> >
//  m_child

//  /* this+0xb4 */ struct matrix m_ltm

//  /* this+0xe4 */ class C3dPosAnim m_posAnim

//  /* this+0xf4 */ class C3dRotAnim m_rotAnim

//  /* this+0x104 */ class C3dScaleAnim m_scaleAnim

//    /* this+0x114 */ class
//    std::vector<C3dNode::ColorInfo,std::allocator<C3dNode::ColorInfo> >
//    m_colorInfo

//  /* this+0x124 */ int m_isAlphaForPlayer
//  /* this+0x128 */ struct C3dAABB m_aabb

//  /* this+0x140 */ class std::vector<int,std::allocator<int> > m_destVertCol

//  public class C3dNode & operator=(const class C3dNode &)
//  public void __local_vftable_ctor_closure()
//  protected void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_RENDER_3DNODE_H_
