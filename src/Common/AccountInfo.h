#ifndef DOLORI_COMMON_ACCOUNTINFO_H_
#define DOLORI_COMMON_ACCOUNTINFO_H_

#include <string>

class CAccountInfo {
 public:
  // accountInfo(const struct accountInfo &);
  CAccountInfo();
  ~CAccountInfo();

 private:
  void CopyContents(const CAccountInfo &);

 private:
  std::string display;
  std::string desc;
  std::string balloon;
  std::string address;
  std::string port;
  int type;
  unsigned long version;
};

#endif // DOLORI_COMMON_ACCOUNTINFO_H_