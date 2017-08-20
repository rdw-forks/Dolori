#ifndef DOLORI_COMMON_PIXEL_FORMAT_H_
#define DOLORI_COMMON_PIXEL_FORMAT_H_

typedef enum PIXEL_FORMAT {
	PF_A1R5G5B5 = 0x0,
	PF_A4R4G4B4 = 0x1,
	PF_R5G6B5 = 0x2,
	PF_R5G5B5 = 0x3,
	PF_A8R8G8B8 = 0x4,
	PF_BUMP = 0x5,
	PF_LAST = 0x6,
	PF_UNSUPPORTED = 0xff,
} PIXEL_FORMAT;

#endif // DOLORI_COMMON_PIXEL_FORMAT_H_
