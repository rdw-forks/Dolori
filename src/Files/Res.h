#ifndef DOLORI_RENDER_RES_H_
#define DOLORI_RENDER_RES_H_

#include <stdlib.h>

#include <string>

class CRes {
 public:
  CRes();
  virtual ~CRes();

  virtual bool Load(const std::string&) = 0;
  virtual CRes* Clone() = 0;

  size_t ext_index() const;
  const std::string& GetName() const;
  void UpdateInfo(const std::string&, size_t);
  void UpdateTimeStamp();

 protected:
  virtual void Reset() = 0;

 private:
  int m_lockCnt;
  unsigned long m_timeStamp;
  size_t m_ext_index;
  std::string m_res_name;
};

#endif  // DOLORI_RENDER_RES_H_
