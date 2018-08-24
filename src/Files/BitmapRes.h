#ifndef DOLORI_RENDER_BITMAPRES_H_
#define DOLORI_RENDER_BITMAPRES_H_

#include <stdint.h>

#include <string>
#include <vector>

#include <il.h>

#include "Files/Res.h"

class CBitmapRes : public CRes {
 public:
  CBitmapRes();
  ~CBitmapRes();

  bool Load(const std::string &) override;
  CRes *Clone() override;

  uint32_t GetWidth() const;
  uint32_t GetHeight() const;
  const ILubyte *GetData() const;
  unsigned int GetColor(int x, int y) const;
  bool LoadFromBuffer(const std::string &, const uint8_t *, size_t);
  bool LoadBMPData(const uint8_t *, size_t);
  bool LoadTGAData(const uint8_t *, size_t);
  bool LoadJPGData(const uint8_t *, size_t);

 protected:
  void Reset() override;

 private:
  bool LoadImageData(const uint8_t *, size_t, ILenum);

 private:
  int m_isAlpha;
  uint32_t m_width;
  uint32_t m_height;
  std::vector<ILubyte> m_data;
};

#endif  // DOLORI_RENDER_BITMAPRES_H_
