#ifndef DOLORI_RENDER_3DDEVICE_H_
#define DOLORI_RENDER_3DDEVICE_H_

#include <SDL.h>
#include "../Render/Surface.h"
#include "Renderer.h"

class C3dDevice {
 public:
  C3dDevice();
  long Init(uint32_t);
  long DestroyObjects();
  CRenderer* CreateRenderer(int);
  void DestroyRenderer(CRenderer*);
  long Clear(unsigned long);
  long ClearZBuffer();
  long ShowFrame();
  int GetWidth();
  int GetHeight();
  CSurface* CreateWallPaper(unsigned int, unsigned int);

 private:
  SDL_Window* m_sdlWnd;
  SDL_GLContext m_glCtx;
  unsigned long m_dwRenderWidth;
  unsigned long m_dwRenderHeight;
  // struct tagRECT m_rcScreenRect;
  // struct tagRECT m_rcViewportRect;
  int m_bIsFullscreen;
  int m_pfRShiftR;
  int m_pfRShiftL;
  int m_pfGShiftR;
  int m_pfGShiftL;
  int m_pfBShiftR;
  int m_pfBShiftL;
  int m_pfAShiftR;
  int m_pfAShiftL;
  unsigned long m_pfBitCount;
  unsigned long m_pfRBitMask;
  unsigned long m_pfGBitMask;
  unsigned long m_pfBBitMask;
  unsigned long m_pfABitMask;
  unsigned long m_dwMinTextureWidth;
  unsigned long m_dwMinTextureHeight;
  unsigned long m_dwMaxTextureWidth;
  unsigned long m_dwMaxTextureHeight;
  unsigned long m_dwMaxTextureAspectRatio;
  unsigned char m_bSupportBltStretch;
  unsigned char m_bSupportTextureSurface;
  float m_fMaterialDiffuseR;
  float m_fMaterialDiffuseG;
  float m_fMaterialDiffuseB;
  float m_fMaterialAmbientR;
  float m_fMaterialAmbientG;
  float m_fMaterialAmbientB;
};

// class C3dDevice {
//	public void C3dDevice::C3dDevice()
//		public void C3dDevice::~C3dDevice()
//		public long C3dDevice::Init(struct HWND__ *, struct _GUID *,
// struct _GUID *, struct _DDSURFACEDESC2 *, unsigned long)
//		public long C3dDevice::DestroyObjects()
//		public int IsFullscreen()
//		public void C3dDevice::EnableClipper(int)
//		public unsigned char C3dDevice::TestScreen()
//		public class CRenderer * C3dDevice::CreateRenderer()
//		public void C3dDevice::DestroyRenderer(class CRenderer *)
//		public class CDC * C3dDevice::CreateDCBuffer(unsigned long,
// unsigned long) 		public class CSurface *
// C3dDevice::CreateWallPaper(unsigned long, unsigned long)
//		public void C3dDevice::ConvertPalette(unsigned long *, const
// struct tagPALETTEENTRY *, int) 		public long
// C3dDevice::Clear(unsigned long) 		public long
// C3dDevice::ClearZBuffer() 		public long C3dDevice::RestoreSurfaces()
//		public long C3dDevice::ShowFrame(unsigned char)
//		public long C3dDevice::CloneFrame()
//		public unsigned short EncodePixel(int, int, int)
//		public int C3dDevice::DecodePixelR(unsigned short)
//		public int C3dDevice::DecodePixelG(unsigned short)
//		public int C3dDevice::DecodePixelB(unsigned short)
//		public int GetWidth()
//		public int GetHeight()
//		public int GetWindowBitCount()
//		public int EnableGDIObject(int)
//		public void C3dDevice::EnableMipmap()
//		public void C3dDevice::AdjustTextureSize(unsigned long *,
// unsigned  long *) 		public struct IDirectDraw7 * GetDirectDraw()
//		public struct IDirect3D7 * GetDirect3D()
//		public struct IDirect3DDevice7 * GetD3DDevice()
//		public struct IDirectDrawSurface7 * GetFrontBuffer()
//		public struct IDirectDrawSurface7 * GetBackBuffer()
//		public struct IDirectDrawSurface7 * GetRenderSurface()
//		public struct _D3DDeviceDesc7 GetDeviceDesc()
//		public struct _DDSURFACEDESC2 * GetFrameBufferDesc()
//		public unsigned char GetBltStretchState()
//		public unsigned long GetRBitMask()
//		public unsigned long GetGBitMask()
//		public unsigned long GetBBitMask()
//		public int GetRShiftR()
//		public int GetGShiftR()
//		public int GetBShiftR()
//		public int GetRShiftL()
//		public int GetGShiftL()
//		public int GetBShiftL()
//		public void C3dDevice::BackupFrame()
//		public void C3dDevice::RestoreFrame()
//		public void SetMaterialDiffuse(float, float, float)
//		public void SetMaterialAmbient(float, float, float)
//		public void GetMaterialDiffuse(float *, float *, float *)
//		public void GetMaterialAmbient(float *, float *, float *)
//		/* this+0x0 */ struct HWND__ * m_hWnd
//		/* this+0x4 */ unsigned long m_dwRenderWidth
//		/* this+0x8 */ unsigned long m_dwRenderHeight
//		/* this+0xc */ struct tagRECT m_rcScreenRect
//
//		/* this+0x1c */ struct tagRECT m_rcViewportRect
//
//		/* this+0x2c */ struct IDirectDrawSurface7 * m_pddsFrontBuffer
//		/* this+0x30 */ struct IDirectDrawSurface7 * m_pddsBackBuffer
//		/* this+0x34 */ struct IDirectDrawSurface7 * m_pddsRenderTarget
//		/* this+0x38 */ struct IDirectDrawSurface7 * m_pddsZBuffer
//		/* this+0x3c */ struct IDirect3DDevice7 * m_pd3dDevice
//		/* this+0x40 */ struct IDirectDraw7 * m_pDD
//		/* this+0x44 */ struct IDirect3D7 * m_pD3D
//		/* this+0x48 */ struct _D3DDeviceDesc7 m_ddDeviceDesc
//
//		/* this+0x134 */ unsigned long m_dwDeviceMemType
//		/* this+0x138 */ struct _DDPIXELFORMAT m_ddpfZBuffer
//
//		/* this+0x158 */ struct _DDSURFACEDESC2 m_ddsdFrameBuffer
//
//		/* this+0x1d4 */ int m_bIsFullscreen
//		/* this+0x1d8 */ int m_bIsGDIObject
//		/* this+0x1dc */ int m_windowBitCount
//		/* this+0x1e0 */ struct IDirectDrawSurface7 * m_pddsRenderBackup
//		private long C3dDevice::CreateZBuffer()
//		private long C3dDevice::CreateBuffers(struct _DDSURFACEDESC2 *,
// unsigned long) 		private long C3dDevice::CreateDirectDraw(struct
//_GUID *, unsigned long) 		private long
// C3dDevice::CreateDirect3D(struct _GUID *, unsigned long) 		private
// long C3dDevice::CreateEnvironment(struct _GUID *, struct _GUID *, struct
//_DDSURFACEDESC2 *, unsigned long) 		private long
// C3dDevice::FlipToGDISurface(int)
//		/* this+0x1e4 */ int m_pfRShiftR
//		/* this+0x1e8 */ int m_pfRShiftL
//		/* this+0x1ec */ int m_pfGShiftR
//		/* this+0x1f0 */ int m_pfGShiftL
//		/* this+0x1f4 */ int m_pfBShiftR
//		/* this+0x1f8 */ int m_pfBShiftL
//		/* this+0x1fc */ int m_pfAShiftR
//		/* this+0x200 */ int m_pfAShiftL
//		/* this+0x204 */ unsigned long m_pfBitCount
//		/* this+0x208 */ unsigned long m_pfRBitMask
//		/* this+0x20c */ unsigned long m_pfGBitMask
//		/* this+0x210 */ unsigned long m_pfBBitMask
//		/* this+0x214 */ unsigned long m_pfABitMask
//		/* this+0x218 */ unsigned long m_dwMinTextureWidth
//		/* this+0x21c */ unsigned long m_dwMinTextureHeight
//		/* this+0x220 */ unsigned long m_dwMaxTextureWidth
//		/* this+0x224 */ unsigned long m_dwMaxTextureHeight
//		/* this+0x228 */ unsigned long m_dwMaxTextureAspectRatio
//		/* this+0x22c */ unsigned char m_bSupportBltStretch
//		/* this+0x22d */ unsigned char m_bSupportTextureSurface
//		/* this+0x230 */ float m_fMaterialDiffuseR
//		/* this+0x234 */ float m_fMaterialDiffuseG
//		/* this+0x238 */ float m_fMaterialDiffuseB
//		/* this+0x23c */ float m_fMaterialAmbientR
//		/* this+0x240 */ float m_fMaterialAmbientG
//		/* this+0x244 */ float m_fMaterialAmbientB
//		public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_RENDER_3DDEVICE_H_