#ifndef DOLORI_INPUT_LANGUAGE_H_
#define DOLORI_INPUT_LANGUAGE_H_

#include <string>

class CLanguage {
 public:
  CLanguage();
  ~CLanguage();

  void AddInput(const std::string& input);
  void ResetInput();
  void SetSelection(int, int);
  int GetInputSize() const;
  std::string GetLanguageText() const;
  void HideText(bool);
  void OnKeyDown(unsigned int, long);

 private:
  std::string m_input;
  int m_inputCursor;
  int m_selectionCursor;
  int m_selectionOrigin;
  std::string m_keyStroke;
  std::string m_compStr;
  int m_compCursorPos;
  bool m_bHideText;
  unsigned short m_langId;
  unsigned int m_codePage;
  int m_underLineStart;
  int m_underLineEnd;
  std::string m_languageFolder;
  unsigned short m_scriptLangId;
  // class std::deque<unsigned long, std::allocator<unsigned long> > m_fakeInput
  // struct tagCANDIDATELIST * m_candidateList
  // int m_candidateCount
  // int m_candidatePageSize
  // int m_candidateSelection
  // class std::vector<unsigned char, std::allocator<unsigned char> >
  // m_candidateBuffer
};

// class CLanguage {
//  *
//    public void CLanguage(const class CLanguage &)
//    public void CLanguage::CLanguage()
//    public void CLanguage::~CLanguage()
//    public void SetHWnd(struct HWND__ *)
//    public void CLanguage::GetLanguageText(class std::string *)
//    public const char * CLanguage::GetLanguageCharset(unsigned char)
//    public const char * GetInput()
//    public void CLanguage::SetInput(const char *)
//    public void CLanguage::ResetInput()
//    public int GetInputSize()
//    public const char * CLanguage::GetKeyStroke()
//    public int CLanguage::GetKeyStrokeSize()
//    public void CLanguage::SetKeyStroke(unsigned char)
//    public void CLanguage::GetSelection(int *, int *)
//    public void CLanguage::SetSelection(int, int)
//    public void CLanguage::GetSelectionRange(int *, int *)
//    public int GetSelectionSize()
//    public int GetSelectionCursor()
//    public const char * GetCompositionString()
//    public int GetCompositionStringSize()
//    public int GetCompositionCursorPos()
//    public long CLanguage::ProcessImeMessage(struct HWND__ *, unsigned int,
//    unsigned int, long, unsigned char *) public void
//    CLanguage::OnKeyDown(unsigned int, long) public void
//    CLanguage::OnChar(unsigned int, long) public const char *
//    CLanguage::GetCandidateString(int) public int GetCandidateCount() public
//    int GetCandidateSelection() public int GetCandidatePageSize() public void
//    CLanguage::HideText(unsigned char) public const char *
//    CLanguage::GetWordBreak(const char *, unsigned int) public const char *
//    CLanguage::LanguageFile(const char *) public void
//    CLanguage::MoveUpSelection(int) public void
//    CLanguage::MoveDownSelection(int) public void AddInput2(const char *)
//    protected void CLanguage::GetImeCompStr()
//    protected void CLanguage::GetImeResultStr()
//    protected void CLanguage::GetImeCompAttr()
//    protected void CLanguage::GetImeCursorPos()
//    protected void CLanguage::GetImeCandidateList()
//    protected void CLanguage::CancelComposition()
//    protected void CLanguage::AddInput(const char *)
//    protected void CLanguage::CopyTextToClipBoard()
//    protected void CLanguage::CopyTextFromClipBoard()
//    protected void CLanguage::CutTextToClipBoard()
//    protected void CLanguage::BeginKeyStroke()
//    protected void CLanguage::EndKeyStroke()
//    protected void CLanguage::ClearKeyStroke()
//    protected void CLanguage::IncreaseSelection()
//    protected void CLanguage::DecreaseSelection()
//    protected void CLanguage::DeleteSelection()
//    protected void ClearSelection()
//    protected void CancelSelection()
//    protected void ClearComposition()
//    protected void ReadCandidate()
//    protected void ClearCandidate()
//    /* this+0x4 */ class std::deque<unsigned long, std::allocator<unsigned
//    long> > m_fakeInput
//
//    /* this+0x34 */ struct tagCANDIDATELIST * m_candidateList
//    /* this+0x38 */ int m_candidateCount
//    /* this+0x3c */ int m_candidatePageSize
//    /* this+0x40 */ int m_candidateSelection
//    /* this+0x44 */ class std::vector<unsigned char, std::allocator<unsigned
//    char> > m_candidateBuffer
//
//    /* this+0x54 */ class std::string m_input
//
//    /* this+0x64 */ int m_inputCursor
//    /* this+0x68 */ int m_selectionCursor
//    /* this+0x6c */ int m_selectionOrigin
//    /* this+0x70 */ class std::string m_keyStroke
//
//    /* this+0x80 */ class std::string m_compStr
//
//    /* this+0x90 */ int m_compCursorPos
//    /* this+0x94 */ unsigned char m_bHideText
//    /* this+0x96 */ unsigned short m_langId
//    /* this+0x98 */ unsigned int m_codePage
//    /* this+0x9c */ int m_underLineStart
//    /* this+0xa0 */ int m_underLineEnd
//    /* this+0xa4 */ class std::string m_languageFolder
//
//    /* this+0xb4 */ unsigned short m_scriptLangId
//    public class CLanguage & operator=(const class CLanguage &)
//    public void __local_vftable_ctor_closure()
//    public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_INPUT_LANGUAGE_H_
