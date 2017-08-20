#include "Hash.h"

#include <string.h>

CHash::CHash() {}

CHash::~CHash() {}

void CHash::SetString(const char* str) {
  size_t str_len;

  strcpy(m_String, str);
  strlwr(m_String);
  str_len = strlen(m_String);
  if (str_len == 0) {
    m_HashCode = 5381;
  } else {
    int hash = 5381;
    unsigned long i = 0;
    do {
      hash = 33 * hash + m_String[i++];
    } while (i < str_len);
    m_HashCode = hash;
  }
}
