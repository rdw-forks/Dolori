#include "Files/Res.h"

#include <stdio.h>

#include "Common/GetTick.h"
#include "Common/debug.h"

CRes::CRes() : m_lockCnt(0), m_timeStamp(), m_ext_index() {}

size_t CRes::ext_index() const { return m_ext_index; }

const std::string &CRes::GetName() const { return m_res_name; }

void CRes::UpdateInfo(const std::string &fName, size_t extIndex) {
  m_res_name = fName;
  m_ext_index = extIndex;
  UpdateTimeStamp();
}

void CRes::UpdateTimeStamp() { m_timeStamp = GetTick(); }
