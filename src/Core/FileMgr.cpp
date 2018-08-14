#include "Core/FileMgr.h"

#include <fstream>
#include <iostream>

#include "Common/debug.h"
#include "Files/MemMapFile.h"
#include "Files/pak_pack.h"

CFileMgr::CFileMgr() {}

CFileMgr::~CFileMgr() {}

// TODO: Fix these outrageous memory leaks
bool CFileMgr::AddPak(char const *name) {
  CMemMapFile *memfile;
  CGPak *gpak;

  LOG(debug, "Opening file {}", name);
  gpak = new CGPak();
  if (!gpak) {
    return false;
  }

  gpak->Init();

  memfile = new CMemMapFile();
  if (!memfile) {
    return false;
  }

  memfile->Init();
  if (!memfile->Open(name)) {
    return false;
  }

  m_pakList.push_front(std::pair<CMemMapFile *, CGPak *>(memfile, gpak));

  return gpak->Open(memfile);
}

void *CFileMgr::GetPak(const char *filename, size_t *size) {
  void *result = nullptr;
  CHash fName;
  PAK_PACK pakPack;

  if (m_pakList.empty()) {
    return nullptr;
  }

  fName.SetString(filename);
  auto it = m_pakList.begin();
  for (; it != m_pakList.end(); ++it) {
    if (it->second->GetInfo(&fName, &pakPack)) {
      result = malloc(pakPack.m_size);
      if (!it->second->GetData(&pakPack, result)) {
        free(result);
        result = nullptr;
      } else {
        *size = pakPack.m_size;
        LOG(debug, "Fetched file {} from pak file", filename);
      }
      break;
    }
  }
  return result;
}

bool CFileMgr::IsDataExist(const char *name) {
  if (m_pakList.empty()) {
    std::ifstream file_stream;
    file_stream.open(name, std::ios::binary);
    if (!file_stream.is_open()) {
      return false;
    }

    file_stream.close();
  } else {
    for (auto it = m_pakList.begin(); it != m_pakList.end(); ++it) {
      CHash hash(name);
      if (it->second->GetInfo(&hash, nullptr)) {
        break;
      }
    }

    std::ifstream file_stream;
    file_stream.open(name, std::ios::binary);
    if (!file_stream.is_open()) {
      return false;
    }

    file_stream.close();
  }

  return true;
}
