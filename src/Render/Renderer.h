#ifndef DOLORI_RENDER_RENDERER_H_
#define DOLORI_RENDER_RENDERER_H_

#include <list>
#include <vector>
#include "../Common/Vector3d.h"
#include "../Render/RPFace.h"
#include "../Render/RPQuadFace.h"
#include "../Render/RPTriFace.h"
#include "pixel_format.h"

class CRenderer {
 public:
  CRenderer();

  void SetSize(int, int);
  int GetWidth();
  int GetHeight();
  void SetPixelFormat(PIXEL_FORMAT);
  void DestroyAllRPList();
  void Clear(bool clearScreen);
  void ClearBackground();
  bool DrawScene();
  void Flip();
  void FlushRenderList();
  void AddRP(CRPFace *, int);
  void DrawBoxScreen(int, int, int, int, unsigned int);

 private:
  void FlushAlphaNoDepthList();
  void FlushEmissiveNoDepthList();
  void FlushFaceList();
  //		private void CRenderer::FlushFaceList()
  //		private void CRenderer::FlushLMGroundList()
  //		private void CRenderer::FlushLMLightList()
  //		private void CRenderer::FlushAlphaDepthList()
  //		private void CRenderer::FlushAlphaList()
  //		private void CRenderer::FlushAlphaNoDepthList()
  //		private void CRenderer::FlushEmissiveDepthList()
  //		private void CRenderer::FlushEmissiveList()
  //		private void CRenderer::FlushEmissiveNoDepthList()
  //		private void CRenderer::FlushRawList()
  //		private void CRenderer::FlushAlphaRawList()
  //		private void CRenderer::FlushEmissiveRawList()
  //		private void CRenderer::FlushEffectList()
  //		private void CRenderer::FlushBumpList()
  //		private void CRenderer::FlushLmList()

 private:
  float m_hpc;
  float m_vpc;
  float m_hratio;
  float m_vratio;
  float m_aspectRatio;
  float m_screenXFactor;
  float m_screenYFactor;
  int m_xoffset;
  int m_yoffset;
  int m_width;
  int m_height;
  int m_halfWidth;
  int m_halfHeight;
  int m_curFrame;
  int m_bRGBBitCount;
  unsigned long m_fpsFrameCount;
  unsigned long m_fpsStartTick;
  int m_isFoggy;
  int m_fogChanged;
  int m_isVertexFog;
  class CTexture *m_oldTexture;
  class CTexture *m_oldLmapTexture;
  float m_guardBandLeft;
  float m_guardBandRight;
  float m_guardBandTop;
  float m_guardBandBottom;
  int m_isShowInfo;
  CVector3d m_eyeVector;
  unsigned long m_nClearColor;
  unsigned long m_dwScreenWidth;
  unsigned long m_dwScreenHeight;
  PIXEL_FORMAT m_pf;
  void *m_lpSurfacePtr;
  long m_lPitch;
  std::vector<CRPFace *> m_rpFaceList;
  std::vector<CRPFace *> m_rpLMGroundList;
  std::vector<CRPFace *> m_rpLMLightList;
  std::vector<std::pair<float, CRPFace *>> m_rpAlphaDepthList;
  std::vector<std::pair<float, CRPFace *>> m_rpAlphaList;
  std::vector<std::pair<float, CRPFace *>> m_rpAlphaNoDepthList;
  std::vector<std::pair<float, CRPFace *>> m_rpEmissiveDepthList;
  std::vector<std::pair<float, CRPFace *>> m_rpEmissiveList;
  std::vector<std::pair<float, CRPFace *>> m_rpEmissiveNoDepthList;
  //
  //		 class std::vector<RPRaw *, std::allocator<RPRaw *> >
  // m_rpRawList
  //
  //		 class std::vector<RPRaw *, std::allocator<RPRaw *> >
  // m_rpRawAlphaList
  //
  //		 class std::vector<RPRaw *, std::allocator<RPRaw *> >
  // m_rpRawEmissiveList
  //
  std::vector<CRPFace *> m_rpAlphaOPList;
  //
  //		 class std::vector<RPLmFace *, std::allocator<RPLmFace *> >
  // m_rpLmList
  //
  //		 class std::vector<RPLmFace *, std::allocator<RPLmFace *> >
  // m_rpBumpFaceList
  //
  //		 class std::list<CacheSurface, std::allocator<CacheSurface>
  //>[0x10] m_cacheSurfaces 		 class std::list<CTexture *,
  // std::allocator<CTexture *> > m_unusedCacheSurfaces
  //
  std::list<CRPFace> m_rpNullFaceList;
  std::list<CRPFace>::iterator m_rpNullFaceListIter;
  std::list<CRPQuadFace> m_rpQuadFaceList;
  //
  //		 class std::list<RPQuadFace, std::allocator<RPQuadFace>
  //>::iterator m_rpQuadFaceListIter
  //
  //		 class std::list<RPLmQuadFace, std::allocator<RPLmQuadFace> >
  // m_rpLmQuadFaceList
  //
  //		 class std::list<RPLmQuadFace, std::allocator<RPLmQuadFace>
  //>::iterator m_rpLmQuadFaceListIter
  //
  std::vector<tlvertex3d> m_vertBuffer;
};

// class CRenderer {
//	public void CRenderer(const class CRenderer &)
//		public void CRenderer::CRenderer()
//		public void CRenderer::~CRenderer()
//		public void CRenderer::SetSize(int, int)
//		public void CRenderer::SetPixelFormat(enum PixelFormat)
//		public void CRenderer::SetTexture(class CTexture *)
//		public void CRenderer::SetLmapTexture(class CTexture *)
//		public void CRenderer::ReleaseCacheSurfaces()
//		public void CRenderer::CreateUnusedCacheSurfaces()
//		public void CRenderer::ReleaseUnusedCacheSurfaces()
//		public void CRenderer::UnloadRarelyUsedCaches()
//		public void CRenderer::DestroyAllRPList()
//		public void CRenderer::SetLookAt(struct vector3d &, struct
// vector3d &, struct vector3d &) 		public void
// CRenderer::SetLight(struct vector3d &, struct vector3d &, struct vector3d &)
//		public void CRenderer::Clear(int)
//		public void CRenderer::ClearBackground()
//		public void SetBackgroundColor(unsigned long)
//		public unsigned char CRenderer::DrawScene()
//		public int CRenderer::Lock()
//		public void CRenderer::Unlock()
//		public void CRenderer::Flip(unsigned char)
//		public void CRenderer::BackupFrame()
//		public void CRenderer::RestoreFrame()
//		public int CRenderer::SaveBmp(const char *, class CBitmapRes *)
//		public int CRenderer::SaveJPG(const char *, class CBitmapRes *)
//		public void CRenderer::ScreenEffect()
//		public void CRenderer::DrawAgeRate()
//		public void CRenderer::DrawBattleFieldIcon()
//		public void CRenderer::ProjectVertex(const struct vector3d &,
// const struct matrix &, struct tlvertex3d *) 		public void
// CRenderer::ProjectVertex(const struct vector3d &, const struct matrix &,
// float
//*, float *, float *) 		public float CRenderer::GetPixelRatio(float)
//		public float CRenderer::GetScreenXFactor()
//		public float CRenderer::GetScreenYFactor()
//		public void CRenderer::BuildRay(int, int, const struct vector3d
//&,  const struct matrix &, struct ray3d *) 		public struct RPFace &
// CRenderer::BorrowNullRP() 		public struct RPQuadFace &
// CRenderer::BorrowQuadRP() 		public struct RPLmQuadFace &
// CRenderer::BorrowLmQuadRP() 		public struct tlvertex3d *
// CRenderer::BorrowVerts(unsigned int) 		public void
// ResetBorrowedRP() 		public void CRenderer::AddRP(struct RPTriFace *,
// int) 		public void CRenderer::AddRP(struct RPFace *, int)
//		public void CRenderer::AddRawRP(struct RPRaw *, int)
//		public void CRenderer::AddLmRP(struct RPLmFace *, enum RfLmType)
//		public void CRenderer::FlushRenderList()
//		public class CTexture * CRenderer::AddSpriteIndex(struct SprImg
//&,  unsigned long *, struct CacheInfo *) 		public class CTexture *
// CRenderer::GetSpriteIndex(struct SprImg &, unsigned long, struct CacheInfo *)
//		public void CRenderer::DoFog()
//		public void CRenderer::FogSwitch(int)
//		public int FogFactor(float)
//		public void CRenderer::SetMultiTextureMode(int)
//		public int CRenderer::TextOutScreen(int, int, const char *,
// unsigned long, int, char) 		public void CRenderer::ShowInfo()
//		public void CRenderer::StartFPSCount()
//		public struct tagSIZE * CRenderer::GetTextSize(const char *,
// int,  int, int, unsigned char) 		 float m_hpc 		 float
// m_vpc 		 float m_hratio 		 float m_vratio
//		 float m_aspectRatio
//		 float m_screenXFactor
//		 float m_screenYFactor
//		 int m_xoffset
//		 int m_yoffset
//		 int m_width
//		 int m_height
//		 int m_halfWidth
//		 int m_halfHeight
//		 int m_curFrame
//		 int m_bRGBBitCount
//		 unsigned long m_fpsFrameCount
//		 unsigned long m_fpsStartTick
//		 int m_isFoggy
//		 int m_fogChanged
//		 int m_isVertexFog
//		 class CTexture * m_oldTexture
//		 class CTexture * m_oldLmapTexture
//		 float m_guardBandLeft
//		 float m_guardBandRight
//		 float m_guardBandTop
//		 float m_guardBandBottom
//		 int m_isShowInfo
//		 struct vector3d m_eyeVector
//
//		 unsigned long m_nClearColor
//		private void CRenderer::FlushFaceList()
//		private void CRenderer::FlushLMGroundList()
//		private void CRenderer::FlushLMLightList()
//		private void CRenderer::FlushAlphaDepthList()
//		private void CRenderer::FlushAlphaList()
//		private void CRenderer::FlushAlphaNoDepthList()
//		private void CRenderer::FlushEmissiveDepthList()
//		private void CRenderer::FlushEmissiveList()
//		private void CRenderer::FlushEmissiveNoDepthList()
//		private void CRenderer::FlushRawList()
//		private void CRenderer::FlushAlphaRawList()
//		private void CRenderer::FlushEmissiveRawList()
//		private void CRenderer::FlushEffectList()
//		private void CRenderer::FlushBumpList()
//		private void CRenderer::FlushLmList()
//		 struct IDirect3DDevice7 * m_device
//		 struct IDirectDrawSurface7 * m_lpSurface
//		 unsigned long m_dwScreenWidth
//		 unsigned long m_dwScreenHeight
//		 enum PixelFormat m_pf
//		 void * m_lpSurfacePtr
//		 long m_lPitch
//		 class std::vector<RPFace *, std::allocator<RPFace *> >
// m_rpFaceList
//
//		 class std::vector<RPFace *, std::allocator<RPFace *> >
// m_rpLMGroundList
//
//		 class std::vector<RPFace *, std::allocator<RPFace *> >
// m_rpLMLightList
//
//		 class std::vector<std::pair<float, RPFace *>,
// std::allocator<std::pair<float, RPFace *> > > m_rpAlphaDepthList
//
//		 class std::vector<std::pair<float, RPFace *>,
// std::allocator<std::pair<float, RPFace *> > > m_rpAlphaList
//
//		 class std::vector<std::pair<float, RPFace *>,
// std::allocator<std::pair<float, RPFace *> > > m_rpAlphaNoDepthList
//
//		 class std::vector<std::pair<float, RPFace *>,
// std::allocator<std::pair<float, RPFace *> > > m_rpEmissiveDepthList
//
//		 class std::vector<std::pair<float, RPFace *>,
// std::allocator<std::pair<float, RPFace *> > > m_rpEmissiveList
//
//		 class std::vector<std::pair<float, RPFace *>,
// std::allocator<std::pair<float, RPFace *> > > m_rpEmissiveNoDepthList
//
//		 class std::vector<RPRaw *, std::allocator<RPRaw *> >
// m_rpRawList
//
//		 class std::vector<RPRaw *, std::allocator<RPRaw *> >
// m_rpRawAlphaList
//
//		 class std::vector<RPRaw *, std::allocator<RPRaw *> >
// m_rpRawEmissiveList
//
//		 class std::vector<RPFace *, std::allocator<RPFace *> >
// m_rpAlphaOPList
//
//		 class std::vector<RPLmFace *, std::allocator<RPLmFace *> >
// m_rpLmList
//
//		 class std::vector<RPLmFace *, std::allocator<RPLmFace *> >
// m_rpBumpFaceList
//
//		 class std::list<CacheSurface, std::allocator<CacheSurface>
//>[0x10] m_cacheSurfaces 		 class std::list<CTexture *,
// std::allocator<CTexture *> > m_unusedCacheSurfaces
//
//		 class std::list<RPFace, std::allocator<RPFace> >
// m_rpNullFaceList
//
//		 class std::list<RPFace, std::allocator<RPFace> >::iterator
// m_rpNullFaceListIter
//
//		 class std::list<RPQuadFace, std::allocator<RPQuadFace> >
// m_rpQuadFaceList
//
//		 class std::list<RPQuadFace, std::allocator<RPQuadFace>
//>::iterator m_rpQuadFaceListIter
//
//		 class std::list<RPLmQuadFace, std::allocator<RPLmQuadFace> >
// m_rpLmQuadFaceList
//
//		 class std::list<RPLmQuadFace, std::allocator<RPLmQuadFace>
//>::iterator m_rpLmQuadFaceListIter
//
//		 class std::vector<tlvertex3d, std::allocator<tlvertex3d> >
// m_vertBuffer
//
//		public class CRenderer & operator=(const class CRenderer &)
//		public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_RENDER_RENDERER_H_
