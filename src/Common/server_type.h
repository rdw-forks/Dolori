#ifndef DOLORI_COMMON_SERVERTYPE_H_
#define DOLORI_COMMON_SERVERTYPE_H_

enum class ServerType {
  kPrimary = 0x0,
  kSakray = 0x1,
  kLocal = 0x2,
  kInstantEvent = 0x3,
  kPVP = 0x4,
  kPK = 0x5,
  kSakPVP = 0x6,
  kSakPK = 0x7,
  kEvent = 0x8,
  kPrimary2 = 0x9,
  kTest = 0xa,
  kSakray2 = 0xb,
  kSakTest = 0xc,
  kADTest = 0xd,
  kEC = 0xe,
  kSakEC = 0xf,

  kLast
};

#endif  // DOLORI_COMMON_SERVERTYPE_H_
