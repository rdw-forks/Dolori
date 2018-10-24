#ifndef DOLORI_RENDER_SPRRES_H_
#define DOLORI_RENDER_SPRRES_H_

#include <memory>
#include <string>
#include <vector>
#include "Files/Res.h"

#pragma pack(push)
#pragma pack(1)

typedef struct _SPR_IMG {
  uint16_t width;
  uint16_t height;
  uint16_t isHalfW;
  uint16_t isHalfH;
  std::vector<uint8_t> image_8bit;
} SprImg;

#pragma pack(pop)

typedef enum _SPR_TYPE {
  SPR_TYPE_PAL = 0,
  SPR_TYPE_RGBA,

  SPR_TYPE_COUNT
} SPR_TYPE;

class CSprRes : public CRes {
 public:
  CSprRes();
  ~CSprRes();

  bool Load(const std::string& filename) override;
  CRes* Clone() override;

  const uint32_t* GetPalette() const;
  SprImg* GetSprImg(SPR_TYPE clip_type, size_t spr_index) const;

 protected:
  void Reset() override;

 private:
  static void DecodeRLE(const std::vector<uint8_t>& image, int w, int h,
                        std::vector<uint8_t>& output);

 private:
  uint32_t m_palette[0x100];
  std::vector<std::unique_ptr<SprImg>> m_sprites[SPR_TYPE_COUNT];
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
