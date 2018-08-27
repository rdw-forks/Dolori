#ifndef DOLORI_RENDER_3DACTOR_H_
#define DOLORI_RENDER_3DACTOR_H_

#include <memory>

#include <glm/glm.hpp>

#include "Files/RsmRes.h"
#include "Render/GlTexture.h"

class C3dActor {
 public:
  C3dActor();

  void AssignModel(CRsmRes* p_rsm_res);
  void Render();
  void SetPos(const glm::vec3&);
  void SetRot(const glm::vec3&);
  void SetScale(const glm::vec3&);
  std::shared_ptr<CTexture> GetTexture(size_t id) const;
  const glm::mat4& GetModelViewMatrix() const;
  const glm::vec3& GetBbRange() const;
  const glm::vec3& GetBbMax() const;
  const glm::vec3& GetBbMin() const;

 private:
  std::shared_ptr<C3dNodeRes> m_root_node;
  glm::vec3 m_pos;
  glm::vec3 m_rot;
  glm::vec3 m_scale;
  bool m_matrix_needs_update;
  glm::mat4 m_modelview_matrix;
  SHADING_TYPE m_shading_type;
  std::vector<std::shared_ptr<CTexture>> m_textures;
  std::string m_name;
  int m_cur_motion;
  int m_anim_type;
  float m_anim_speed;
  int m_anim_len;
  glm::vec3 m_realbbmin;
  glm::vec3 m_realbbmax;
  glm::vec3 m_realbbrange;
  glm::vec3 m_bbmin;
  glm::vec3 m_bbmax;
  glm::vec3 m_bbrange;
};

// class C3dActor {
//  public void C3dActor(const class C3dActor &)
//  public void C3dActor::C3dActor()
//  public void C3dActor::~C3dActor()
//  public void OnInit()
//  public void C3dActor::Reset()
//  public void C3dActor::SetFrame(int)
//  public void SetPos(const struct vector3d &)
//  public void SetRot(const struct vector3d &)
//  public void SetScale(const struct vector3d &)
//  public void C3dActor::SetOpacity(float)
//  public void SetAnimType(int)
//  public struct vector3d GetPos()
//  public void C3dActor::OnProcess()
//  public void C3dActor::Render(struct matrix &, unsigned char, int)
//  public void C3dActor::AssignModel(class C3dModelRes *)
//  public void C3dActor::UpdateVertexColor(const struct vector3d &, const
//  struct vector3d &, const struct vector3d &)
//  public class C3dNode * FindNode(const char *)
//  public void C3dActor::SetVolumeBoxInfo(class std::list<CVolumeBox
//  *,std::allocator<CVolumeBox *> > *)
//  public int C3dActor::CheckCollision(const struct vector3d &)
//  public void C3dActor::AdjustCollision(struct vector3d &)
//  public void C3dActor::CalcShadowHeight(const struct vector3d &, float &)
//  public void C3dActor::CullByAABB(const class CRayPicker &)
//  public void C3dActor::CullByOBB(const struct lineSegment3d &)
//  public char * GetName()
//  public float GetAnimSpeed()
//  public int GetBlockType()
//  public int GetIsHideCheck()
//  public void SetName(char *)
//  public void SetAnimSpeed(float)
//  public void SetBlockType(int)
//  public void SetIsHideCheck(int)
//  public void HalfAlphaOn()
//  public void HalfAlphaOff()
//  public void ProcessFadeAlpha()
//  public unsigned char IsHalfAlpha()
//  public unsigned char GetFadeAlphaCnt()
//  /* this+0x0 */ struct vector3d m_pos

//  /* this+0xc */ struct vector3d m_rot

//  /* this+0x18 */ struct vector3d m_scale

//  /* this+0x24 */ int m_shadeType
//  /* this+0x28 */ class C3dNode * m_node
//  /* this+0x2c */ char[0x80] m_name
//  /* this+0xac */ int m_curMotion
//  /* this+0xb0 */ int m_animType
//  /* this+0xb4 */ float m_animSpeed
//  /* this+0xb8 */ int m_animLen
//  /* this+0xbc */ int m_isMatrixNeedUpdate
//  private void C3dActor::UpdateMatrix()
//  /* this+0xc0 */ struct matrix m_wtm

//  /* this+0xf0 */ struct matrix m_iwtm

//  /* this+0x120 */ struct vector3d m_posOffset

//  /* this+0x12c */ int m_isBbNeedUpdate
//  private void C3dActor::UpdateBound()
//  /* this+0x130 */ struct C3dOBB m_oBoundingBox

//  /* this+0x1cc */ struct C3dAABB m_aaBoundingBox

//  /* this+0x1e4 */ int m_renderSignature
//  /* this+0x1e8 */ int m_isHideCheck
//  /* this+0x1ec */ unsigned char m_isHalfAlpha
//  /* this+0x1ed */ unsigned char m_fadeAlphaCnt
//  /* this+0x1f0 */ int m_blockType
//  /* this+0x1f4 */ class std::list<CVolumeBox *,std::allocator<CVolumeBox *> >
//  m_volumeBoxList

//  public class C3dActor & operator=(const class C3dActor &)
//  public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_RENDER_3DACTOR_H_
