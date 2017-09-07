#include "FileMgr.h"
#include <iostream>
#include "../Files/MemMapFile.h"
#include "../Files/pak_pack.h"
#include <fstream>

CFileMgr::CFileMgr() {}

CFileMgr::~CFileMgr() {}

bool CFileMgr::AddPak(char const *name) {
  CMemMapFile *memfile;
  CGPak *gpak;

  std::cout << "Opening " << name << std::endl;
  gpak = new CGPak();
  if (!gpak) return false;
  gpak->Init();

  memfile = new CMemMapFile();
  if (!memfile) return false;
  memfile->Init();

  if (!memfile->Open(name)) return false;
  m_pakList.push_front(std::pair<CMemMapFile *, CGPak *>(memfile, gpak));

  return gpak->Open(memfile);
}

void *CFileMgr::GetPak(const char *filename, size_t *size) {
  void *result = NULL;
  CHash fName;
  PAK_PACK pakPack;

  if (m_pakList.empty()) return NULL;
  fName.SetString(filename);
  auto it = m_pakList.begin();
  for (; it != m_pakList.end(); ++it) {
    if (it->second->GetInfo(&fName, &pakPack)) {
      result = malloc(pakPack.m_size);
      if (!it->second->GetData(&pakPack, result)) {
        free(result);
        result = NULL;
      }
      *size = pakPack.m_size;
      std::cout << "Fetched " << filename << " from Pak" << std::endl;
      break;
    }
  }
  return result;
}

bool CFileMgr::IsDataExist(const char *name)
{
  if (m_pakList.empty())
  {
    std::ifstream file_stream;
    file_stream.open(name, std::ios::binary);
    if (!file_stream.is_open())
      return false;
    file_stream.close();
  }
  else
  {
    for (auto it = m_pakList.begin(); it != m_pakList.end(); ++it)
    {
      CHash hash(name);
      if (it->second->GetInfo(&hash, NULL))
        break;
    }
    std::ifstream file_stream;
    file_stream.open(name, std::ios::binary);
    if (!file_stream.is_open())
      return false;
    file_stream.close();
  }

  return true;
}
