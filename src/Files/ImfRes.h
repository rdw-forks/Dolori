#ifndef DOLORI_FILES_IMFRES_H_
#define DOLORI_FILES_IMFRES_H_

#include <glm/glm.hpp>

#include <vector>

#include "Files/Res.h"

typedef struct _ImfData {
  std::vector<int32_t> priority;
  std::vector<int32_t> cx;
  std::vector<int32_t> cy;
} ImfData;

class CImfRes : public CRes {
 public:
  CImfRes();

  bool Load(const std::string& filename) override;
  CRes* Clone() override;

  glm::i32vec2 GetPoint(size_t layer, size_t action, size_t motion) const;

 protected:
  void Reset() override;

 private:
  std::vector<std::vector<ImfData>> m_ImfData;
  int32_t m_maxAction[0xf];
  int32_t m_maxMotion[0x68][0xf];
};

// class CImfRes {
//        CRes, offset = 0x0
//
//		public void CImfRes(const class CImfRes &)
//		public void CImfRes::CImfRes(class Exemplar, const char *,
// const
// char
//*) 		public void CImfRes::CImfRes() 		public
// class
// CRes
//* CImfRes::Clone() 		public unsigned char
// CImfRes::Load(const
// char *) 		public struct tagPOINT CImfRes::GetPoint(int, int,
// int) public int CImfRes::GetPriority(int, int, int)
// public int CImfRes::GetLayer(int, int, int) 		public
// int CImfRes::GetLongestMotion(int) 		public int
// CImfRes::GetNumMotion(int, int) 		public int
// CImfRes::GetNumAction(int) 		public int
// CImfRes::GetNumLayer() public void CImfRes::Create()
// public int CImfRes::CheckSum(int)
//		/* this+0x110 */ class std::vector<std::vector<ImfData,
// std::allocator<ImfData> >, std::allocator<std::vector<ImfData,
// std::allocator<ImfData> > > > m_ImfData
//
//		/* this+0x120 */ int[0xf] m_maxAction
//		/* this+0x15c */ int[0x68][0xf] m_maxMotion
//		public class CImfRes & operator=(const class CImfRes &)
//		public void CImfRes::~CImfRes()
//		public void __local_vftable_ctor_closure()
//		public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_FILES_IMFRES_H_
