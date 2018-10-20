#ifndef DOLORI_UI_UIMAKECHARWND_H_
#define DOLORI_UI_UIMAKECHARWND_H_

#include "Common/character_info.h"
#include "Render/view_sprite.h"
#include "UI/UIBitmapEditCtrl.h"
#include "UI/UIFrameWnd.h"
#include "UI/UIStaticText.h"

class CUIMakeCharWnd : public CUIFrameWnd {
 public:
  CUIMakeCharWnd();

  void OnCreate(int x, int y) override;
  void OnDraw() override;
  void OnProcess() override;

  void InitTextControls();
  void MakeButton();
  void *SendMsg(CUIWindow *, int, void *val1 = nullptr, void *val2 = nullptr,
                void *val3 = nullptr, void *val4 = nullptr) override;

 private:
  CUIBitmapEditCtrl *m_nameEditCtrl;
  CharacterInfo m_charInfo;
  CharacterInfo m_charInfo2;
  VIEW_SPRITE m_viewChar;
  VIEW_SPRITE m_viewChar2;
  CUIStaticText *m_text[0x6];
};

// class UIMakeCharWnd {
//	UIFrameWnd, offset = 0x0
//
//		public void UIMakeCharWnd(const class UIMakeCharWnd &)
//		public void UIMakeCharWnd::UIMakeCharWnd()
//		public void UIMakeCharWnd::~UIMakeCharWnd()
//		public void UIMakeCharWnd::OnCreate(int, int)
//		public void UIMakeCharWnd::OnProcess()
//		public void UIMakeCharWnd::OnDestroy()
//		public void UIMakeCharWnd::OnDraw()
//		public int UIMakeCharWnd::SendMsg(class UIWindow *, int, int,
// int,
// int, int) 		public void UIMakeCharWnd::MakeButton()
// public void UIMakeCharWnd::InitTextControls() 		public void
// UIMakeCharWnd::DrawHexagon()
//		/* this+0x60 */ class UIBitmapEditCtrl * m_nameEditCtrl
//		/* this+0x64 */ struct CHARACTER_INFO m_charInfo
//
//		/* this+0xd0 */ struct CHARACTER_INFO m_charInfo2
//
//		/* this+0x13c */ struct viewSprite m_viewChar
//
//		/* this+0x228 */ struct viewSprite m_viewChar2
//
//		/* this+0x314 */ class UIStaticText *[0x6] m_text
//		public class UIMakeCharWnd & operator=(const class UIMakeCharWnd
//&) 		public void __local_vftable_ctor_closure() 		public
// void *
//__vecDelDtor(unsigned int)
//}

#endif  // DOLORI_UI_UIMAKECHARWND_H_
