#ifndef DOLORI_RENDER_VIEWFRUSTUM_H_
#define DOLORI_RENDER_VIEWFRUSTUM_H_

#include <list>

#include <glm/glm.hpp>

#include "Render/SceneGraphNode.h"

class CViewFrustum {
 public:
  CViewFrustum();
  ~CViewFrustum();

  void Build(float hratio, float vratio, const glm::mat4& view_matrix,
             CSceneGraphNode* root_node);

 private:
  std::list<CSceneGraphNode*> m_cubelet_list_total;
  std::list<CSceneGraphNode*> m_cubelet_list_partial;
  glm::vec4 m_planes[0x6];
  glm::vec3 m_plane_normals[0x6];
};

// class CViewFrustum {
//  public void CViewFrustum(const class CViewFrustum &)
//    public void CViewFrustum::CViewFrustum()
//    public void CViewFrustum::Free()
//    public void CViewFrustum::Build(float, float, const struct matrix &,
//    struct SceneGraphNode *) private void CViewFrustum::CullSceneNode(struct
//    SceneGraphNode *, int, unsigned char) private int
//    CViewFrustum::CheckAABBIntersect(struct SceneGraphNode *) private int
//    CViewFrustum::CheckOBBIntersect(const struct C3dOBB &)
//    /* this+0x0 */ class std::list<SceneGraphNode *,
//    std::allocator<SceneGraphNode *> > m_cubeletListTotal
//
//    /* this+0xc */ class std::list<SceneGraphNode *,
//    std::allocator<SceneGraphNode *> > m_cubeletListPartial
//
//    /* this+0x18 */ struct plane3d[0x6] m_planes
//    /* this+0x78 */ struct vector3d[0x6] m_planeNormals
//    public class CViewFrustum & operator=(const class CViewFrustum &)
//    public void CViewFrustum::~CViewFrustum()
//    public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_RENDER_VIEWFRUSTUM_H_
