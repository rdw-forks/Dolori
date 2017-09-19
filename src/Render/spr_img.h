#ifndef DOLORI_RENDER_SPR_IMG_H_
#define DOLORI_RENDER_SPR_IMG_H_

#include <stdint.h>
// #include "Texture.h"

#pragma pack(push)
#pragma pack(1)

typedef struct SPR_IMG {
  uint16_t width;
  uint16_t height;
  uint16_t isHalfW;
  uint16_t isHalfH;
  // CTexture* tex;
  uint8_t* image_8bit;
} SPR_IMG;

#pragma pack(pop)

#endif  // DOLORI_RENDER_SPR_IMG_H_