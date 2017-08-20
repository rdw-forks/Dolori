#include "RPQuadFace.h"

CRPQuadFace::CRPQuadFace() {
	m_verts = m_qverts;
	m_numVerts = 4;
	m_numIndices = 0;
	m_primType = GL_QUADS;
}