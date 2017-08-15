#include "Session.h"
#include "../Common/GetTick.h"
#include "../Common/Globals.h"
#include "../Common/service_type.h"

CSession::CSession() {}

CSession::~CSession() {}

void CSession::Init() {}

void CSession::Create() {}

void CSession::SetSex(int sex) { m_sex = sex; }

int CSession::GetSex() { return m_sex; }

void CSession::SetTextType(bool isShorten, bool isBold) {
  if (g_serviceType == ServiceKorea || g_serviceType == ServiceIndonesia ||
      g_serviceType == ServiceGermany || g_serviceType == ServiceBrazil) {
    g_NameBalloonShorten = isShorten;
    g_NameBalloonfontBold = isBold;
  }
}

void CSession::SetCharName(const char *char_name) {
  strncpy_s(m_cName, char_name, sizeof(m_cName));
}

void CSession::SetServerTime(unsigned int startTime) {
  m_numLatePacket = 0;
  m_diffTime = GetTick() - startTime;
}

void CSession::SetPlayerPosDir(int x, int y, int dir) {
  m_dir = dir;
  m_posX = x;
  m_posY = y;
}

std::list<std::string> CSession::GetNumExNameList() { return m_exNameList; }

bool CSession::IsMasterAid(int showLevel) {
  if (IsGravityAid(m_aid) && showLevel == 7) return true;
  if (g_serviceType != ServiceKorea) return false;

  if (m_aid > 0x2C8C83) {
    if (m_aid != 2919558) return false;
  } else if (m_aid != 2919555) {
    if (m_aid == 100025) return showLevel == 5;
    if (m_aid != 234073) return false;
    return showLevel == 1;
  }
  if (showLevel == 2) return true;
  return showLevel == 1;
}

bool CSession::IsGravityAid(int aid) {
  auto it = s_dwAdminAID.begin();

  for (; it != s_dwAdminAID.end(); ++it) {
    if (*it == aid) break;
  }
  return it != s_dwAdminAID.end();
}