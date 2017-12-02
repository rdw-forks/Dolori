#ifndef DOLORI_RENDER_TEXTURE_H_
#define DOLORI_RENDER_TEXTURE_H_

#include "Surface.h"
#include "pixel_format.h"

class CTexture : public CSurface {
 public:
  CTexture();
  CTexture(unsigned long, unsigned long, PIXEL_FORMAT);
  CTexture(unsigned long, unsigned long, PIXEL_FORMAT, SDL_Surface*);
  virtual ~CTexture();
  // static void SetUVOffset(float, float);
  void Create(unsigned long, unsigned long, PIXEL_FORMAT);
  bool CreateBump(unsigned long, unsigned long);
  unsigned long GetUpdateWidth();
  unsigned long GetUpdateHeight();

 private:
  PIXEL_FORMAT m_pf;
  unsigned char m_blackkey;
  unsigned long m_update_width;
  unsigned long m_update_height;
  char m_tex_name[256];
  long m_lock_count;
  unsigned long m_time_stamp;
  // static float m_u_offset;
  // static float m_v_offset;
};

#endif  // DOLORI_RENDER_TEXTURE_H_
