#ifndef DOLORI_MODES_MODE_H_
#define DOLORI_MODES_MODE_H_

#include "../Common/Vector2d.h"

class CMode {
 public:
  CMode();
  ~CMode();

  bool GetLoopCond();
  void SetLoopCond(bool);

  virtual void OnInit(const char *);
  virtual int OnRun();
  virtual void OnExit();

 protected:
  int m_subMode;
  int m_subModeCnt;
  int m_nextSubMode;
  int m_fadeInCount;
  bool m_loopCond;
  int m_isConnected;
  class UITransBalloonText *m_helpBalloon;
  unsigned long m_helpBalloonTick;
  unsigned long m_mouseAnimStartTick;
  int m_isMouseLockOn;
  int m_screenShotNow;
  CVector2d m_mouseSnapDiff;
  int m_cursorActNum;
  int m_cursorMotNum;
};

// class CMode {
//	*
//		public void CMode(const class CMode &)
//		public void CMode::CMode()
//		public void CMode::~CMode()
//		public int CMode::OnRun()
//		public void CMode::OnInit(const char *)
//		public void CMode::OnExit()
//		public void CMode::OnUpdate()
//		public int CMode::SendMsg(int, int, int, int)
//		public void CMode::Initialize()
//		public void PostQuitMsg()
//		public void CMode::ScreenShot()
//		public void CMode::SetCursorAction(int)
//		public void CMode::RunFadeOut(int)
//		public void CMode::DrawSprite(int, int, class CActRes *, class
// CSprRes *, int, int, float, float, unsigned long) 		public void
// CMode::DrawTexture(struct tagRECT *, int, float, unsigned long, class
// CTexture
//*, struct UVRECT)
//		public void CMode::DrawBackGround2D(struct tagRECT *, int,
// float,  unsigned long, class CTexture *, struct UVRECT) 		public
// void  CMode::DrawMouseCursor() 		public void
// CMode::DrawBattleMode() 		public void CMode::MakeHelpBalloon(const
// char *, int, int,  unsigned long) 		public void
// CMode::ProcessHelpBalloon() 		public void CMode::ProcessFadeIn()
//		public void CMode::ProcessKeyBoard()
//		public int GetCursorAction()
//		public int GetCursorMotion()
//		public int GetSubMode()
//		public int GetLoopCond()
//		protected void CMode::OnChangeState(int)
//		protected void SetNextSubState(int)
//		protected void SetSubState(int)
//		int m_subMode
//		int m_subModeCnt
//		int m_nextSubMode
//		int m_fadeInCount
//		int m_loopCond
//		int m_isConnected
//		class UITransBalloonText * m_helpBalloon
//		unsigned long m_helpBalloonTick
//		unsigned long m_mouseAnimStartTick
//		int m_isMouseLockOn
//		int m_screenShotNow
//		struct vector2d m_mouseSnapDiff
//
//		int m_cursorActNum
//		int m_cursorMotNum
//		public class CMode & operator=(const class CMode &)
//		public void __local_vftable_ctor_closure()
//		public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_MODES_MODE_H_