#include "RPTriFace.h"

CRPTriFace::CRPTriFace() : CRPFace(3) {
  m_primType = GL_TRIANGLES;
  m_indices = {0, 1, 2};
}