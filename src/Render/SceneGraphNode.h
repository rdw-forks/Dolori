#ifndef DOLORI_RENDER_SCENEGRAPHNODE_H_
#define DOLORI_RENDER_SCENEGRAPHNODE_H_

#include <glm/glm.hpp>
#include <vector>
#include "3dAttr.h"
#include "3dGround.h"

class CSceneGraphNode {
 public:
  CSceneGraphNode();
  ~CSceneGraphNode();

 private:
  CSceneGraphNode *m_parent;
  CSceneGraphNode *m_child[0x4];
  // struct C3dAABB m_aabb;
  glm::vec3 m_center;
  glm::vec3 m_halfSize;
  int m_needUpdate;
  // std::vector<C3dActor *> m_actor_list;
  C3dGround *m_ground;
  // struct tagRECT m_groundArea;
  C3dAttr *m_attr;
  // struct tagRECT m_attrArea;
};

// struct SceneGraphNode {
//  public void SceneGraphNode(const struct SceneGraphNode &)
//    public void SceneGraphNode::SceneGraphNode()
//    public void SceneGraphNode::~SceneGraphNode()
//    public void SceneGraphNode::Build(int)
//    public void SceneGraphNode::InsertObject(class C3dAttr *, int)
//    public void SceneGraphNode::InsertObject(class C3dGround *, int)
//    public void SceneGraphNode::InsertObject(class C3dActor *, int)
//    public void SceneGraphNode::RemoveObject(class C3dActor *, int)
//    public void SceneGraphNode::UpdateVolume(int)
//    public void SceneGraphNode::UpdateVolumeAfter(int)
//    public class std::vector<C3dActor *, std::allocator<C3dActor *> > *
//    SceneGraphNode::GetActorList(float, float, int)
//    /* this+0x0 */ struct SceneGraphNode * m_parent
//    /* this+0x4 */ struct SceneGraphNode *[0x4] m_child
//    /* this+0x14 */ struct C3dAABB m_aabb
//
//    /* this+0x2c */ struct vector3d m_center
//
//    /* this+0x38 */ struct vector3d m_halfSize
//
//    /* this+0x44 */ int m_needUpdate
//    /* this+0x48 */ class std::vector<C3dActor *, std::allocator<C3dActor *> >
//    m_actorList
//
//    /* this+0x58 */ class C3dGround * m_ground
//    /* this+0x5c */ struct tagRECT m_groundArea
//
//    /* this+0x6c */ class C3dAttr * m_attr
//    /* this+0x70 */ struct tagRECT m_attrArea
//
//    public void SceneGraphNode::InsertObjectAfter(class C3dActor *, int)
//    public void SceneGraphNode::CopySceneGraph(int, struct SceneGraphNode *)
//    public void SceneGraphNode::LoadSceneGraph(class CFile *, int)
//    public struct SceneGraphNode & operator=(const struct SceneGraphNode &)
//    public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_RENDER_SCENEGRAPHNODE_H_
