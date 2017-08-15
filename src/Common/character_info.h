#ifndef DOLORI_COMMON_CHARACTER_INFO_H_
#define DOLORI_COMMON_CHARACTER_INFO_H_

#pragma pack(push)
#pragma pack(1)
#pragma warning(disable : 4200)

struct CHARACTER_INFO {
  unsigned long GID;
  int exp;
  int money;
  int jobexp;
  int joblevel;
  int bodystate;
  int healthstate;
  int effectstate;
  int virtue;
  int honor;
  short jobpoint;
  short hp;
  short maxhp;
  short sp;
  short maxsp;
  short speed;
  short job;
  short head;
  short weapon;
  short level;
  short sppoint;
  short accessory;
  short shield;
  short accessory2;
  short accessory3;
  short headpalette;
  short bodypalette;
  unsigned char name[0x18];
  unsigned char Str;
  unsigned char Agi;
  unsigned char Vit;
  unsigned char Int;
  unsigned char Dex;
  unsigned char Luk;
  unsigned char CharNum;
  unsigned char haircolor;
  short bIsChangedCharName;
};

#pragma pack(pop)
#pragma warning(default : 4200)

#endif // DOLORI_COMMON_CHARACTER_INFO_H_