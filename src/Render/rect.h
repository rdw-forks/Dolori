#ifndef DOLORI_RENDER_RECT_H_
#define DOLORI_RENDER_RECT_H_

#ifndef _WIN32
#include <stdint.h>

typedef struct _RECT {
  uint32_t left;
  uint32_t top;
  uint32_t right;
  uint32_t bottom;
} RECT;
#else
#include <windows.h>
#endif  // _WIN32

#endif  // DOLORI_RENDER_RECT_H_
