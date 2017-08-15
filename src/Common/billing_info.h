#ifndef DOLORI_COMMON_BILLING_INFO_H_
#define DOLORI_COMMON_BILLING_INFO_H_

struct BILLING_INFO {
  char dummy1;
  unsigned long code;
  unsigned long time1;
  unsigned long time2;
  char dummy2[0x7];
};

#endif // DOLORI_COMMON_BILLING_INFO_H_
