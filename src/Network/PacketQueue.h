#ifndef DOLORI_NETWORK_PACKETQUEUE_H_
#define DOLORI_NETWORK_PACKETQUEUE_H_

#include <vector>

class CPacketQueue {
public:
  CPacketQueue();
  ~CPacketQueue();

  void Init(int);
  int GetSize();
  void InsertData(int, const char *);
  bool PeekData(int, char *);
  bool GetData(int, char *);
  bool RemoveData(int);
  char *GetDataPtr();

private:
  char *m_buf;
  int m_frontPos;
  int m_rearPos;
  std::vector<char> m_buffer;
};

// class CPacketQueue {
//	public void CPacketQueue(const class CPacketQueue &)
//		public void CPacketQueue::CPacketQueue(int)
//		public void CPacketQueue::CPacketQueue()
//		public void CPacketQueue::~CPacketQueue()
//		public void CPacketQueue::Init(int)
//		public int CPacketQueue::GetSize()
//		public void CPacketQueue::InsertData(int, const char *)
//		public unsigned char CPacketQueue::GetData(int, char *)
//		public unsigned char CPacketQueue::PeekData(int, char *)
//		public unsigned char CPacketQueue::RemoveData(int)
//		public int GetSafeDataLen()
//		public char * GetDataPtr()
//		/* this+0x0 */ char * m_buf
//		/* this+0x4 */ int m_frontPos
//		/* this+0x8 */ int m_rearPos
//	/* this+0xc */ class std::vector<char, std::allocator<char> > m_buffer
//
//		public class CPacketQueue & operator=(const class CPacketQueue
//&) 		public void * __vecDelDtor(unsigned int)
//}

#endif // DOLORI_NETWORK_PACKETQUEUE_H_
