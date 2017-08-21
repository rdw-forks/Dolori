#ifndef DOLORI_CORE_UIWINDOWMGR_H_
#define DOLORI_CORE_UIWINDOWMGR_H_

#include <string>
#include "../Render/BitmapRes.h"
#include "../Render/Surface.h"

class CUIWindowMgr {
 public:
  CUIWindowMgr();
  ~CUIWindowMgr();

  void SetSize(int, int);
  void SetWallpaper(CBitmapRes*);
  void RenderWallPaper();

 private:
  int m_chatWndX;
  int m_chatWndY;
  int m_chatWndHeight;
  int m_chatWndShow;
  int m_gronMsnWndShow;
  int m_gronMsgWndShow;
  int m_chatWndStatus;
  float m_miniMapZoomFactor;
  unsigned long m_miniMapArgb;
  int m_isDrawCompass;
  int m_isDragAll;
  int m_conversionMode;
  bool m_isInvalidatedByForce;
  unsigned char m_chatWndStickOn;
  unsigned char m_onStSubChat;
  unsigned char m_onBtSubChat;
  int m_lastMouseX;
  int m_lastMouseY;
  int m_modalResult;
  CSurface* m_wallpaperSurface;
  int m_w;
  int m_h;
  std::string m_wallPaperBmpName;
  short T_Logo_X;
  short T_Logo_Y;
  short T_Char_X;
  short T_Char_Y;
  short T_Tape_Y;
  short T_12Age_X;
  short T_12Age_Y;
  short T_Grav_X;
  short T_Grav_Y;
  short T_Intel_X;
  short T_Intel_Y;
  char T_CLICK;
};

#endif  // DOLORI_CORE_UIWINDOWMGR_H_
