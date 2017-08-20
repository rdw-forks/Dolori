#include "Vector3d.h"

CVector3d::CVector3d() {}

CVector3d::CVector3d(float x, float y, float z) {
	Set(x, y, z);
}

void CVector3d::Set(float x, float y, float z) {
	m_x = x;
	m_y = y;
	m_z = z;
}