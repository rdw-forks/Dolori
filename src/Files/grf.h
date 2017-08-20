#ifndef DOLORI_FILES_GRF_H_
#define DOLORI_FILES_GRF_H_

#include <stdint.h>

#define GRF_MAGIC_VALUE "Master of Magic"

#pragma pack(push, 1)
struct GRF_HEADER {
	char Magic[16];  /// "Master of Magic" +\0
	char Key[14];    // 0x01 -&gt; 0x0E, or 0x00 -&gt; 0x00 (no encryption)
	uint32_t FileTableOffset;  /// The location of the file table
	uint32_t Seed;             /// What is the value of randomly
	uint32_t FilesCount;  /// The actual number of files = FilesCount - Seed - 7
	uint32_t Version;     /// GRF file version: 0x102, 0x103, 0x200
};
#pragma pack(pop)

#endif // DOLORI_FILES_GRF_H_
