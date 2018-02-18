#ifndef DOLORI_RENDER_VIEW_H_
#define DOLORI_RENDER_VIEW_H_

#include <glm/glm.hpp>
#include "ViewFrustum.h"
#include "World.h"

struct VIEWINFO3D {
  glm::vec3 at;
  float latitude;
  float longitude;
  float distance;
};

class CView {
 public:
  CView();
  ~CView();

  void OnEnterFrame();
  void OnCalcViewInfo();
  void OnRender();

 private:
  float m_side_quake;
  float m_front_quake;
  float m_latitude_quake;
  bool m_is_FPS_mode;
  bool m_is_quake;
  unsigned long m_quake_start_tick;
  unsigned long m_quake_time;
  struct VIEWINFO3D m_cur;
  struct VIEWINFO3D m_dest;
  struct VIEWINFO3D m_backup_cur;
  struct VIEWINFO3D m_backup_dest;
  glm::vec3 m_from;
  glm::vec3 m_up;
  glm::mat4 m_view_matrix;
  glm::mat4 m_inv_view_matrix;
  CViewFrustum m_view_frustum;
  class CSkyBoxEllipse* m_skybox;
};

// class CView {
//  *
//    public void CView(const class CView &)
//    public void CView::CView()
//    public void CView::~CView()
//    public void CView::OnEnterFrame()
//    public void CView::OnExitFrame()
//    public void CView::OnRender()
//    public void CView::OnCalcViewInfo()
//    public float GetCurLongitude()
//    public float GetCurLatitude()
//    public float GetCurDistance()
//    public float GetDestLongitude()
//    public float GetDestLatitude()
//    public float GetDestDistance()
//    public struct vector3d GetCurAt()
//    public struct vector3d GetFrom()
//    public struct matrix GetViewMatrix()
//    public void SetDestLongitude(float)
//    public void SetDestDistance(float)
//    public void SetDestLatitude(float)
//    public void SetDestAt(float, float, float)
//    public void SetCurLongitude(float)
//    public void SetCurDistance(float)
//    public void SetCurLatitude(float)
//    public void SetCurAt(float, float, float)
//    public void AdjustDestLongitude(float)
//    public void HoldAt()
//    public void ResetLongitude(float)
//    public void ResetLatitude(float)
//    public void ResetDistance(float)
//    public void ResetAt(float, float, float)
//    public void PushCamera()
//    public void PopCamera()
//    public void CView::AddLongitude(float)
//    public void CView::AddLatitude(float)
//    public void CView::AddDistance(float)
//    public void CView::SetQuake(int, int, float, float, float)
//    public void CView::SetQuakeInfo(float, float, float)
//    public void CView::GetEeyeVector(struct vector3d *)
//    public struct vector3d * GetEeyeFromVector()
//    public unsigned char IsFPSmode()
//    protected void CView::InterpolateViewInfo()
//    protected void CView::ProcessQuake()
//    protected void CView::BuildViewMatrix()
//     float m_sideQuake
//     float m_frontQuake
//     float m_latitudeQuake
//     unsigned char m_isFPSmode
//     int m_isQuake
//     unsigned long m_quakeStartTick
//     unsigned long m_QuakeTime
//     struct ViewInfo3d m_cur
//
//     struct ViewInfo3d m_dest
//
//     struct ViewInfo3d m_backupCur
//
//     struct ViewInfo3d m_backupDest
//
//     struct vector3d m_from
//
//     struct vector3d m_up
//
//     struct matrix m_viewMatrix
//
//     struct matrix m_invViewMatrix
//
//     class CViewFrustum m_viewFrustum
//
//     class CWorld * m_world
//     class CSkyBoxEllipse * m_skyBox
//    public class CView & operator=(const class CView &)
//    public void __local_vftable_ctor_closure()
//    public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_RENDER_VIEW_H_
