#include "Render/Res.h"

#include <stdio.h>

#include "Common/ErrorMsg.h"
#include "Common/GetTick.h"
#include "Common/debug.h"

CRes::CRes() : m_extIndex() {}

CRes::~CRes() {}

CHash *const CRes::GetHash() { return &m_fName; }

void CRes::UpdateInfo(const char *fName, size_t extIndex) {
  m_fName.SetString(fName);
  m_extIndex = extIndex;
  UpdateTimeStamp();
}

void CRes::UpdateTimeStamp() { m_timeStamp = GetTick(); }

void CRes::OnLoadError(const char *fName) {
  LOG(error, "Failed to find file {}", fName);
  const auto error_msg =
      std::string("ResourceError : Can't find file ") + std::string(fName);
  ErrorMsg(error_msg.c_str());
}
