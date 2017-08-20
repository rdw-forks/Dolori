#ifndef DOLORI_COMMON_VECTOR3D_H_
#define DOLORI_COMMON_VECTOR3D_H_


class CVector3d {
 public:
  CVector3d(float, float, float);
  CVector3d();
  void Set(float, float, float);
  // public void MatrixMult(const struct vector3d &, const struct matrix &)
  // public void CrossProduct(const struct vector3d &, const struct vector3d
  // &)  public void Normalize()  public float Magnitude()  public float
  // Angle(const struct vector3d &)  public float DotProduct(const struct
  // vector3d &)
 private:
  /* this+0x0 */ float m_x;
  /* this+0x4 */ float m_y;
  /* this+0x8 */ float m_z;
};

#endif // DOLORI_COMMON_VECTOR3D_H_