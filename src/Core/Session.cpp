#include "Core/Session.h"

#include <sstream>

#include "Common/GetTick.h"
#include "Common/Globals.h"
#include "Common/const_strings.h"
#include "Common/debug.h"
#include "Common/service_type.h"

CSession::CSession() : m_char_name() {}

void CSession::Init() {}

bool CSession::Create() { return InitTable(); }

void CSession::SetSex(int sex) { m_sex = sex; }

int CSession::GetSex() { return m_sex; }

bool CSession::InitTable() {
  InitPcNameTable();
  InitJobNameTable();
  if (!g_MsgStrMgr->InitMsgStrings("msgStringTable.txt")) {
    LOG(error, "Failed to init message strings");
    return false;
  }

  return true;
}

void CSession::SetTextType(bool isShorten, bool isBold) {
  if (g_serviceType == ServiceType::kKorea ||
      g_serviceType == ServiceType::kIndonesia ||
      g_serviceType == ServiceType::kGermany ||
      g_serviceType == ServiceType::kBrazil) {
    g_NameBalloonShorten = isShorten;
    g_NameBalloonfontBold = isBold;
  }
}

void CSession::SetCharName(const std::string &char_name) {
  m_char_name = char_name;
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

bool CSession::IsMasterAid(uint32_t showLevel) {
  if (IsGravityAid(m_aid) && showLevel == 7) {
    return true;
  }
  if (g_serviceType != ServiceType::kKorea) {
    return false;
  }

  if (m_aid > 0x2C8C83) {
    if (m_aid != 2919558) {
      return false;
    }
  } else if (m_aid != 2919555) {
    if (m_aid == 100025) {
      return showLevel == 5;
    }

    if (m_aid != 234073) {
      return false;
    }
    return showLevel == 1;
  }

  return showLevel == 1 || showLevel == 2;
}

bool CSession::IsGravityAid(uint32_t aid) {
  bool result = false;

  for (const auto &admin_aid : s_dwAdminAID) {
    if (aid == admin_aid) {
      result = true;
      break;
    }
  }

  return result;
}

void CSession::InvalidateBasicWnd() {
  CGameMode *game_mode = g_ModeMgr->GetGameMode();
  if (game_mode != nullptr) {
    /*if (dword_7687EC)
    {
      UIWindow::InvalidateChildren(dword_7687EC);
    }
    game_mode->InvalidatePlayerGage();*/
  }
}

void CSession::InitPcNameTable() {
  // Jobs
  m_newPcJobNameTable[0] = "초보자";  // Novice
  m_newPcJobNameTable[1] = "검사";    // Swordman
  // m_newPcJobNameTable[2] = "";           // Mage
  m_newPcJobNameTable[3] = "마법사";     // Magician
  m_newPcJobNameTable[4] = "궁수";       // Archer
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
  // TODO(LinkZ): Babies
  m_jobNameTable[4218] = "Summoner";
}

const char *CSession::GetCharName() const { return m_char_name.c_str(); }

const char *CSession::GetJobName(unsigned int job) const {
  const auto elem = m_jobNameTable.find(job);
  if (elem == std::cend(m_jobNameTable)) {
    return nullptr;
  }

  return elem->second;
}

std::string CSession::GetJobActName(int job, int sex) const {
  const char *job_name = nullptr;
  std::ostringstream tmp_buffer;

  const auto job_elem = m_newPcJobNameTable.find(job);
  if (job_elem == std::cend(m_newPcJobNameTable)) {
    LOG(error, "Cannot find .act name for job #{}", job);
    return {};
  }

  if (job <= 3950) {
    job_name = job_elem->second;
  } else {
    job_name = std::next(job_elem, -3950)->second;
  }

  const auto sex_elem = m_newPcSexNameTable.find(sex);
  if (sex_elem == std::cend(m_newPcSexNameTable)) {
    return {};
  }

  // "인간족/몸통/%s/%s%s.act"
  tmp_buffer << const_strings::kCharactersFolderName
             << const_strings::kBodyFolderName << sex_elem->second << '/'
             << job_name << sex_elem->second << ".act";

  return tmp_buffer.str();
}

// TODO(LinkZ): Reduce code duplication
std::string CSession::GetJobSprName(int job, int sex) {
  const char *job_name = nullptr;
  std::ostringstream tmp_buffer;

  const auto job_elem = m_newPcJobNameTable.find(job);
  if (job_elem == std::cend(m_newPcJobNameTable)) {
    LOG(error, "Cannot find .spr name for job #{}", job);
    return nullptr;
  }

  if (job <= 3950) {
    job_name = job_elem->second;
  } else {
    job_name = std::next(job_elem, -3950)->second;
  }

  const auto sex_elem = m_newPcSexNameTable.find(sex);
  if (sex_elem == std::cend(m_newPcSexNameTable)) {
    return {};
  }

  // "인간족/몸통/%s/%s%s.spr"
  tmp_buffer << const_strings::kCharactersFolderName
             << const_strings::kBodyFolderName << sex_elem->second << '/'
             << job_name << sex_elem->second << ".spr";

  return tmp_buffer.str();
}

char *CSession::GetHeadActName(uint16_t head, int sex, char *buf) {
  const char *sex_folder_name;
  const char *head_name;
  const char *sex_suffix;

  if (head < 0 || head > 25) {
    head = 13;
  }

  if (sex != 0) {
    sex_suffix = m_pcSexNameTable[1];
    head_name = m_newPcHeadNameTable_M[head];
    sex_folder_name = m_newPcSexNameTable[1];
  } else {
    sex_suffix = m_pcSexNameTable[0];
    head_name = m_newPcHeadNameTable_F[head];
    sex_folder_name = m_newPcSexNameTable[0];
  }

  sprintf(buf, "인간족/머리통/%s/%s%s.act", sex_folder_name, head_name,
          sex_suffix);

  return buf;
}

char *CSession::GetHeadSprName(uint16_t head, int sex, char *buf) {
  const char *sex_folder_name;
  const char *head_name;
  const char *sex_suffix;

  if (head < 0 || head > 25) {
    head = 13;
  }

  if (sex != 0) {
    sex_suffix = m_pcSexNameTable[1];
    head_name = m_newPcHeadNameTable_M[head];
    sex_folder_name = m_newPcSexNameTable[1];
  } else {
    sex_suffix = m_pcSexNameTable[0];
    head_name = m_newPcHeadNameTable_F[head];
    sex_folder_name = m_newPcSexNameTable[0];
  }

  sprintf(buf, "인간족/머리통/%s/%s%s.spr", sex_folder_name, head_name,
          sex_suffix);

  return buf;
}

std::string CSession::GetImfName(int job, int sex) {
  std::ostringstream tmp_buffer;
  const char *imf_name;

  const auto job_elem = m_newPcJobImfNameTable.find(job);
  if (job_elem == std::cend(m_newPcJobImfNameTable)) {
    LOG(error, "Cannot find .imf name for job #{}", job);
    return {};
  }

  if (job <= 3950) {
    imf_name = job_elem->second;
  } else {
    imf_name = std::next(job_elem, -3950)->second;
  }

  const auto sex_elem = m_pcSexNameTable.find(sex);
  if (sex_elem == std::cend(m_pcSexNameTable)) {
    return {};
  }

  tmp_buffer << imf_name << sex_elem->second << ".imf";

  return tmp_buffer.str();
}
