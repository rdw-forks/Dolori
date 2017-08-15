#ifndef DOLORI_COMMON_VECTOR2D_H_
#define DOLORI_COMMON_VECTOR2D_H_

class CVector2d {
public:
  CVector2d(float, float);
  CVector2d();
  ~CVector2d();

  void Set(float, float);
  void Normalize();

private:
  /* this+0x0 */ float m_x;
  /* this+0x4 */ float m_y;
};

#endif // DOLORI_COMMON_VECTOR2D_H_