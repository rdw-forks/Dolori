#ifndef DOLORI_FILES_FILE_H_
#define DOLORI_FILES_FILE_H_

#include <fstream>
#include <iostream>
#include <string>

class CFile {
 public:
  CFile();
  ~CFile();

  static bool IsFileExist(const char *fName);
  bool Open(const std::string &, int);
  bool Read(void *buffer, size_t nCount);
  bool Seek(long lOff, size_t nFrom);
  bool Write(const void *, size_t);
  void Close();
  const std::string &GetFileName() const;
  size_t GetLength() const;
  const unsigned char *GetBuf() const;

 protected:
  bool OpenFromFolder(const std::string &);
  static void MakeFileName(const std::string &input, std::string &output);
  static void NormalizeFileName(const std::string &input, std::string &output);

 private:
  std::fstream m_fileStream;
  unsigned char *m_buf;
  size_t m_size;
  size_t m_cursor;
  std::string m_fileName;
};

#endif  // DOLORI_FILES_FILE_H_
