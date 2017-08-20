#ifndef DOLORI_FILES_HASH_H_
#define DOLORI_FILES_HASH_H_

class CHash {
 public:
  CHash();
  ~CHash();
  void SetString(const char *);

 private:
  unsigned long m_HashCode;
  char m_String[0xfc];
};

// class CHash {
//	public void CHash::CHash(const char *)
//		public void CHash::CHash()
//		public void CHash::SetString(const char *)
//		public const char * c_str()
//		public unsigned char CHash::operator<(const class CHash &)
//		public unsigned char CHash::operator==(const class CHash &)
//		public unsigned char CHash::operator!=(const class CHash &)
//		/* this+0x0 */ unsigned long m_HashCode
//		/* this+0x4 */ char[0xfc] m_String
//		protected void CHash::CreateHashCode()
//}

#endif  // DOLORI_FILES_HASH_H_