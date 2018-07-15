#include "Render/RPQuadFace.h"

CRPQuadFace::CRPQuadFace() : CRPFace(4) {
  m_primType = GL_QUADS;
  m_indices = {0, 1, 3, 2};
}
