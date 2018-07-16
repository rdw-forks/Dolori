#ifndef DOLORI_RENDER_SPRRES_H_
#define DOLORI_RENDER_SPRRES_H_

#include <string>
#include <vector>

#include "Render/Res.h"
#include "Render/spr_img.h"

typedef enum SPR_TYPE { SPR_PAL = 0x0, SPR_RGBA = 0x1 } SPR_TYPE;

#pragma pack(push)
#pragma pack(1)

typedef struct SPR_HEADER {
  uint16_t magic;
  uint16_t version;
  uint16_t pal_img_count;
  // uint16_t rgba_img_count;
} SPR_HEADER;

#pragma pack(pop)

class CSprRes : public CRes {
 public:
  CSprRes();
  ~CSprRes();

  CRes* Clone();
  void Reset();
  const uint32_t* GetPalette();
  bool Load(const std::string& fName);
  SPR_IMG* GetSprImg(SPR_TYPE clip_type, unsigned long spr_index);
  uint8_t* DecodeRLE(uint8_t* image, int x, int y, unsigned short* size);

 private:
  uint32_t m_pal[0x100];
  std::vector<SPR_IMG*> m_sprites[0x2];
  uint16_t m_count;
};

// class CSprRes {
//  CRes, offset = 0x0
//
//    public void CSprRes(const class CSprRes &)
//    public void CSprRes::CSprRes(class Exemplar, const char *, const char *)
//    public void CSprRes::CSprRes()
//    public class CRes * CSprRes::Clone()
//    public unsigned char CSprRes::Load(const char *)
//    public void CSprRes::Reset()
//    public void Unload()
//    public unsigned char * CSprRes::ZeroCompression(unsigned char *, int, int,
//    unsigned short &) public unsigned char *
//    CSprRes::ZeroDecompression(unsigned char *, int, int) public unsigned char
//    * CSprRes::HalfImage(unsigned char *, int, int, int, int)
//    /* this+0x110 */ unsigned long[0x100] m_pal
//    /* this+0x510 */ class std::vector<SprImg *, std::allocator<SprImg *>
//    >[0x2] m_sprites
//    /* this+0x530 */ int m_count
//    public class CSprRes & operator=(const class CSprRes &)
//    public void CSprRes::~CSprRes()
//    public void __local_vftable_ctor_closure()
//    public void * __vecDelDtor(unsigned int)
//}

#endif  // DOLORI_RENDER_SPRRES_H_
