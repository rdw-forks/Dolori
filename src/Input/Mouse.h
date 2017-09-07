#ifndef DOLORI_INPUT_MOUSE_H_
#define DOLORI_INPUT_MOUSE_H_

typedef enum MOUSE_BTN_STATE {
  BTN_NONE = 0x0,
  BTN_DOWN = 0x1,
  BTN_PRESSED = 0x2,
  BTN_UP = 0x3,
  BTN_DBLCLK = 0x4,
} MOUSE_BTN_STATE;

typedef enum MOUSE_BTN {
  BTN_LEFT = 0x0,
  BTN_RIGHT = 0x1,
  BTN_WHEEL = 0x2
} MOUSE_BTN;

class CMouse {
 public:
  CMouse();
  ~CMouse();

  void Init();
  void ResetState();
  void ResetButtonState();
  void SetXPos(int);
  int GetXPos();
  void SetYPos(int);
  int GetYPos();
  void SetLBtn(MOUSE_BTN_STATE);
  MOUSE_BTN_STATE GetLBtn();
  void SetRBtn(MOUSE_BTN_STATE);
  MOUSE_BTN_STATE GetRBtn();
  void SetWBtn(MOUSE_BTN_STATE);
  MOUSE_BTN_STATE GetWBtn();
  void SetButtonPressed(MOUSE_BTN);
  void ReadState();

 private:
  void* m_hevtMouse;
  int m_xDelta;
  int m_yDelta;
  int m_xPos;
  int m_yPos;
  int m_wheel;
  MOUSE_BTN_STATE m_oldBtnState[0x3];
  MOUSE_BTN_STATE m_btnState[0x3];
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
