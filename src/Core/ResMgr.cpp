#define _CRT_SECURE_NO_WARNINGS
#include "Core/ResMgr.h"

#include <algorithm>

#include "Files/ActRes.h"
#include "Files/BitmapRes.h"
#include "Files/File.h"
#include "Files/GatRes.h"
#include "Files/GndRes.h"
#include "Files/RsmRes.h"
#include "Files/RswRes.h"
#include "Files/SprRes.h"

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
  RegisterType("tga", "texture/", new CBitmapRes());
  RegisterType("jpg", "texture/", new CBitmapRes());
  RegisterType("spr", "sprite/", new CSprRes());
  RegisterType("act", "sprite/", new CActRes());
  RegisterType("rsw", "", new CRswRes());
  RegisterType("gnd", "", new CGndRes());
  RegisterType("gat", "", new CGatRes());
  RegisterType("rsm", "model/", new CRsmRes());
}

void CResMgr::Reset() {}

void CResMgr::ReadResNameTable(const std::string& resNameTable) {
  CFile file;

  if (file.Open(resNameTable, 0)) {
    size_t file_size = file.GetLength();
    char* buffer;

    buffer = new char[file_size + 1];
    if (buffer == nullptr) {
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

void CResMgr::RegisterType(const std::string& resId, const std::string& baseDir,
                           CRes* t) {
  size_t extIndex = m_resExt.size();

  m_resExt[resId] = extIndex;
  m_objTypes.push_back(t);
  m_typeDir.push_back(baseDir);
  m_fileList.push_back(std::map<std::string, CRes*>());
}

std::string CResMgr::GetRealResName(std::string res_name) const {
  return std::move(res_name);
}

CRes* CResMgr::Get(std::string filename, bool bRefresh) {
  std::unique_lock<std::recursive_mutex> lock(m_getResSection);
  std::string open_filename;

  // Warning: This assumes that filename is an ASCII string
  std::transform(std::begin(filename), std::end(filename), std::begin(filename),
                 ::tolower);
  size_t pos = filename.rfind('.');
  const char* ext_ptr = &filename.c_str()[pos];
  if (ext_ptr == nullptr) {
    return nullptr;
  }

  auto resext_node = m_resExt.find(ext_ptr + 1);
  if (resext_node == std::end(m_resExt)) {
    return nullptr;
  }

  size_t extIndex = resext_node->second;

  // Type directory
  const std::string& type_dir = m_typeDir[extIndex];
  if (filename.compare(0, type_dir.length(), type_dir) == 0) {
    open_filename = filename;
  } else {
    open_filename = type_dir + filename;
  }

  // Is the res already loaded ?
  auto res_node = m_fileList[extIndex].find(open_filename);
  if (res_node != m_fileList[extIndex].end()) {
    CRes* res = res_node->second;
    if (res != nullptr && !bRefresh) {
      res->UpdateTimeStamp();
      return res;
    }
  }

  // Try to load the res
  CRes* clone = m_objTypes[extIndex]->Clone();
  if (clone == nullptr) {
    return nullptr;
  }

  if (!clone->Load(open_filename)) {
    const std::string real_res_name = std::move(GetRealResName(filename));
    if (real_res_name.compare(0, type_dir.length(), type_dir) == 0) {
      open_filename = real_res_name;
    } else {
      open_filename = type_dir + real_res_name;
    }

    if (!clone->Load(open_filename)) {
      delete clone;
      return nullptr;
    }
  }

  clone->UpdateInfo(open_filename, extIndex);
  m_fileList[extIndex][clone->GetName()] = clone;
  return clone;
}

void CResMgr::Unload(CRes* res_to_unload) {
  if (res_to_unload == nullptr) {
    return;
  }

  const size_t ext_index = res_to_unload->ext_index();
  const auto res_name = res_to_unload->GetName();
  auto res_node = m_fileList[ext_index].find(res_name);
  if (res_node != std::cend(m_fileList[ext_index])) {
    m_fileList[ext_index].erase(res_node);
    delete res_to_unload;
  }
}
