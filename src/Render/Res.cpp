#include "Res.h"
#include <stdio.h>
#include "Common/ErrorMsg.h"
#include "Common/GetTick.h"

CRes::CRes() { m_extIndex = 0; }

CRes::~CRes() {}

CHash *const CRes::GetHash() { return &m_fName; }

void CRes::UpdateInfo(const char *fName, size_t extIndex) {
  m_fName.SetString(fName);
  m_extIndex = extIndex;
  UpdateTimeStamp();
}

void CRes::UpdateTimeStamp() { m_timeStamp = GetTick(); }

void CRes::OnLoadError(const char *fName) {
  char msg[256];

  snprintf(msg, sizeof(msg), "ResourceError : Can't find file %s", fName);
  ErrorMsg(msg);
}