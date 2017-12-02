#ifndef DOLORI_RENDER_LIGHTMAP_H_
#define DOLORI_RENDER_LIGHTMAP_H_

typedef struct LIGHTMAP {
  unsigned char brightObj[0x3];
  class CTexture* surface;
  // struct texCoor coor[0x4];
  // struct COLOR intensity[0x4];
} LIGHTMAP;

#endif  // DOLORI_RENDER_LIGHTMAP_H_