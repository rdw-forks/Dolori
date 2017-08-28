#include "Renderer.h"
#include <math.h>
#include <iostream>
#include "../Common/Globals.h"

CRenderer::CRenderer() {}

void CRenderer::SetSize(int cx, int cy) {
  m_width = cx;
  m_height = cy;
  m_halfWidth = cx / 2;
  m_halfHeight = cy / 2;
  m_aspectRatio = cy / (float)cx;
  m_hpc = (double)(cx / 2) / tan(3.141592 * 15.0 * 0.0027777778);
  m_vpc = (double)(cy / 2) / tan(3.141592 * 15.0 * 0.0027777778);
  m_hratio = tan((90.0 - 15.0 * 0.5) * 3.141592 * 0.0055555557);
  m_xoffset = cx / 2;
  m_yoffset = cy / 2;
  m_vratio = tan((90.0 - 15.0 * 0.5) * 3.141592 * 0.0055555557);
  m_hpc = m_aspectRatio * m_hpc;
  m_hratio = m_aspectRatio * m_hratio;
  m_screenXFactor = cx * 0.0015625;
  m_screenYFactor = cy * 0.0020833334;
  // g_avgPixelRatio = cy * 0.0017447917;
  // g_slope = g_gradient / m_screenYFactor;
  // g_shadowSlope = g_gradient / m_screenYFactor;
}

int CRenderer::GetWidth() { return m_width; }

int CRenderer::GetHeight() { return m_height; }

void CRenderer::SetPixelFormat(PIXEL_FORMAT pf) { m_pf = pf; }

void CRenderer::DestroyAllRPList() {
  m_rpFaceList.clear();
  m_rpLMGroundList.clear();
  m_rpLMLightList.clear();
  m_rpAlphaDepthList.clear();
  m_rpAlphaList.clear();
  m_rpAlphaNoDepthList.clear();
  m_rpEmissiveDepthList.clear();
  m_rpEmissiveNoDepthList.clear();
  // m_rpRawAlphaList.clear();
  // m_rpRawEmissiveList.clear();
  m_rpAlphaOPList.clear();
  // m_rpLmList.clear();
  // m_rpBumpFaceList.clear();
}

void CRenderer::Clear(bool clearScreen) {
  if (clearScreen)
    g_3dDevice->Clear(0xFF000000);
  else
    g_3dDevice->ClearZBuffer();
}

void CRenderer::ClearBackground() { g_3dDevice->Clear(m_nClearColor); }

bool CRenderer::DrawScene() {
  /* Flush what needs to be drawn */
  FlushRenderList();
  /* Clear render list */
  DestroyAllRPList();

  return true;
}

void CRenderer::Flip() { g_3dDevice->ShowFrame(); }

void CRenderer::FlushRenderList() {
  FlushFaceList();
  FlushAlphaNoDepthList();
  FlushEmissiveNoDepthList();
}

// 0x2 : Emissive
// 0x200 : NO_DEPTH
void CRenderer::AddRP(CRPFace* face, int renderFlags) {
  if (m_isVertexFog) {
  }

  if (renderFlags & 0x1) {
    struct tlvertex3d v0 = face->GetVertex(0);
    struct tlvertex3d v1 = face->GetVertex(1);
    float index = (v0.oow - v1.oow) * 0.5 + v1.oow;

    if (renderFlags & 0x4) {
      m_rpAlphaOPList.push_back(face);
    } else if (renderFlags & 0x2) {
      if (renderFlags & 0x100) {
        m_rpEmissiveDepthList.push_back(std::make_pair(index, face));
      } else if (renderFlags & 0x200) {
        m_rpEmissiveNoDepthList.push_back(std::make_pair(index, face));
      } else {
        m_rpEmissiveList.push_back(std::make_pair(index, face));
      }
    } else if (renderFlags & 0x100) {
      m_rpAlphaDepthList.push_back(std::make_pair(index, face));
    } else if (renderFlags & 0x200) {
      m_rpAlphaNoDepthList.push_back(std::make_pair(index, face));
    } else {
      m_rpAlphaList.push_back(std::make_pair(index, face));
    }
  } else if (renderFlags & 0x800) {
    m_rpLMGroundList.push_back(face);
  } else if (!(renderFlags & 0x10)) {
    m_rpFaceList.push_back(face);
  } else {
    m_rpLMLightList.push_back(face);
  }
}

void CRenderer::DrawBoxScreen(int x, int y, int cx, int cy,
                              unsigned int color) {
  CRPQuadFace* face = new CRPQuadFace();
  struct tlvertex3d v[4];

  if (color & 0xFF000000) {
    v[0].x = x;
    v[0].y = y;
    v[0].z = 1e-006;
    v[0].oow = 0.999999f;

    v[1].x = x + cx;
    v[1].y = y;
    v[1].z = 1e-006;
    v[1].oow = 0.999999f;

    v[2].x = x + cx;
    v[2].y = y + cy;
    v[2].z = 1e-006;
    v[2].oow = 0.999999f;

    v[3].x = x;
    v[3].y = y + cy;
    v[3].z = 1e-006;
    v[3].oow = 0.999999f;

    face->SetGeomInfo(0, v[0]);
    face->SetColorInfo(0, color);
    face->SetGeomInfo(1, v[1]);
    face->SetColorInfo(1, color);
    face->SetGeomInfo(2, v[2]);
    face->SetColorInfo(2, color);
    face->SetGeomInfo(3, v[3]);
    face->SetColorInfo(3, color);
    AddRP(face, 0x201);
  }
}

// CRenderer::BorrowQuadRP
// Regarde si le QuadListIter fait partie de la liste QuadFace non vide
// Si tel est le cas, on retourne le QuadFace corresepondant
// Sinon on créer un nouveau QuadFace qu'on insère dans la liste des QuadFace
// Puis on retourne le QuadFace nouvellement créé

void CRenderer::FlushAlphaNoDepthList() {
  for (auto it = m_rpAlphaNoDepthList.begin(); it != m_rpAlphaNoDepthList.end();
       ++it) {
    (it->second)->DrawPri();
  }
}

void CRenderer::FlushEmissiveNoDepthList() {
  for (auto it = m_rpEmissiveNoDepthList.begin();
       it != m_rpEmissiveNoDepthList.end(); ++it) {
    (it->second)->DrawPri();
  }
}

void CRenderer::FlushFaceList() {
  for (auto it = m_rpFaceList.begin(); it != m_rpFaceList.end(); ++it) {
    (*it)->DrawPri();
  }
}