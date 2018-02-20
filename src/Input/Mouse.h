#ifndef DOLORI_INPUT_MOUSE_H_
#define DOLORI_INPUT_MOUSE_H_

class CMouse {
 public:
  enum ButtonState {
    kNone = 0,
    kDown = 1,
    kPressed = 2,
    kUp = 3,
    kDbClick = 4
  };

  enum Button { kLeft = 0, kRight = 1, kWheel = 2 };

  CMouse();
  ~CMouse();

  void Init();
  void ResetState();
  void ResetButtonState();
  void SetXPos(int);
  int GetXPos();
  void SetYPos(int);
  int GetYPos();
  void SetWheel(int wheel);
  int GetWheel();
  void SetLBtn(ButtonState);
  ButtonState GetLBtn();
  void SetRBtn(ButtonState);
  ButtonState GetRBtn();
  void SetWBtn(ButtonState);
  ButtonState GetWBtn();
  void SetButtonPressed(Button);
  void ReadState();

 private:
  void* m_hevtMouse;
  int m_xDelta;
  int m_yDelta;
  int m_xPos;
  int m_yPos;
  int m_wheel;
  ButtonState m_oldBtnState[0x3];
  ButtonState m_btnState[0x3];
  int m_dblclkCnt[0x3];
  int m_dblclkTime;
  int m_bSwapButton;
};

// class CMouse {
//  public void CMouse()
//    public void CMouse::Init()
//    public void CMouse::Exit()
//    public void CMouse::ReadState()
//    public void CMouse::ResetState()
//    public void CMouse::ResetButtonState()
//    public int GetWheel()
//    public int GetXPos()
//    public int GetYPos()
//    public void SetXPos(int)
//    public void SetYPos(int)
//    public int GetXDelta()
//    public int GetYDelta()
//    public enum EBtnState GetLBtn()
//    public enum EBtnState GetRBtn()
//    public enum EBtnState GetWBtn()
//    public void SetLBtn(enum EBtnState)
//    public void SetRBtn(enum EBtnState)
//    public void SetWBtn(enum EBtnState)
//    public void SetButtonPressed(int)
//    /* this+0x0 */ struct IDirectInputA * m_lpdi
//    /* this+0x4 */ struct IDirectInputDeviceA * m_pMouse
//    /* this+0x8 */ void * m_hevtMouse
//    /* this+0xc */ int m_xDelta
//    /* this+0x10 */ int m_yDelta
//    /* this+0x14 */ int m_xPos
//    /* this+0x18 */ int m_yPos
//    /* this+0x1c */ int m_wheel
//    /* this+0x20 */ int[0x3] m_oldBtnState
//    /* this+0x2c */ enum EBtnState[0x3] m_btnState
//    /* this+0x38 */ int[0x3] m_dblclkCnt
//    /* this+0x44 */ int m_dblclkTime
//    /* this+0x48 */ int m_bSwapButton
//}

#endif  // DOLORI_INPUT_MOUSE_H_
