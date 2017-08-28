#ifndef DOLORI_RENDER_TEXMGR_H_
#define DOLORI_RENDER_TEXMGR_H_

#include <map>
#include "pixel_format.h"
#include "Texture.h"

class CTexMgr {
 public:
  CTexMgr();
  ~CTexMgr();

  CTexture *CreateTexture(unsigned long, unsigned long, PIXEL_FORMAT);

 private:
  //std::map<char const *, CTexture *, CharPrtLess> m_texTable;
};

// class CTexMgr {
//	public void CTexMgr(const class CTexMgr &)
//		public void CTexMgr::CTexMgr()
//		public void CTexMgr::~CTexMgr()
//		public class CTexture * CTexMgr::CreateTexture(int, int,
// unsigned  long *, enum PixelFormat, unsigned char) 		public class
// CTexture *  CTexMgr::CreateTexture(unsigned long, unsigned long, enum
// PixelFormat, struct  IDirectDrawSurface7 *) 		public void
// CTexMgr::ReCreateTexture(class CTexture *, int, int, unsigned long *)
//		public class CTexture * CTexMgr::GetTexture(const char *,
// unsigned
// char) 		public void CTexMgr::DestroyTexture(class CTexture *)
//		public void CTexMgr::DestroyAllTexture()
//		public void CTexMgr::ReloadAllTexture()
//		public void CTexMgr::UnloadRarelyUsedTexture()
//		public class CTexture * GetDummyTexture()
//		private class CTexture * CTexMgr::FindTexture(const char *)
//		private class CTexture * CTexMgr::LoadTexture(const char *,
// unsigned char) 		private void CTexMgr::AddTexture(class CTexture
//*)
//		/* this+0x0 */ class std::map<char const *, CTexture *,
// CharPrtLess, std::allocator<CTexture *> > m_texTable
//
//		/* [0x0003:0x0003daf0] */ static  class CTexture s_dummy_texture
//
//		public class CTexMgr & operator=(const class CTexMgr &)
//		public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_RENDER_TEXMGR_H_
