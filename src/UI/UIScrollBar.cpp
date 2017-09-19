#include "UIScrollBar.h"
#include "../Common/Globals.h"
#include "UIBmp.h"

CUIScrollBar::CUIScrollBar() {
  m_maxPos = 0;
  m_curPos = 0;
  m_drawMode = 0;
  m_startDragX = 0;
  m_startDragY = 0;
  m_deltaDrag = 0;
  m_parentNumItem = 0;
  m_parentnumCanDisplayItem = 0;
  m_scrollBtnSize = 13;
  m_isVert = true;
  m_fixedLength = 13;
  m_type = 1;
}

CUIScrollBar::~CUIScrollBar() {}

void CUIScrollBar::SetPos(int pos) { m_curPos = pos; }

int CUIScrollBar::GetPos() { return m_curPos; }

void CUIScrollBar::SetVert(bool is_vertical) { m_isVert = is_vertical; }

void CUIScrollBar::SetType(int type) { m_type = type; }

void CUIScrollBar::SetRange(int range, size_t parentnumCanDisplayItem,
                            size_t parentNumItem) {
  m_maxPos = range;
  m_parentnumCanDisplayItem = parentnumCanDisplayItem;
  m_parentNumItem = parentNumItem;
  Invalidate();
  if (m_curPos > m_maxPos) m_curPos = m_maxPos;
}

int CUIScrollBar::GetFixedLength() { return m_fixedLength; }

void CUIScrollBar::Resize(int cx, int cy) {
  Invalidate();
  if (m_isVert) {
    CUIWindow::Resize(m_fixedLength, cy);
    OnSize(m_fixedLength, cy);
  } else {
    CUIWindow::Resize(cx, m_fixedLength);
    OnSize(cx, m_fixedLength);
  }
}

void CUIScrollBar::OnDraw() {
  ClearDC(0);
  if (m_maxPos) {
    if (m_isVert) {
      CBitmapRes *bitmap;

      // Render top part of the scrollbar's background
      bitmap = (CBitmapRes *)g_ResMgr->Get(
          UIBmp("유저인터페이스/scroll0up.bmp"), false);
      DrawBitmap(0, 1, bitmap, 0);

      // Render middle part of the scrollbar's background
      int nb_of_elements = (m_h - m_scrollBtnSize - 14) / 13 +
                           ((m_h - m_scrollBtnSize - 14) % 13 != 0);
      if (nb_of_elements) {
        bitmap = (CBitmapRes *)g_ResMgr->Get(
            UIBmp("유저인터페이스/scroll0mid.bmp"), false);

        int offset_y = 0;
        for (int i = 0; i < nb_of_elements; i++) {
          DrawBitmap(0, m_scrollBtnSize + offset_y, bitmap, 0);
          offset_y += 13;
        }
      }

      // DrawBox(0, m_h - m_scrollBtnSize, m_w, 13, 0xFFFF00FF);
      // Render bottom part of the scrollbar's background
      bitmap = (CBitmapRes *)g_ResMgr->Get(
          UIBmp("유저인터페이스/scroll0down.bmp"), false);
      DrawBitmap(0, m_h - m_scrollBtnSize - 1, bitmap, 1);

      int y =
          m_scrollBtnSize + (m_h - 3 * m_scrollBtnSize) * m_curPos / m_maxPos;

      // Render top part of the scrollbar
      bitmap = (CBitmapRes *)g_ResMgr->Get(
          UIBmp("유저인터페이스/scroll0bar_up.bmp"), false);
      DrawBitmap(0, y, bitmap, 1);

      // Render middle part of the scrollbar
      bitmap = (CBitmapRes *)g_ResMgr->Get(
          UIBmp("유저인터페이스/scroll0bar_mid.bmp"), false);
      int current_y = y + 4;
      for (int current_y = y + 4; current_y < m_scrollBtnSize + y - 4;
           current_y += 4)
        DrawBitmap(0, current_y, bitmap, 1);

      // Render bottom part of the bar's scrollbar
      bitmap = (CBitmapRes *)g_ResMgr->Get(
          UIBmp("유저인터페이스/scroll0bar_down.bmp"), false);
      DrawBitmap(0, m_scrollBtnSize + y - 4, bitmap, 1);

    } else {
    }
  }
}

void CUIScrollBar::OnLBtnDown(int x, int y) {
  if (m_maxPos) {
    int hit = HitTest(x, y);
    m_startDragX = x;
    m_startDragY = y;
    m_deltaDrag = 0;

    if (m_isVert) {
      switch (hit) {
        case 0:
          m_parent->SendMsg(this, 7, (void *)-1, 0, 0, 0);
          break;
        case 1:
          m_parent->SendMsg(this, 9, 0, 0, 0, 0);
          break;
        case 2:
          g_WindowMgr->SetCapture(this);
          break;
        case 3:
          m_parent->SendMsg(this, 10, 0, 0, 0, 0);
          break;
        case 4:
          m_parent->SendMsg(this, 7, (void *)1, 0, 0, 0);
          break;
        default:
          return;
      };
    } else {
      switch (hit) {
        case 2:
          g_WindowMgr->SetCapture(this);
          break;
        case 0:
          m_parent->SendMsg(this, 8, (void *)-1, 0, 0, 0);
          break;
        case 1:
          m_parent->SendMsg(this, 11, 0, 0, 0, 0);
          break;
        case 3:
          m_parent->SendMsg(this, 12, 0, 0, 0, 0);
          break;
        case 4:
          m_parent->SendMsg(this, 8, (void *)1, 0, 0, 0);
          break;
        default:
          return;
      };
    }
  }
}

void CUIScrollBar::OnLBtnUp(int x, int y) {
  if (m_maxPos) {
    if (g_WindowMgr->GetCapture() == this) g_WindowMgr->ReleaseCapture();
  } else {
    m_parent->OnLBtnUp(x + m_x, y + m_y);
  }
}

void CUIScrollBar::OnMouseMove(int x, int y) {
  int previous_draw_mode;
  int pos_scroll_end;
  int scrollbar_length;
  size_t button_drag;

  if (!m_maxPos) {
    m_parent->OnMouseMove(x + m_x, y + m_y);
    return;
  }

  scrollbar_length = m_h;
  if (!m_isVert) scrollbar_length = m_w;
  if (scrollbar_length != 3 * m_scrollBtnSize) {
    previous_draw_mode = m_drawMode;
    switch (HitTest(x, y) + 1) {
      case 0:
      case 2:
      case 4:
        m_drawMode = 0;
        break;
      case 1:
        m_drawMode = 1;
        break;
      case 3:
        m_drawMode = 3;
        break;
      case 5:
        m_drawMode = 2;
        break;
      default:
        break;
    }
    if (previous_draw_mode != m_drawMode) Invalidate();

    if (g_WindowMgr->GetCapture() == this && m_parent) {
      if (!m_isVert) {
        pos_scroll_end = m_w - 3 * m_scrollBtnSize;
        if ((m_maxPos + 1) * (x - m_startDragX) / pos_scroll_end == m_deltaDrag)
          return;
        button_drag =
            (m_maxPos + 1) * (x - m_startDragX) / pos_scroll_end - m_deltaDrag;
        m_deltaDrag +=
            (size_t)m_parent->SendMsg(this, 8, (void *)button_drag, 0, 0, 0);
        return;
      } else {
        pos_scroll_end = m_h - 3 * m_scrollBtnSize;
        if ((m_maxPos + 1) * (y - m_startDragY) / pos_scroll_end !=
            m_deltaDrag) {
          button_drag = (m_maxPos + 1) * (y - m_startDragY) / pos_scroll_end -
                        m_deltaDrag;
          m_deltaDrag +=
              (size_t)m_parent->SendMsg(this, 7, (void *)button_drag, 0, 0, 0);
          return;
        }
      }
    }
  }
}

int CUIScrollBar::HitTest(int x, int y) {
  if (!m_maxPos) return -1;
  if (x < 0) return -1;
  if (x >= m_w) return -1;
  if (y < 0) return -1;
  if (y >= m_h) return -1;

  if (m_isVert) {
    if (y < m_scrollBtnSize) return 0;
    if (y < m_scrollBtnSize + (m_h - 3 * m_scrollBtnSize) * m_curPos / m_maxPos)
      return 1;
    if (y <
        2 * m_scrollBtnSize + (m_h - 3 * m_scrollBtnSize) * m_curPos / m_maxPos)
      return 2;
    return (y >= m_h - m_scrollBtnSize) + 3;
  } else {
    if (x < m_scrollBtnSize) return 0;
    if (x < m_scrollBtnSize + (m_w - 3 * m_scrollBtnSize) * m_curPos / m_maxPos)
      return 1;
    if (x <
        2 * m_scrollBtnSize + (m_w - 3 * m_scrollBtnSize) * m_curPos / m_maxPos)
      return 2;
    return (x >= m_w - m_scrollBtnSize) + 3;
  }
}