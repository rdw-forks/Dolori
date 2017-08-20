#ifndef DOLORI_RENDER_RES_H_
#define DOLORI_RENDER_RES_H_

#include "../Files/Hash.h"

class CRes {
 public:
  CRes();
  virtual ~CRes();

 private:
  int m_lockCnt;
  unsigned long m_timeStamp;
  int m_extIndex;
  CHash m_fName;
};

#endif  // DOLORI_RENDER_RES_H_
