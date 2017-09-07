#ifndef DOLORI_FILES_FILE_H_
#define DOLORI_FILES_FILE_H_

#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <iostream>

class CFile {
 public:
  CFile();
  ~CFile();

  static bool IsFileExist(const char * fName);
  bool Open(const char *, int);
  bool Read(void *lpBuf, unsigned long nCount);
  bool Seek(long lOff, unsigned long nFrom);
  bool Write(const void *, unsigned long);
  void Close();
  char *GetFileName();
  size_t GetLength();
  const unsigned char *GetBuf();

 protected:
  bool OpenFromFolder(const char *);
  static void MakeFileName(char *, const char *, unsigned long);
  static char *NormalizeFileName(char *, const char *);

 private:
  std::fstream m_fileStream;
  unsigned char *m_buf;
  size_t m_size;
  size_t m_cursor;
  char m_fileName[0x80];
};

#endif  // DOLORI_FILES_FILE_H_
