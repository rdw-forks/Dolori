#include "Mouse.h"
#include "../Common/GetTick.h"
#include "../Common/Globals.h"

CMouse::CMouse() {}

CMouse::~CMouse() {}

void CMouse::Init() {
  m_xPos = 320;
  m_yPos = 240;
  m_oldBtnState[0] = BTN_NONE;
  m_oldBtnState[1] = BTN_NONE;
  m_oldBtnState[2] = BTN_NONE;
  m_btnState[0] = BTN_NONE;
  m_btnState[1] = BTN_NONE;
  m_btnState[2] = BTN_NONE;
  m_dblclkTime = 500;
  m_bSwapButton = 0;
}

void CMouse::ResetState() {
  m_xPos = g_3dDevice->GetWidth() / 2;
  m_yPos = g_3dDevice->GetHeight() / 2;
  m_xDelta = 0;
  m_yDelta = 0;
  ResetButtonState();
}

void CMouse::ResetButtonState() {
  for (int i = 0; i < 3; i++) m_btnState[i] = BTN_NONE;
  for (int i = 0; i < 3; i++) m_oldBtnState[i] = BTN_NONE;
}

void CMouse::SetXPos(int x) {
  m_xDelta = m_xPos - x;
  m_xPos = x;
}

int CMouse::GetXPos() { return m_xPos; }

void CMouse::SetYPos(int y) {
  m_yDelta = m_yPos - y;
  m_yPos = y;
}

int CMouse::GetYPos() { return m_yPos; }

void CMouse::SetLBtn(MOUSE_BTN_STATE state) {
  m_oldBtnState[BTN_LEFT] = m_btnState[BTN_LEFT];
  m_btnState[BTN_LEFT] = state;
}

MOUSE_BTN_STATE CMouse::GetLBtn() { return m_btnState[BTN_LEFT]; }

void CMouse::SetRBtn(MOUSE_BTN_STATE state) {
  m_oldBtnState[BTN_RIGHT] = m_btnState[BTN_RIGHT];
  m_btnState[BTN_RIGHT] = state;
}

MOUSE_BTN_STATE CMouse::GetRBtn() { return m_btnState[BTN_RIGHT]; }

void CMouse::SetWBtn(MOUSE_BTN_STATE state) {
  m_oldBtnState[BTN_WHEEL] = m_btnState[BTN_WHEEL];
  m_btnState[BTN_WHEEL] = state;
}

MOUSE_BTN_STATE CMouse::GetWBtn() { return m_btnState[BTN_WHEEL]; }

void CMouse::SetButtonPressed(MOUSE_BTN id) {
  if (id > 2) return;
  m_oldBtnState[id] = m_btnState[id];
  m_btnState[id] = BTN_PRESSED;
}

void CMouse::ReadState() {}