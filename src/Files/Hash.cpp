#include "Files/Hash.h"

#include <algorithm>
#include <functional>

CHash::CHash() : m_HashCode(), m_String() {}

CHash::CHash(const std::string& str) : CHash() { SetString(str); }

void CHash::SetString(const std::string& str) {
  m_String = str;

  std::transform(std::cbegin(m_String), std::cend(m_String),
                 std::begin(m_String), ::tolower);
  m_HashCode = std::hash<std::string>{}(m_String);
}

const std::string& CHash::GetString() const { return m_String; }
