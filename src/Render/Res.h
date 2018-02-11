#ifndef DOLORI_RENDER_RES_H_
#define DOLORI_RENDER_RES_H_

#include <stdlib.h>
#include "Files/Hash.h"

class CRes {
 public:
  CRes();
  virtual ~CRes();

  CHash* const GetHash();
  void UpdateInfo(const char*, size_t);
  void UpdateTimeStamp();
  void OnLoadError(const char*);
  virtual bool Load(const char*) { return false; };
  virtual CRes* Clone() { return nullptr; };

 private:
  int m_lockCnt;
  unsigned long m_timeStamp;
  size_t m_extIndex;
  CHash m_fName;
};

#endif  // DOLORI_RENDER_RES_H_
