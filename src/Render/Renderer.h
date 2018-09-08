#ifndef DOLORI_RENDER_RENDERER_H_
#define DOLORI_RENDER_RENDERER_H_

#include <list>
#include <map>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "Files/SprRes.h"
#include "Render/GlProgram.h"
#include "Render/GlTexture.h"
#include "Render/Surface.h"
#include "Render/Texture.h"
#include "Render/VBO.h"
#include "Render/pixel_format.h"

typedef struct _VertexP2T2 {
  float position[2];
  float texture_coord[2];
} VertexP2T2;

typedef struct _VertexP3T2N3 {
  glm::vec3 position;
  glm::vec2 tex_coords;
  glm::vec3 normal;
} VertexP3T2N3;

typedef struct _RenderBlock3d {
  const float *modelview_matrix;
  const float *nodeview_matrix;
  GLuint gl_texture_id;
  std::shared_ptr<CGlVBO> vbo;
  size_t vbo_first_item;
  size_t vbo_item_count;
} RenderBlock3d;

typedef struct _WorldLightInfo {
  glm::vec3 light_dir;
  glm::vec3 diffuse_col;
  glm::vec3 ambient_col;
  float light_opacity;
} WorldLightInfo;

typedef struct _SurfaceCache {
  const SPR_IMG *id;
  const uint32_t *pal_id;
  CSurface *tex;
  uint32_t last_time;
} SurfaceCache;

class CRenderer {
 public:
  CRenderer();

  bool Init();
  void SetSize(int, int);
  int GetWidth() const;
  int GetHeight() const;
  float GetHorizontalRatio() const;
  float GetVerticalRatio() const;
  void SetPixelFormat(PIXEL_FORMAT);
  void DestroyAllRPList();
  void Clear(bool clearScreen);
  void ClearBackground();
  bool DrawScene();
  void Flip();
  void FlushRenderList();
  void AddSurface(CSurface *surface, const RECT &position);
  void AddWorldRenderBlock(RenderBlock3d *render_block);
  void DrawBoxScreen(int, int, int, int, unsigned int);
  CSurface *AddSpriteIndex(const SPR_IMG *img, const uint32_t *pal_id);
  CSurface *GetSpriteIndex(const SPR_IMG *img, const uint32_t *pal_id);
  const glm::mat4 &projection_matrix() const;
  const glm::mat4 &view_matrix() const;
  void SetViewMatrix(const glm::mat4 &matrix);
  RenderBlock3d *BorrowRenderBlock();
  void SetLightInfo(const WorldLightInfo &);

 private:
  void FlushSurfacesList();
  void FlushWorldRenderList();

 private:
  glm::mat4 m_projection_matrix;
  glm::mat4 m_2d_projection_matrix;
  glm::mat4 m_view_matrix;
  CGlProgram m_surface_program;
  CGlProgram m_world_program;
  CGlVBO m_surface_vbo;
  WorldLightInfo m_world_light_info;
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
  CTexture *m_oldTexture;
  CTexture *m_oldLmapTexture;
  float m_guardBandLeft;
  float m_guardBandRight;
  float m_guardBandTop;
  float m_guardBandBottom;
  int m_isShowInfo;
  glm::vec3 m_eyeVector;
  unsigned long m_nClearColor;
  unsigned long m_dwScreenWidth;
  unsigned long m_dwScreenHeight;
  PIXEL_FORMAT m_pf;
  void *m_lpSurfacePtr;
  long m_lPitch;
  std::vector<std::pair<CSurface *, RECT>> m_surfaces_list;
  std::list<std::unique_ptr<RenderBlock3d>>::iterator m_render_blocks_cursor;
  std::list<std::unique_ptr<RenderBlock3d>> m_render_blocks_pool;
  std::list<RenderBlock3d *> m_world_render_list;

  std::list<SurfaceCache> m_cache_surfaces[0x10];
  std::list<CTexture *> m_unused_cache_surfaces;
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
