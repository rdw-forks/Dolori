#ifndef DOLORI_RENDER_CACHE_INFO_H_
#define DOLORI_RENDER_CACHE_INFO_H_

typedef struct CACHE_INFO {
  size_t id;
  size_t pal_id;
  unsigned long last_time;
  float tu;         // 12
  float tv;         // 16
  float tu1;        // 20
  float tv1;        // 24
  unsigned long x;  // 28
  unsigned long y;  // 32
} CACHE_INFO;

#endif  // DOLORI_RENDER_CACHE_INFO_H_
