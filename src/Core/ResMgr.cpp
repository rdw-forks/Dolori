#define _CRT_SECURE_NO_WARNINGS
#include "Core/ResMgr.h"

#include "Files/File.h"
#include "Render/3dWorldRes.h"
#include "Render/ActRes.h"
#include "Render/BitmapRes.h"
#include "Render/GndRes.h"
#include "Render/SprRes.h"

CResMgr::CResMgr()
    : m_usedForSprTexture(),
      m_usedForModelTexture(),
      m_usedForGNDTexture(),
      m_usedForSprite(),
      m_usedForSprAction(),
      m_usedForGAT(),
      m_usedForGND(),
      m_usedForIMF(),
      m_usedForModel(),
      m_ResMemAmount(),
      m_ResSprAmount(),
      m_ResTexAmount(),
      m_ResGatAmount(),
      m_ResGndAmount(),
      m_ResRswAmount(),
      m_ResModAmount(),
      m_ResWavAmount() {
  RegisterType("bmp", "texture/", new CBitmapRes());
  RegisterType("spr", "sprite/", new CSprRes());
  RegisterType("act", "sprite/", new CActRes());
  RegisterType("rsw", "", new C3dWorldRes());
  RegisterType("gnd", "", new CGndRes());
}

CResMgr::~CResMgr() {}

void CResMgr::ReadResNameTable(const std::string& resNameTable) {
  CFile file;

  if (file.Open(resNameTable, 0)) {
    size_t file_size = file.GetLength();
    char* buffer;

    buffer = new char[file_size + 1];
    if (!buffer) {
      return;
    }

    if (!file.Read(buffer, file_size)) {
      delete[] buffer;
      return;
    }

    buffer[file_size] = '\0';
    file.Close();

    // Parse the content of the name table
    std::string a;
    std::string b;
    char* beg_of_line = buffer;
    for (size_t i = 0; i < file_size; i++) {
      char cur_char = buffer[i];

      if (cur_char == '\r' || cur_char == '\n') {
        buffer[i] = '\0';
        beg_of_line = &buffer[i + 1];
        continue;
      }

      if (cur_char == '#') {
        buffer[i] = '\0';
        // If we have a left element,
        // fetch the right one and fill the map
        if (a.length() > 0) {
          b = beg_of_line;
          m_realResName[a] = b;
          a.clear();
          b.clear();
          beg_of_line = &buffer[i + 1];
          continue;
        }
        // Else we fetch what could be
        // a left element
        a = beg_of_line;
        beg_of_line = &buffer[i + 1];
      }
    }
    delete[] buffer;
  }
}

void CResMgr::RegisterType(const char* resId, const char* baseDir, CRes* t) {
  size_t extIndex = m_resExt.size();

  m_resExt[resId] = extIndex;
  m_objTypes.push_back(t);
  m_typeDir.push_back(baseDir);
  std::map<CHash* const, CRes*, ResPtrLess> map;
  m_fileList.push_back(map);
}

const char* CResMgr::GetRealResName(const char* resName) { return resName; }

CRes* CResMgr::Get(const char* fNameInput, bool bRefresh) {
  char open_filename[0x100];
  char filename[0x80];

  if (!fNameInput) {
    return nullptr;
  }

  m_getResSection.lock();
  strncpy(filename, fNameInput, sizeof(filename));
  ToLower(filename);
  const char* ext_ptr = StrChrBackward(filename, '.');
  if (!ext_ptr) {
    m_getResSection.unlock();
    return nullptr;
  }

  auto resext_node = m_resExt.find(ext_ptr + 1);
  if (resext_node == m_resExt.end()) {
    m_getResSection.unlock();
    return nullptr;
  }

  size_t extIndex = resext_node->second;
  if (extIndex < 0) {
    m_getResSection.unlock();
    return nullptr;
  }

  // Type directory
  const char* type_dir = m_typeDir[extIndex];
  size_t type_dir_len = strlen(type_dir);
  memset(open_filename, 0, sizeof(open_filename));
  if (!strncmp(filename, type_dir, type_dir_len)) {
    strncpy(open_filename, filename, sizeof(open_filename));
  } else {
    strncpy(open_filename, type_dir, sizeof(open_filename));
    strncpy(open_filename + type_dir_len, filename,
            sizeof(open_filename) - type_dir_len);
  }

  // Is the res already loaded ?
  CHash hash(open_filename);
  auto res_node = m_fileList[extIndex].find(&hash);
  if (res_node != m_fileList[extIndex].end()) {
    CRes* res = res_node->second;
    if (res && !bRefresh) {
      res->UpdateTimeStamp();
      m_getResSection.unlock();
      return res;
    }
  }

  // Try to load the res
  CRes* clone = m_objTypes[extIndex]->Clone();
  if (clone == nullptr) {
    m_getResSection.unlock();
    return nullptr;
  }

  if (!clone->Load(open_filename)) {
    const char* real_res_name = GetRealResName(filename);
    char* filename_ptr = open_filename;

    if (strncmp(real_res_name, type_dir, type_dir_len)) {
      strncpy(open_filename, type_dir, sizeof(open_filename));
      filename_ptr = open_filename + type_dir_len;
    }

    strncpy(filename_ptr, real_res_name, sizeof(open_filename) - type_dir_len);

    if (!clone->Load(open_filename)) {
      clone->OnLoadError(filename);
      delete clone;
      m_getResSection.unlock();
      return nullptr;
    }
  }

  clone->UpdateInfo(open_filename, extIndex);
  m_fileList[extIndex][clone->GetHash()] = clone;
  m_getResSection.unlock();
  return clone;
}

char* CResMgr::ToLower(char* str) {
  for (; *str != '\0'; str++) {
    *str = (char)tolower(*str);
  }

  return str;
}

const char* CResMgr::StrChrBackward(const char* strName, char c) {
  const char* result;

  result = &strName[strlen(strName) - 1];
  if (result < strName) {
    return nullptr;
  }

  while (*result != c) {
    if (--result < strName) {
      result = nullptr;
    }
  }

  return result;
}
