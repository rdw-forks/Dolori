#include "Render/ViewFrustum.h"

CViewFrustum::CViewFrustum() {}

CViewFrustum::~CViewFrustum() {}

void CViewFrustum::Build(float hratio, float vratio,
                         const glm::mat4 &view_matrix,
                         CSceneGraphNode *root_node) {}
