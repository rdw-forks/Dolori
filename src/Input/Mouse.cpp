#include "Input/Mouse.h"

#include "Common/GetTick.h"
#include "Common/Globals.h"

CMouse::CMouse() : m_oldBtnState(), m_btnState() {}

void CMouse::Init() {
  m_xPos = 320;
  m_yPos = 240;
  m_oldBtnState[0] = ButtonState::kNone;
  m_oldBtnState[1] = ButtonState::kNone;
  m_oldBtnState[2] = ButtonState::kNone;
  m_btnState[0] = ButtonState::kNone;
  m_btnState[1] = ButtonState::kNone;
  m_btnState[2] = ButtonState::kNone;
  m_dblclkTime = 500;
  m_bSwapButton = 0;
}

void CMouse::ResetState() {
  m_xPos = g_3dDevice->GetWidth() / 2;
  m_yPos = g_3dDevice->GetHeight() / 2;
  m_xDelta = 0;
  m_yDelta = 0;
  m_wheel = 0;
  ResetButtonState();
}

void CMouse::ResetButtonState() {
  for (int i = 0; i < 3; i++) {
    m_btnState[i] = ButtonState::kNone;
  }

  for (int i = 0; i < 3; i++) {
    m_oldBtnState[i] = ButtonState::kNone;
  }
}

void CMouse::SetXPos(int x) {
  m_xDelta = m_xPos - x;
  m_xPos = x;
}

int CMouse::GetXPos() const { return m_xPos; }

void CMouse::SetYPos(int y) {
  m_yDelta = m_yPos - y;
  m_yPos = y;
}

int CMouse::GetYPos() const { return m_yPos; }

void CMouse::SetWheel(int wheel) { m_wheel = wheel; }

int CMouse::GetWheel() const { return m_wheel; }

void CMouse::SetLBtn(ButtonState state) {
  m_oldBtnState[Button::kLeft] = m_btnState[Button::kLeft];
  m_btnState[Button::kLeft] = state;
}

CMouse::ButtonState CMouse::GetLBtn() const {
  return m_btnState[Button::kLeft];
}

void CMouse::SetRBtn(ButtonState state) {
  m_oldBtnState[Button::kRight] = m_btnState[Button::kRight];
  m_btnState[Button::kRight] = state;
}

CMouse::ButtonState CMouse::GetRBtn() const {
  return m_btnState[Button::kRight];
}

void CMouse::SetWBtn(ButtonState state) {
  m_oldBtnState[Button::kWheel] = m_btnState[Button::kWheel];
  m_btnState[Button::kWheel] = state;
}

CMouse::ButtonState CMouse::GetWBtn() const {
  return m_btnState[Button::kWheel];
}

void CMouse::SetButtonPressed(Button id) {
  if (id >= Button::kButtonsCount) {
    return;
  }

  m_oldBtnState[id] = m_btnState[id];
  m_btnState[id] = ButtonState::kPressed;
}

void CMouse::ReadState() {}
