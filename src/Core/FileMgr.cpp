#include "Core/FileMgr.h"

#include <fstream>
#include <iostream>

#include "Common/debug.h"
#include "Files/MemMapFile.h"
#include "Files/pak_pack.h"

CFileMgr::CFileMgr() : m_pakList() {}

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

void *CFileMgr::GetPak(const std::string &file_name, size_t *file_size) {
  uint8_t *result = nullptr;

  if (m_pakList.empty()) {
    return nullptr;
  }

  for (const auto elem : m_pakList) {
    PAK_PACK pakPack;

    if (elem.second->GetInfo(file_name, &pakPack)) {
      result = new uint8_t[pakPack.m_size];
      if (!elem.second->GetData(&pakPack, result)) {
        LOG(error, "Failed to fecth file {}", file_name);
        delete[] result;
        return nullptr;
      }

      if (file_size != nullptr) {
        *file_size = pakPack.m_size;
      }
      LOG(debug, "Fetched file {} from pak file", file_name);
      break;
    }
  }

  return result;
}

bool CFileMgr::IsDataExist(const std::string &file_name) {
  if (!m_pakList.empty()) {
    for (const auto elem : m_pakList) {
      if (elem.second->GetInfo(file_name, nullptr)) {
        return true;
      }
    }
  }

  std::ifstream file_stream;
  file_stream.open(file_name, std::ios::binary);
  if (!file_stream.is_open()) {
    return false;
  }

  file_stream.close();

  return true;
}
