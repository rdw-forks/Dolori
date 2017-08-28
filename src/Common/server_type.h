#ifndef DOLORI_COMMON_SERVERTYPE_H_
#define DOLORI_COMMON_SERVERTYPE_H_

typedef enum SERVER_TYPE {
  ServerPrimary = 0x0,
  ServerSakray = 0x1,
  ServerLocal = 0x2,
  ServerInstantEvent = 0x3,
  ServerPVP = 0x4,
  ServerPK = 0x5,
  ServerSakPVP = 0x6,
  ServerSakPK = 0x7,
  ServerEvent = 0x8,
  ServerPrimary2 = 0x9,
  ServerTest = 0xa,
  ServerSakray2 = 0xb,
  ServerSakTest = 0xc,
  ServerADTest = 0xd,
  ServerEC = 0xe,
  ServerSakEC = 0xf,
  ServerLast = 0x10,
} SERVER_TYPE;

#endif  // DOLORI_COMMON_SERVERTYPE_H_
