#ifndef DOLORI_RENDER_TEXTURE_H_
#define DOLORI_RENDER_TEXTURE_H_

#include "Surface.h"
#include "pixel_format.h"

class CTexture :
	public CSurface {
public:
	CTexture();
	CTexture(unsigned long, unsigned long, PIXEL_FORMAT);
	virtual ~CTexture();
	//static void SetUVOffset(float, float);
	bool Create(unsigned long, unsigned long, PIXEL_FORMAT);
	bool CreateBump(unsigned long, unsigned long);

private:
	PIXEL_FORMAT m_pf;
	unsigned char m_blackkey;
	unsigned long m_updateWidth;
	unsigned long m_updateHeight;
	char m_texName[256];
	long m_lockCnt;
	unsigned long m_timeStamp;
	//static float m_uOffset;
	//static float m_vOffset;
};

#endif  // DOLORI_RENDER_TEXTURE_H_
