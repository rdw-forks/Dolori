#ifndef DOLORI_FILES_GPACK_H_
#define DOLORI_FILES_GPACK_H_

#include <memory>
#include <string>
#include <list>
#include <vector>

#include "Files/Hash.h"
#include "Files/MemFile.h"
#include "Files/pak_pack.h"

class CGPak {
 public:
  CGPak();

  bool Open(std::shared_ptr<CMemFile> memfile);
  void Init();
  bool GetInfo(const std::string &, PAK_PACK *) const;
  bool GetData(const PAK_PACK *pakPack, void *buffer);

 protected:
  bool OpenPak01();
  bool OpenPak02();
  void NormalizeFileName(const std::string &input, std::string &output);

 private:
  unsigned long m_FileVer;
  unsigned long m_FileCount;
  unsigned long m_PakInfoOffset;
  unsigned long m_PakInfoSize;
  std::list<PAK_PACK> m_PakPack;
  std::vector<unsigned char> m_pDecBuf;
  std::shared_ptr<CMemFile> m_memFile;
  // CRITICAL_SECTION m_csPak;
};

// class CGPak {
//	*
//		public void CGPak(const class CGPak &)
//		public void CGPak()
//		public void CGPak::~CGPak()
//		public unsigned char CGPak::Open(class CMemFile *)
//		public unsigned char CGPak::GetInfo(const class CHash &, struct
// PakPack *)
//		public unsigned char CGPak::GetData(const struct PakPack &, void
//*) 		protected void CGPak::Init() 		protected char
// CGPak::ChangeLHBit_BYTE(char) 		protected void
// CGPak::ModifyString(char *, const char *, int) 		protected void
// CGPak::ModifyString(char *, const char *) 		protected int
// CGPak::IsNeverEncrypt(const char *)
//		protected char * CGPak::MakeSeed(const char *, char *)
//		protected unsigned char CGPak::OpenPak01()
//		protected unsigned char CGPak::OpenPak02()
//		 unsigned long m_FileVer
//		 unsigned long m_FileCount
//		 unsigned long m_PakInfoOffset
//		 unsigned long m_PakInfoSize
//	 class std::vector<PakPack, std::allocator<PakPack> > m_PakPack
//
//	 class std::vector<unsigned char, std::allocator<unsigned char> >
// m_pDecBuf
//
//	 class CMemFile * m_memFile
//		public class CGPak & operator=(const class CGPak &)
//		public void __local_vftable_ctor_closure()
//		public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_FILES_GPACK_H_
