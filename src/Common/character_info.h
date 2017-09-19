#ifndef DOLORI_COMMON_CHARACTER_INFO_H_
#define DOLORI_COMMON_CHARACTER_INFO_H_

#ifndef PACKETVER
#define PACKETVER 20080910
#endif

#pragma pack(push)
#pragma pack(1)
#pragma warning(disable : 4200)

struct CHARACTER_INFO {
  unsigned int char_id;
  unsigned int base_exp;
  int zeny;
  unsigned int job_exp;
  unsigned int job_level;
  unsigned int bodystate;
  unsigned int healthstate;
  unsigned int effectstate;
  int virtue;  // Karma
  int honor;   // Manner
  unsigned short status_points;
  unsigned int hp;
  unsigned int max_hp;
  unsigned short sp;
  unsigned short max_sp;
  unsigned short speed;
  unsigned short class_;
  unsigned short head_style;
#if PACKETVER >= 20141022
  unsigned short body;
#endif
  unsigned short weapon;
  unsigned short base_level;
  unsigned short skill_points;
  unsigned short head_bottom;
  unsigned short shield;
  unsigned short head_top;
  unsigned short head_mid;
  unsigned short head_color;
  unsigned short body_color;
  char name[24];
  unsigned char str;
  unsigned char agi;
  unsigned char vit;
  unsigned char int_;
  unsigned char dex;
  unsigned char luk;
  unsigned short char_slot;
  unsigned short can_rename;
#if (PACKETVER >= 20100720 && PACKETVER <= 20100727) || PACKETVER >= 20100803
  char map_name[MAP_NAME_LENGTH_EXT];
#endif
#if PACKETVER >= 20100803
  unsigned int delete_date;
#endif
#if PACKETVER >= 20110111
  // Non-standard (and probably wrong), since all equipment slots are 2-byte
  // shorts.
  unsigned int robe;
#endif
#if PACKETVER >= 20110928
  // Non-standard (and probably wrong), since can_rename is a 2-byte boolean.
  unsigned int can_changeslot;
#endif
};

#pragma pack(pop)
#pragma warning(default : 4200)

#endif  // DOLORI_COMMON_CHARACTER_INFO_H_
