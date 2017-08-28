#ifndef DOLORI_CORE_RESMGR_H_
#define DOLORI_CORE_RESMGR_H_

#include <map>
#include <mutex>
#include <string>
#include <vector>
#include "../Render/Res.h"

struct CharPrtLess {
  bool operator()(const char *a, const char *b) const {
    return std::strcmp(a, b) < 0;
  }
};

struct ResPtrLess {
  bool operator()(CHash *a, CHash *b) const { return *a < *b; }
};

class CResMgr {
 public:
  CResMgr();
  ~CResMgr();

  void ReadResNameTable(const char *);
  void RegisterType(const char *, const char *, CRes *);
  char *GetRealResName(const char *);
  CRes *Get(const char *, bool);

 private:
  char *ToLower(char *);
  const char *StrChrBackward(const char *, char);

 private:
  std::map<const char *, int, CharPrtLess> m_resExt;
  std::vector<const char *> m_typeDir;
  std::vector<CRes *> m_objTypes;
  std::vector<std::map<CHash *const, CRes *, ResPtrLess>> m_fileList;
  std::recursive_mutex m_getResSection;
  std::map<std::string, std::string> m_realResName;
  unsigned long m_usedForSprTexture;
  unsigned long m_usedForModelTexture;
  unsigned long m_usedForGNDTexture;
  unsigned long m_usedForSprite;
  unsigned long m_usedForSprAction;
  unsigned long m_usedForGAT;
  unsigned long m_usedForGND;
  unsigned long m_usedForIMF;
  unsigned long m_usedForModel;
  unsigned long m_ResMemAmount;
  unsigned long m_ResSprAmount;
  unsigned long m_ResTexAmount;
  unsigned long m_ResGatAmount;
  unsigned long m_ResGndAmount;
  unsigned long m_ResRswAmount;
  unsigned long m_ResModAmount;
  unsigned long m_ResWavAmount;
};

// class CResMgr {
//  public void CResMgr(const class CResMgr &)
//    public void CResMgr::CResMgr()
//    public void CResMgr::~CResMgr()
//    public void CResMgr::Reset()
//    public class CRes * CResMgr::Get(const char *, unsigned char)
//    public class CRes * CResMgr::GetAlways(const char *)
//    public int CResMgr::IsExist(const char *)
//    public void CResMgr::Unload(class CRes *)
//    public void CResMgr::UnloadAll()
//    public void CResMgr::UnloadRarelyUsedRes()
//    public void CResMgr::UnloadUnlockedRes()
//    public void CResMgr::UnloadResByExt(const char *)
//    public void CResMgr::RegisterType(const char *, const char *, class CRes
//    *) public void CResMgr::ReadResNameTable(const char *) public void
//    CResMgr::PrintRes(const char *) private class CRes * CResMgr::FindRes(int,
//    const char *) private void CResMgr::MakeOpenName(char *, const char *,
//    const char *) private const char * CResMgr::ExtractExt(const char *)
//    private int CResMgr::FindExtIndex(const char *)
//    private const char * CResMgr::GetRealResName(const char *)
//    private char * CResMgr::ToLower(char *)
//     class std::map<char const *, int, CharPrtLess,
//    std::allocator<int> > m_resExt
//
//     class std::vector<char const *, std::allocator<char const
//    *> > m_typeDir
//
//     class std::vector<CRes *, std::allocator<CRes *> >
//    m_objTypes
//
//     class std::vector<std::map<CHash *, CRes *, ResPtrLess,
//    std::allocator<CRes *> >, std::allocator<std::map<CHash *, CRes *,
//    ResPtrLess, std::allocator<CRes *> > > > m_fileList
//
//     struct _RTL_CRITICAL_SECTION m_GetResSection
//
//     class std::map<std::string, std::string,
//    std::less<std::string >, std::allocator<std :83de5b43 m_realResName
//
//     unsigned long m_usedForSprTexture
//     unsigned long m_usedForModelTexture
//     unsigned long m_usedForGNDTexture
//     unsigned long m_usedForSprite
//     unsigned long m_usedForSprAction
//     unsigned long m_usedForGAT
//     unsigned long m_usedForGND
//     unsigned long m_usedForIMF
//     unsigned long m_usedForModel
//     unsigned long m_ResMemAmount
//     unsigned long m_ResSprAmount
//     unsigned long m_ResTexAmount
//     unsigned long m_ResGatAmount
//     unsigned long m_ResGndAmount
//     unsigned long m_ResRswAmount
//     unsigned long m_ResModAmount
//     unsigned long m_ResWavAmount
//    public class CResMgr & operator=(const class CResMgr &)
//    public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_CORE_RESMGR_H_
