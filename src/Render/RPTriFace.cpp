#include "RPTriFace.h"

CRPTriFace::CRPTriFace() {
	m_verts = m_tverts;
	m_numVerts = 3;
	m_numIndices = 0;
	m_primType = GL_TRIANGLES;
}