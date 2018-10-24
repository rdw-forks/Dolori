#ifndef DOLORI_FILES_CLIENTINFO_H_
#define DOLORI_FILES_CLIENTINFO_H_

#include <string>

#include <tinyxml2.h>

class ClientInfo {
 public:
  const unsigned int kDefaultClientVersion = 23;

  ClientInfo(std::string file_path);

  bool Load();

 private:
  void SetOption(const tinyxml2::XMLDocument& document);
  void SetLoginStartMode();

 private:
  std::string file_path_;
};

#endif /* DOLORI_FILES_CLIENTINFO_H_ */
