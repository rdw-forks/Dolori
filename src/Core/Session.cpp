#include "Session.h"
#include "../Common/GetTick.h"
#include "../Common/Globals.h"
#include "../Common/service_type.h"

CSession::CSession() {}

CSession::~CSession() {}

void CSession::Init() {}

void CSession::Create() { InitTable(); }

void CSession::SetSex(int sex) { m_sex = sex; }

int CSession::GetSex() { return m_sex; }

void CSession::InitTable() {
  InitPcNameTable();
  InitJobNameTable();
  g_MsgStrMgr->InitMsgStrings("msgStringTable.txt");
}

void CSession::SetTextType(bool isShorten, bool isBold) {
  if (g_serviceType == ServiceKorea || g_serviceType == ServiceIndonesia ||
      g_serviceType == ServiceGermany || g_serviceType == ServiceBrazil) {
    g_NameBalloonShorten = isShorten;
    g_NameBalloonfontBold = isBold;
  }
}

void CSession::SetCharName(const char *char_name) {
  strncpy(m_cName, char_name, sizeof(m_cName));
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

void CSession::InvalidateBasicWnd() {
  if (g_ModeMgr->GetGameMode()) {
    /*if (dword_7687EC)
    {
      UIWindow::InvalidateChildren(dword_7687EC);
    }
    g_ModeMgr->GetGameMode()->InvalidatePlayerGage();*/
  }
}

void CSession::InitPcNameTable() {
  // Jobs
  m_newPcJobNameTable[16] = "세이지";    // Monk
  m_newPcJobNameTable[17] = "몽크";      // Sage
  m_newPcJobNameTable[66] = "챔피온";    // Champion
  m_newPcJobNameTable[67] = "프로페서";  // Professor

  m_newPcJobNameTable[268] = "프로페서";  // Doram place-holder

  // Sex
  m_newPcSexNameTable[0] = "여";
  m_newPcSexNameTable[1] = "남";
  m_pcSexNameTable[0] = "_여";
  m_pcSexNameTable[1] = "_남";

  // Heads
  m_newPcHeadNameTable_M[0] = "2";
  m_newPcHeadNameTable_M[1] = "2";
  m_newPcHeadNameTable_F[0] = "2";
  m_newPcHeadNameTable_F[1] = "2";
}

void CSession::InitJobNameTable() {
  m_jobNameTable[0] = "Novice";
  m_jobNameTable[1] = "Swordman";
  m_jobNameTable[2] = "Mage";
  m_jobNameTable[3] = "Magician";
  m_jobNameTable[4] = "Archer";
  m_jobNameTable[5] = "Acolyte";
  m_jobNameTable[6] = "Merchant";
  m_jobNameTable[7] = "Thief";
  m_jobNameTable[8] = "Knight";
  m_jobNameTable[9] = "Priest";
  m_jobNameTable[10] = "Wizard";
  m_jobNameTable[11] = "Blacksmith";
  m_jobNameTable[12] = "Hunter";
  m_jobNameTable[13] = "Assassin";
  m_jobNameTable[14] = "Knight";
  m_jobNameTable[15] = "Crusader";
  m_jobNameTable[16] = "Monk";
  m_jobNameTable[17] = "Sage";
  m_jobNameTable[18] = "Rogue";
  m_jobNameTable[19] = "Alchemist";
  m_jobNameTable[20] = "Bard";
  m_jobNameTable[21] = "Dancer";
  m_jobNameTable[22] = "Crusader";
  m_jobNameTable[23] = "Super Novice";
  m_jobNameTable[24] = "Gunslinger";
  m_jobNameTable[25] = "Ninja";
  m_jobNameTable[4001] = "Novice High";
  m_jobNameTable[4002] = "Swordman High";
  m_jobNameTable[4003] = "Magician High";
  m_jobNameTable[4004] = "Archer High";
  m_jobNameTable[4005] = "Acolyte High";
  m_jobNameTable[4006] = "Merchant High";
  m_jobNameTable[4007] = "Thief High";
  m_jobNameTable[4008] = "Lord Knight";
  m_jobNameTable[4009] = "High Pirest";
  m_jobNameTable[4010] = "High Wizard";
  m_jobNameTable[4011] = "Whitesmith";
  m_jobNameTable[4012] = "Sniper";
  m_jobNameTable[4013] = "Assassin Cross";
  m_jobNameTable[4014] = "Lord Knight";
  m_jobNameTable[4015] = "Paladin";
  m_jobNameTable[4016] = "Champion";
  m_jobNameTable[4017] = "Professor";
  m_jobNameTable[4018] = "Stalker";
  m_jobNameTable[4019] = "Creator";
  m_jobNameTable[4020] = "Clown";
  m_jobNameTable[4021] = "Gypsy";
  m_jobNameTable[4022] = "Paladin";
  // TODO: Babies
}

const char *CSession::GetJobName(int job) { return m_jobNameTable[job]; }

char *CSession::GetJobActName(int job, int sex, char *buf) {
  const char *job_name;

  if (job <= 3950)
    job_name = m_newPcJobNameTable[job];
  else
    job_name = m_newPcJobNameTable[job - 3950];
  sprintf(buf, "인간족/몸통/%s/%s%s.act", m_newPcSexNameTable[sex], job_name,
          m_pcSexNameTable[sex]);

  return buf;
}

char *CSession::GetJobSprName(int job, int sex, char *buf) {
  const char *job_name;

  if (job <= 3950)
    job_name = m_newPcJobNameTable[job];
  else
    job_name = m_newPcJobNameTable[job - 3950];
  sprintf(buf, "인간족/몸통/%s/%s%s.spr", m_newPcSexNameTable[sex], job_name,
          m_pcSexNameTable[sex]);

  return buf;
}

char *CSession::GetHeadActName(int job, unsigned short *head, int sex,
                               char *buf) {
  const char *sex_folder_name;
  const char *head_name;
  const char *sex_suffix;

  if (*head < 0 || *head > 25) *head = 13;

  if (sex) {
    sex_suffix = m_pcSexNameTable[1];
    head_name = m_newPcHeadNameTable_M[*head];
    sex_folder_name = m_newPcSexNameTable[1];
  } else {
    sex_suffix = m_pcSexNameTable[0];
    head_name = m_newPcHeadNameTable_F[*head];
    sex_folder_name = m_newPcSexNameTable[0];
  }
  sprintf(buf, "인간족/머리통/%s/%s%s.act", sex_folder_name, head_name,
          sex_suffix);

  return buf;
}

char *CSession::GetHeadSprName(int job, unsigned short *head, int sex,
                               char *buf) {
  const char *sex_folder_name;
  const char *head_name;
  const char *sex_suffix;

  if (*head < 0 || *head > 25) *head = 13;

  if (sex) {
    sex_suffix = m_pcSexNameTable[1];
    head_name = m_newPcHeadNameTable_M[*head];
    sex_folder_name = m_newPcSexNameTable[1];
  } else {
    sex_suffix = m_pcSexNameTable[0];
    head_name = m_newPcHeadNameTable_F[*head];
    sex_folder_name = m_newPcSexNameTable[0];
  }
  sprintf(buf, "인간족/머리통/%s/%s%s.spr", sex_folder_name, head_name,
          sex_suffix);

  return buf;
}

char *CSession::GetImfName(int job, int head, int sex, char *buf) {
  const char *imf_name;

  if (job <= 3950)
    imf_name = m_newPcJobImfNameTable[job];
  else
    imf_name = m_newPcJobImfNameTable[job - 3950];
  sprintf(buf, "%s%s.imf", imf_name, m_pcSexNameTable[sex]);

  return buf;
}
