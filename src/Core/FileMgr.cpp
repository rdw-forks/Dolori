#include "FileMgr.h"
#include "../Files/MemMapFile.h"
#include <iostream>

CFileMgr::CFileMgr() {}

CFileMgr::~CFileMgr() {}

bool CFileMgr::AddPak(char const* name) {
  CMemMapFile* memfile;
  CGPak* gpak;

  std::cout << "Opening " << name << std::endl;
  gpak = new CGPak();
  if (gpak) gpak->Init();

  memfile = new CMemMapFile();
  if (memfile) {
    memfile->init();
    memfile->open(name);
  }
  m_pakList.push_front(std::pair<CMemMapFile*, CGPak*>(memfile, gpak));

  return gpak->Open(memfile);
}