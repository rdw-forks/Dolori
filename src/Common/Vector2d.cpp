#include "Vector2d.h"

CVector2d::CVector2d(float x, float y) { Set(x, y); }

CVector2d::CVector2d() {}

CVector2d::~CVector2d() {}

void CVector2d::Set(float x, float y) {
  m_x = x;
  m_y = y;
}

void CVector2d::Normalize() {}