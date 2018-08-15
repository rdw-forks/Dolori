#include "Core/FileMgr.h"

#include <fstream>
#include <iostream>

#include "Common/debug.h"
#include "Files/MemMapFile.h"
#include "Files/pak_pack.h"

CFileMgr::CFileMgr() : m_pakList() {}

CFileMgr::~CFileMgr() {}

bool CFileMgr::AddPak(const std::string &pak_name) {
  LOG(debug, "Opening file {}", pak_name);

  auto gpak = std::make_shared<CGPak>();
  if (!gpak) {
    return false;
  }

  auto memfile = std::make_shared<CMemMapFile>();
  if (!memfile) {
    return false;
  }

  gpak->Init();
  memfile->Init();

  if (!memfile->Open(pak_name.c_str())) {
    LOG(error, "Failed to open in-memory file: {}", pak_name);
    return false;
  }

  m_pakList.push_front(
      std::pair<std::shared_ptr<CMemFile>, std::shared_ptr<CGPak>>(memfile,
                                                                   gpak));

  return gpak->Open(memfile);
}

void *CFileMgr::GetPak(const std::string &file_name, size_t *size) {
  void *result = nullptr;
  CHash fName;

  if (m_pakList.empty()) {
    return nullptr;
  }

  fName.SetString(file_name.c_str());
  for (const auto elem : m_pakList) {
    PAK_PACK pakPack;

    if (elem.second->GetInfo(&fName, &pakPack)) {
      result = new uint8_t[pakPack.m_size];
      if (!elem.second->GetData(&pakPack, result)) {
        free(result);
        return nullptr;
      }

      *size = pakPack.m_size;
      LOG(debug, "Fetched file {} from pak file", file_name);
      break;
    }
  }

  return result;
}

bool CFileMgr::IsDataExist(const std::string &name) {
  if (!m_pakList.empty()) {
    for (const auto elem : m_pakList) {
      CHash hash(name.c_str());
      if (elem.second->GetInfo(&hash, nullptr)) {
        return true;
      }
    }
  }

  std::ifstream file_stream;
  file_stream.open(name, std::ios::binary);
  if (!file_stream.is_open()) {
    return false;
  }

  file_stream.close();

  return true;
}
