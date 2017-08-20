#ifndef DOLORI_FILES_FILE_H_
#define DOLORI_FILES_FILE_H_

#include <fstream>
#include <iostream>

class CFile {
 public:
  CFile();
  ~CFile();

  bool Open(const char *, int);
  bool Read(void *lpBuf, unsigned long nCount);
  bool Seek(long lOff, unsigned long nFrom);
  bool Write(const void*, unsigned long);
  void Close();
  char* GetFileName();
  unsigned long GetLength();
  const unsigned char* GetBuf();

 protected:
  static void MakeFileName(char *, const char *, unsigned long);

 private:
  std::fstream m_fileStream;
  unsigned char *m_buf;
  unsigned long m_size;
  unsigned long m_cursor;
  char m_fileName[0x80];
};

#endif  // DOLORI_FILES_FILE_H_
