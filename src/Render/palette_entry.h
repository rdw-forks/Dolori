#ifndef DOLORI_RENDER_PALETTE_ENTRY_H_
#define DOLORI_RENDER_PALETTE_ENTRY_H_

#pragma pack(push)
#pragma pack(1)

typedef struct PALETTE_ENTRY {
  unsigned char peRed;
  unsigned char peGreen;
  unsigned char peBlue;
  unsigned char peFlags;
} PALETTE_ENTRY;

#pragma pack(pop)

#endif  // DOLORI_RENDER_PALETTE_ENTRY_H_