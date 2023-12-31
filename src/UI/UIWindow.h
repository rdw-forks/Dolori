#ifndef DOLORI_UI_UIWINDOW_H_
#define DOLORI_UI_UIWINDOW_H_

#include <stdint.h>

#include <list>
#include <memory>

#include "Files/BitmapRes.h"
#include "Render/Surface.h"

// Forward declaration
class CUIWindowMgr;

typedef enum _WINDOW_MESSAGE {
  WM_BUTTON_PRESSED = 6,
  WM_SET_ACTION_BUTTON_OK = 80
} WINDOW_MESSAGE;

class CUIWindow {
 public:
  CUIWindow(CUIWindowMgr *p_window_mgr);
  virtual ~CUIWindow();

  void Create(int, int);

  int GetX() const;
  int GetY() const;
  int GetHeight() const;
  int GetWidth() const;
  virtual void Move(int, int);
  virtual void Resize(int, int);
  virtual void OnProcess() {}
  virtual void DoDraw(bool);
  virtual void OnDraw() {}
  virtual void OnCreate(int, int) {}
  virtual bool IsUpdateNeeded() const;
  virtual void OnBeginEdit();
  virtual void OnFinishEdit();
  virtual void *SendMsg(CUIWindow *, int message, const void *val1 = nullptr,
                        const void *val2 = nullptr, const void *val3 = nullptr,
                        const void *val4 = nullptr);
  void OnSize(int, int) {}
  bool IsShow() const;
  void SetShow(bool);
  void AddChild(CUIWindow *);
  void RemoveChild(CUIWindow *window);
  bool IsChildOf(CUIWindow *) const;
  void DrawBitmap(int, int, const CBitmapRes *, int);
  void DrawBox(int x, int y, int cx, int cy, uint32_t color);
  void ClearDC(uint32_t color);
  void DrawSurface();
  void InvalidateChildren();
  void Invalidate();
  void TextOutA(int x, int y, const std::string &text, size_t, int, int,
                unsigned int);
  void TextOutUTF8(int x, int y, const std::string &text, size_t textLen,
                   int fontType, int fontHeight, unsigned int colorText);
  void TextOutWithOutline(int x, int y, const std::string &text, size_t,
                          uint32_t, uint32_t, int, int, bool);
  void TextOutWithDecoration(int x, int y, const std::string &text,
                             size_t textLen, unsigned int *colorRef,
                             int fontType, int fontHeight);
  static const char *InterpretColor(const char *color_text,
                                    unsigned int *colorRef);
  CUIWindow *HitTest(int x, int y);
  void SetId(size_t);
  size_t GetId() const;
  CUIWindow *GetParent() const;
  void GetGlobalCoor(int *, int *);
  virtual void OnLBtnDown(int, int) {}
  virtual void OnLBtnDblClk(int, int) {}
  virtual void OnRBtnDown(int, int) {}
  virtual void OnRBtnDblClk(int, int) {}
  virtual void OnWBtnDown(int, int) {}
  virtual void OnLBtnUp(int, int) {}
  virtual void OnRBtnUp(int, int) {}
  virtual void OnWBtnUp(int, int) {}
  virtual void OnMouseShape(int, int);
  virtual void OnMouseHover(int, int) {}
  virtual void OnMouseMove(int, int) {}

 protected:
  virtual bool ShouldDoHitTest();

 protected:
  CUIWindowMgr *p_window_mgr_;
  CUIWindow *m_parent;
  std::list<CUIWindow *> m_children;
  int m_x;
  int m_y;
  int m_w;
  int m_h;
  bool m_isDirty;
  std::unique_ptr<CSurface> m_surface;
  size_t m_id;
  size_t m_state;
  int m_state_cnt;
  bool m_show;
  unsigned long m_trans;
  unsigned long m_transTarget;
  unsigned long m_transTime;
};

// class UIWindow {
//  *
//    public void UIWindow(const class UIWindow &)
//    public void UIWindow::UIWindow()
//    public void UIWindow::~UIWindow()
//    public void UIWindow::Create(int, int)
//    public void UIWindow::Destroy()
//    public void UIWindow::AddChild(class UIWindow *)
//    public void UIWindow::RemoveChild(class UIWindow *)
//    public void UIWindow::RemoveAllChildren()
//    public void UIWindow::ClearAllChildrenState()
//    public void UIWindow::InvalidateChildren()
//    public void UIWindow::SetId(int)
//    public int GetId()
//    public int UIWindow::IsFamily(class UIWindow *)
//    public void UIWindow::Invalidate()
//    public void UIWindow::InvalidateWallPaper()
//    public class UIWindow * UIWindow::HitTest(int, int)
//    public void UIWindow::DoDraw(int)
//    public void UIWindow::Resize(int, int)
//    public unsigned char UIWindow::IsFrameWnd()
//    public unsigned char UIWindow::IsUpdateNeed()
//    public void UIWindow::Move(int, int)
//    public unsigned char UIWindow::CanGetFocus()
//    public unsigned char UIWindow::GetTransBoxInfo(struct BOXINFO *)
//    public unsigned char UIWindow::IsTransmitMouseInput()
//    public unsigned char UIWindow::ShouldDoHitTest()
//    public void UIWindow::DragAndDrop(int, int, const struct DRAG_INFO *
//    const) public void UIWindow::StoreInfo() public void
//    UIWindow::SaveOriginalPos() public void UIWindow::MoveDelta(int, int)
//    public unsigned char UIWindow::IsChildOf(class UIWindow *)
//    public class UIWindow * UIWindow::GetNextSiblingOf(class UIWindow *)
//    public class UIWindow * UIWindow::GetPrevSiblingOf(class UIWindow *)
//    public class UIWindow * UIWindow::GetAncestor()
//    public void UIWindow::GetGlobalCoor(int &, int &)
//    public int IsShow()
//    public unsigned long UIWindow::GetColor()
//    public void UIWindow::SetShow(int)
//    public void UIWindow::OnCreate(int, int)
//    public void UIWindow::OnDestroy()
//    public void UIWindow::OnProcess()
//    public void UIWindow::OnDraw()
//    public void UIWindow::OnDraw2()
//    public void UIWindow::OnRun()
//    public void UIWindow::OnSize(int, int)
//    public void UIWindow::OnBeginEdit()
//    public void UIWindow::OnFinishEdit()
//    public void UIWindow::OnLBtnDown(int, int)
//    public void UIWindow::OnLBtnDblClk(int, int)
//    public void UIWindow::OnMouseMove(int, int)
//    public void UIWindow::OnMouseHover(int, int)
//    public void UIWindow::OnMouseShape(int, int)
//    public void UIWindow::OnLBtnUp(int, int)
//    public void UIWindow::OnRBtnDown(int, int)
//    public void UIWindow::OnRBtnUp(int, int)
//    public void UIWindow::OnRBtnDblClk(int, int)
//    public void UIWindow::OnWheel(int)
//    public void UIWindow::RefreshSnap()
//    public int UIWindow::SendMsg(class UIWindow *, int, int, int, int, int)
//    public unsigned char UIWindow::GetTransBoxInfo2(struct BOXINFO *)
//    public void UIWindow::DrawBoxScreen2()
//    public int GetX()
//    public int GetY()
//    public int GetHeight()
//    public int GetWidth()
//    protected void UIWindow::DrawBitmap(int, int, class CBitmapRes *, unsigned
//    char) protected void UIWindow::TextOutA(int, int, const char *, int, int,
//    int, unsigned long) protected void UIWindow::TextOutWithRightAlign(int,
//    int, const char *, int, int, int, unsigned long) protected void
//    UIWindow::TextOutWithDecoration(int, int, const char *, int, unsigned long
//    *, int, int) protected void UIWindow::TextOutWithShadow(int, int, const
//    char *, int, unsigned long, unsigned long, int, int) protected void
//    UIWindow::TextOutWithOutline(int, int, const char *, int, unsigned long,
//    unsigned long, int, int, unsigned char) protected void
//    UIWindow::TextOutWithDecoOutline(int, int, const char *, int, unsigned
//    long *, unsigned long, int, int, unsigned char) protected void
//    UIWindow::TextOutVertical(int, int, const char *, int, int, int, unsigned
//    long) protected void UIWindow::TextOutWithOutlineVertical(int, int, const
//    char *, int, unsigned long, unsigned long, int, int, unsigned char)
//    protected void UIWindow::TextOutWithTwoColors(int, int, const char *,
//    unsigned long, unsigned long, int, int, int) protected int
//    UIWindow::GetTextWidth(const char *, int, int, int, unsigned char)
//    protected int UIWindow::GetTextHeight(const char *, int, int, int,
//    unsigned char) protected int UIWindow::GetTextHeightVertical(const char *,
//    int, int, int, unsigned char) protected int
//    UIWindow::GetColorTextWidth(const char *, int, int, int, unsigned char)
//    protected char * UIWindow::PolishText(const char *, int, int, int,
//    unsigned char) protected char * UIWindow::PolishText2(const char *, int)
//    protected void UIWindow::PolishText3(const char *, class
//    std::vector<std::string, std::allocator<std::string > > &, class
//    std::vector<bool, std::allocator<bool> > &, int) protected void
//    UIWindow::PolishText4(const char *, class std::vector<std::string,
//    std::allocator<std::string > > &, int) protected void
//    UIWindow::ClearDC(unsigned long) protected void
//    UIWindow::ClearDCRect(unsigned long, struct tagRECT &) protected void
//    UIWindow::DrawBox(int, int, int, int, unsigned long) protected void
//    UIWindow::DrawBorderLine(int, int, int, int, unsigned long) protected void
//    UIWindow::DrawTriangleDC(int, int, int, int, int, int, unsigned long)
//    protected const char * UIWindow::InterpretColor(const char *, unsigned
//    long *) protected const char * UIWindow::FindColorMark(const char *, const
//    char *)
//     class UIWindow * m_parent
//     class std::list<UIWindow *, std::allocator<UIWindow *> >
//    m_children
//
//     int m_x
//     int m_y
//     int m_w
//     int m_h
//     int m_isDirty
//     class CDC * m_dc
//     int m_id
//     int m_state
//     int m_stateCnt
//     int m_show
//     unsigned long m_trans
//     unsigned long m_transTarget
//     unsigned long m_transTime
//    public class UIWindow & operator=(const class UIWindow &)
//    public void __local_vftable_ctor_closure()
//    public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_UI_UIWINDOW_H_
