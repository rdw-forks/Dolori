#ifndef DOLORI_RENDER_WORLD_H_
#define DOLORI_RENDER_WORLD_H_

#include <list>
#include <memory>
#include <vector>

#include "Files/GatRes.h"
#include "GameObject/Player.h"
#include "Modes/Mode.h"
#include "Render/3dActor.h"
#include "Render/3dGround.h"
#include "Render/SceneGraphNode.h"

class CWorld {
 public:
  CWorld();
  ~CWorld();

  void OnEnterFrame();
  void Render();
  const CPlayer& GetPlayer() const;

 private:
  CMode* m_cur_mode;
  std::list<CGameObject*> m_game_object_list;
  std::list<CGameActor*> m_actor_list;
  // std::list<CItem*> m_item_list;
  // std::list<CSkill*> m_skill_list;
  std::list<std::unique_ptr<C3dActor>> m_bg_obj_list;
  C3dGround m_ground;
  CPlayer m_player;
  CGatRes m_attr;
  long m_bgObjCount;
  long m_bgObjThread;
  bool m_isPKZone;
  bool m_isSiegeMode;
  bool m_isBattleFieldMode;
  bool m_isEventPVPMode;
  CSceneGraphNode m_root_node;
  CSceneGraphNode* m_calculated;
  float m_light_opacity;
  glm::vec3 m_light_dir;
  glm::vec3 m_diffuse_col;
  glm::vec3 m_ambient_col;
};

// class CWorld {
//  *
//    public void CWorld(const class CWorld &)
//    public void CWorld::CWorld()
//    public void CWorld::~CWorld()
//    public void CWorld::OnEnterFrame()
//    public void CWorld::MakeFixedActor()
//    public void CWorld::OnExitFrame()
//    public void CWorld::ProcessActors()
//    public void CWorld::RemoveGameObject(class CGameObject *)
//    public void CWorld::InitPlayer()
//    public int CWorld::CheckAttr(struct vector3d)
//    public int CWorld::CheckGround(struct vector3d)
//    public void CWorld::AdjustPos(struct vector3d &)
//    public void CWorld::AdjustPos2(struct vector3d &)
//    public float CWorld::CalcShadowHeight(struct vector3d &)
//    public struct SceneGraphNode * GetRootNode()
//    public void CWorld::GetServerCoor(float, float, int &, int &)
//    public void CWorld::GetClientCoor(float, float, float &, float &)
//    public void CWorld::GetClientCoor(int, int, float &, float &)
//    public void SetCellInfo(int, int, int)
//    public void CWorld::Add3DActorToWorld(class C3dActor *)
//    public void CWorld::WaitForThreadEnd()
//    public void SetPKZone(int)
//    public void SetSiegeMode(int)
//    public void SetBattleFieldMode(int)
//    public void SetEventPVPMode(int)
//    public int IsPKZone()
//    public int IsSiegeMode()
//    public int IsBattleFieldMode()
//    public int IsEventPVPMode()
//    public class CGameActor * CWorld::GetGameActorByAID(unsigned long)
//    public class CItem * CWorld::GetItemByAID(unsigned long)
//    public class CSkill * CWorld::GetSkillByAID(unsigned long)
//    public unsigned char CWorld::RemoveSkill(unsigned long)
//    public unsigned char CWorld::RemoveGameActor(class CGameObject *)
//    public unsigned char CWorld::RemoveGameActor(unsigned long)
//    public unsigned char CWorld::RemoveItem(unsigned long)
//    public void CWorld::RemoveGameActorAll()
//    public class CSkill * CWorld::MakeSkill(int, int, int)
//    public unsigned char CWorld::RemoveSkillbyJT(int)
//     class CMode * m_curMode
//     class std::list<CGameObject *, std::allocator<CGameObject
//    *> > m_gameObjectList
//
//     class std::list<CGameActor *, std::allocator<CGameActor *>
//    > m_actorList
//
//     class std::list<CItem *, std::allocator<CItem *> >
//    m_itemList
//
//     class std::list<CSkill *, std::allocator<CSkill *> >
//    m_skillList
//
//     class C3dGround * m_ground
//     class CPlayer * m_player
//     class C3dAttr * m_attr
//     class std::vector<C3dActor *, std::allocator<C3dActor *> >
//    m_bgObjList
//
//     long m_bgObjCount
//     long m_bgObjThread
//    private void CWorld::BuildSceneGraph()
//    private void CWorld::FreeSceneGraph()
//     int m_isPKZone
//     int m_isSiegeMode
//     int m_isBattleFieldMode
//     int m_isEventPVPMode
//     struct SceneGraphNode m_rootNode
//
//     struct SceneGraphNode * m_Calculated
//    public class CWorld & operator=(const class CWorld &)
//    public void __local_vftable_ctor_closure()
//    public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_RENDER_WORLD_H_
