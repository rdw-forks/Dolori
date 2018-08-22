#include "Render/3dNode.h"

void C3dNode::AssignModel(C3dNodeRes *p_node_res) {}

void C3dNode::Render(const glm::mat4 *matrix, int arg2, unsigned char arg3) {
  for (auto node : m_children) {
    node->Render(matrix, arg2, arg3);
  }
}
