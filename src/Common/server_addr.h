#ifndef DOLORI_COMMON_SERVER_ADDR_H_
#define DOLORI_COMMON_SERVER_ADDR_H_

struct SERVER_ADDR {
  unsigned int ip;
  unsigned short port;
  unsigned char name[0x14];
  unsigned short usercount;
  unsigned short state;
  unsigned short property;
};

#endif // DOLORI_COMMON_SERVER_ADDR_H_
